/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include <zconf.h>
#include <atomic>
#include <chrono>
#include <iostream>
#include <Stage.h>
#include "Box2D/Box2D.h"
#include "Chronometer.h"
//#include <random>

#include "Config.h"
#include "Game.h"
#include "Player.h"
#include "Stage.h"
#include "ImpactOnCourse.h"

Worms::Game::Game(Stage &&stage, std::vector<CommunicationSocket> &sockets)
    : physics(b2Vec2{0.0f, -10.0f}),
      stage(std::move(stage)),
      maxTurnTime(::Game::Config::getInstance().getExtraTurnTime()),
      gameTurn(*this),
      sockets(sockets),
      inputs(sockets.size()) {
    this->inputThreads.reserve(sockets.size());
    this->outputThreads.reserve(sockets.size());
    for (std::size_t i = 0; i < sockets.size(); i++) {
        this->inputThreads.emplace_back([this, i] { this->inputWorker(i); });
        this->outputThreads.emplace_back([this, i] { this->outputWorker(i); });
    }
    /* reserves the required space to avoid reallocations that may move the worm addresses */
    this->players.reserve(this->stage.getWorms().size());
    uint8_t id = 0;
    for (auto &wormData : this->stage.getWorms()) {
        /* initializes the instances */
        this->players.emplace_back(this->physics);
        this->players.back().setPosition(wormData.position);
        this->players.back().health = wormData.health;
        this->players.back().setId(id);
        this->players.back().addObserver(this);
        id++;
    }

    this->teams.makeTeams(this->players, (uint8_t)sockets.size());

    /* sets the girders */
    for (auto &girder : this->stage.getGirders()) {
        b2PolygonShape poly;

        b2BodyDef bdef;
        bdef.type = b2_staticBody;
        bdef.position.Set(0.0f, 0.0f);
        b2Body *staticBody = this->physics.createBody(bdef);

        b2FixtureDef fixture;
        fixture.density = 1;
        fixture.shape = &poly;

        poly.SetAsBox(girder.length / 2, girder.height / 2, b2Vec2(girder.pos.x, girder.pos.y), 0);
        staticBody->CreateFixture(&fixture);
    }

    this->currentWorm = this->teams.getCurrentPlayerID();
    this->currentWormToFollow = this->currentWorm;

    this->gameClock.addObserver(this);
}

Worms::Game::~Game() {
    this->exit();
    for (auto &t : this->outputThreads) {
        t.join();
    }

    for (auto &t : this->inputThreads) {
        t.join();
    }
}

/**
 * @brief Reads player messages from a socket and pushes them into the input queue.
 *
 * @param playerIndex The index of the player.
 */
