/*
 *  Created by Rodrigo.
 *  date: 21/05/18
 */

#include "BackFlipping.h"
#include "../Player.h"

Worms::BackFlipping::BackFlipping(GUI::Position p)
    : State(Worm::StateID::BackFlipping), startPosition(p) {}

void Worms::BackFlipping::update(Worms::Player &p, float dt, b2Body *body) {
    /*
     * when the worm lands (there was a collision between the worm and the
     * girder) it has to changes its state to endJump, and take an impulse
     * of equal absolute value and different sign of the impulse taken in
     * startJump stage (remember, the worm has a friction coefficient 0).
     *
     * In the y-axis there will be no impulse because its velocity was
     * cancelled because of the collision with the girder.
     */
    this->timeElapsed += dt;

    if (p.isOnGround()) {
        float32 mass = body->GetMass();
        b2Vec2 previousVel = body->GetLinearVelocity();
        b2Vec2 impulses = {mass * (0.0f - previousVel.x), 0.0f};
        body->ApplyLinearImpulseToCenter(impulses, true);

        p.landDamage(this->startPosition.y - p.getPosition().y);
        p.setState(Worm::StateID::Land);
        //        p.setState(Worm::StateID::EndBackFlip);
    }
}

void Worms::BackFlipping::moveRight(Worms::Player &p) {}

void Worms::BackFlipping::moveLeft(Worms::Player &p) {}

void Worms::BackFlipping::jump(Worms::Player &p) {}

void Worms::BackFlipping::stopMove(Worms::Player &p) {}

void Worms::BackFlipping::backFlip(Worms::Player &p) {}

void Worms::BackFlipping::bazooka(Worms::Player &p) {}

void Worms::BackFlipping::pointUp(Worms::Player &p) {}

void Worms::BackFlipping::pointDown(Worms::Player &p) {}

void Worms::BackFlipping::startShot(Worms::Player &p) {}

void Worms::BackFlipping::endShot(Worms::Player &p) {}

void Worms::BackFlipping::grenade(Worms::Player &p) {}

void Worms::BackFlipping::cluster(Worms::Player &p) {}

void Worms::BackFlipping::mortar(Worms::Player &p) {}

void Worms::BackFlipping::banana(Worms::Player &p) {}

void Worms::BackFlipping::holy(Worms::Player &p) {}

void Worms::BackFlipping::setTimeout(Worms::Player &p, uint8_t time) {}

void Worms::BackFlipping::aerialAttack(Worms::Player &p) {}

void Worms::BackFlipping::dynamite(Worms::Player &p) {}

void Worms::BackFlipping::teleport(Worms::Player &p) {}

void Worms::BackFlipping::baseballBat(Worms::Player &p) {}