void Worms::Game::inputWorker(std::size_t playerIndex) {
    PlayerInput &input = this->inputs.at(playerIndex);
    CommunicationSocket &socket = this->sockets.at(playerIndex);

    /* TODO: avoid hardcoding the size */
    IO::PlayerMsg msg;
    char *buffer = new char[msg.getSerializedSize()];

    try {
        while (!this->quit) {
            /* reads the raw data from the buffer */
            socket.receive(buffer, msg.getSerializedSize());

            /* sets the struct data from the buffer */
            msg.deserialize(buffer, msg.getSerializedSize());

            /* pushes the message into the player's input queue if it's the current player */
            if (this->currentTeam == playerIndex) {
                input.push(msg);
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Worms::Game::inputWorker:" << e.what() << std::endl;
        this->quit = true;
    }

    delete buffer;
}

/**
 * @brief Sends model snapshot messages to a socket.
 *
 * @param playerIndex The index of the player to send the spanshots to.
 */
void Worms::Game::outputWorker(std::size_t playerIndex) {
    CommunicationSocket &socket = this->sockets.at(playerIndex);

    IO::GameStateMsg msg;
    char *buffer = new char[msg.getSerializedSize()];

    try {
        while (!this->quit) {
            msg = this->snapshot.get(true);
            msg.serialize(buffer, msg.getSerializedSize());
            socket.send(buffer, msg.getSerializedSize());
        }
    } catch (const std::exception &e) {
        std::cerr << "Worms::Game::outputWorker:" << e.what() << std::endl;
        this->quit = true;
    }

    delete buffer;
}

void Worms::Game::start() {
    try {
        /* game loop */
        Utils::Chronometer chronometer;
        float lag = 0.0f;
        float32 timeStep = 1.0f / 60.0f;

        while (!quit) {
            double dt = chronometer.elapsed();
            lag += dt;

            this->gameClock.update(dt);
            this->gameTurn.update(dt);

            IO::PlayerMsg pMsg;
            if (this->inputs.at(this->currentTeam).pop(pMsg, false)) {
                if (this->processingClientInputs) {
                    if (this->currentPlayerShot) {
                        if (pMsg.input != IO::PlayerInput::startShot &&
                            pMsg.input != IO::PlayerInput::endShot) {
                            this->players.at(this->currentWorm).handleState(pMsg);
                        }
                    } else {
                        this->players.at(this->currentWorm).handleState(pMsg);
                    }
                }
            }

            /* updates the actors */
            for (auto &worm : this->players) {
                worm.update(dt);
            }

            /* updates the physics engine */
            for (int i = 0; i < 5 && lag > timeStep; i++) {
                this->physics.update(timeStep);
                lag -= timeStep;
            }

            /* serializes and updates the game state */
            this->snapshot.set(this->serialize());
            this->snapshot.swap();

            usleep(16 * 1000);
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl << "In Worms::Game::start" << std::endl;
    } catch (...) {
        std::cerr << "Unkown error in Worms::Game::start()" << std::endl;
    }
}

void Worms::Game::endTurn() {
    this->teams.endTurn(this->players);
    this->currentTeam = this->teams.getCurrentTeam();
    this->currentWorm = this->teams.getCurrentPlayerID();
    this->currentWormToFollow = this->currentWorm;

    this->processingClientInputs = true;
    this->gameClock.restart();
    this->gameTurn.restart();
}

IO::GameStateMsg Worms::Game::serialize() const {
    assert(this->players.size() <= 20);

    IO::GameStateMsg m;
    m.num_worms = 0;
    for (const auto &worm : this->players) {
        m.positions[m.num_worms * 2] = worm.getPosition().x;
        m.positions[m.num_worms * 2 + 1] = worm.getPosition().y;
        m.stateIDs[m.num_worms] = worm.getStateId();
        m.wormsHealth[m.num_worms] = worm.health;
        m.wormsTeam[m.num_worms] = worm.getTeam();
        m.num_worms++;
    }

    /* sets the current player's data */
    m.elapsedTurnSeconds = this->gameClock.getTimeElapsed();
    m.currentPlayerTurnTime = this->gameClock.getTurnTime();
    m.currentWorm = this->currentWorm;
    m.currentWormToFollow = this->currentWormToFollow;
    m.currentTeam = this->currentTeam;
    m.activePlayerAngle = this->players[this->currentWorm].getWeaponAngle();
    m.activePlayerWeapon = this->players[this->currentWorm].getWeaponID();

    m.bulletsQuantity = this->players[this->currentWorm].getBullets().size();
    uint8_t i = 0, j = 0;
    for (auto &bullet : this->players[this->currentWorm].getBullets()) {
        Math::Point<float> p = bullet.getPosition();
        m.bullets[i++] = p.x;
        m.bullets[i++] = p.y;
        m.bulletsAngle[j] = bullet.getAngle();
        m.bulletType[j++] = bullet.getWeaponID();
    }

    m.processingInputs = this->processingClientInputs;

    return m;
}

void Worms::Game::exit() {
    this->quit = true;
}

void Worms::Game::onNotify(Subject &subject, Event event) {
    switch (event) {
        /**
         * Because i didnt want to move all responsability of the bullets to
         * the game (until the refactor of the start), i added this function
         * that delegates to the player the responsability to iterate all over
         * the bullets and add the game as an observer
         */
        case Event::Shot: {
             this->players[this->currentWorm].addObserverToBullets(this);
             this->gameClock.playerShot();
             this->gameTurn.playerShot(this->players[this->currentWorm].getWeaponID());
             this->currentPlayerShot = true;
             break;
        }
        /**
         * On explode, the game must check worms health.
         */
        case Event::Explode: {
            auto &bullet = dynamic_cast<const Bullet &>(subject);
            this->gameTurn.explosion();
            this->calculateDamage(bullet);
            break;
        }
        /**
         * onExplode will create new Bullets in player's container, and we
         * need to listen to them.
         */
        case Event::OnExplode: {
            auto &bullet = dynamic_cast<const Bullet &>(subject);
            this->calculateDamage(bullet);
            this->players[this->currentWorm].onExplode(bullet, this->physics);
            this->players[this->currentWorm].addObserverToBullets(this);
            break;
        }
        case Event::WormFalling: {
            this->gameTurn.wormFalling(dynamic_cast<const Player &>(subject).getId());
            break;
        }
        case Event::WormLanded: {
            this->gameTurn.wormLanded(dynamic_cast<const Player &>(subject).getId());
            break;
        }
        case Event::Hit: {
            this->gameTurn.wormHit(dynamic_cast<const Player &>(subject).getId());
            break;
        }
        case Event::EndHit: {
            this->gameTurn.wormEndHit(dynamic_cast<const Player &>(subject).getId());
            break;
        }
        case Event::Drowning: {
            this->gameTurn.wormDrowning(dynamic_cast<const Player &>(subject).getId());
            break;
        }
        case Event::Drowned: {
            this->gameTurn.wormDrowned(dynamic_cast<const Player &>(subject).getId());
            break;
        }
        case Event::Dying: {
            this->gameTurn.wormDying();
            break;
        }
        case Event::Dead: {
            this->gameTurn.wormDead();
            this->gameTurn.endTurn();
            break;
        }
        case Event::NewWormToFollow: {
            this->currentWormToFollow = dynamic_cast<const ImpactOnCourse &>(subject).getWormToFollow();
            break;
        }
        case Event::DamageOnLanding: {
            this->gameClock.endTurn();
            break;
        }
        case Event::ImpactEnd: {
            auto &wormsHit = dynamic_cast<ImpactOnCourse &>(subject).getWormsHit();
            for (auto worm : wormsHit) {
                Worm::StateID wormState = this->players[worm].getStateId();
                if (this->players[worm].health == 0) {
                    if (wormState != Worm::StateID::Die &&
                        wormState != Worm::StateID::Dead) {
                        this->players[worm].setState(Worm::StateID::Die);
                    }
                }
            }
            break;
        }
        case Event::EndTurn: {
            this->processingClientInputs = false;
            this->gameTurn.endTurn();
            break;
        }
        case Event::TurnEnded: {
            if (this->players[this->currentWorm].getStateId() != Worm::StateID::Dead) {
                this->players[this->currentWorm].setState(Worm::StateID::Still);
            }
            this->currentPlayerShot = false;
            this->gameClock.waitForNextTurn();
            break;
        }
        case Event::NextTurn: {
            this->endTurn();
            break;
        }
    }
}

void Worms::Game::calculateDamage(const Worms::Bullet &bullet) {
    ::Game::Bullet::DamageInfo damageInfo = bullet.getDamageInfo();
    for (auto &worm : this->players) {
        worm.acknowledgeDamage(damageInfo, bullet.getPosition());
    }
    this->players[this->currentWorm].cleanBullets();
}