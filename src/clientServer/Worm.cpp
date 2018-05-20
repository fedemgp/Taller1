/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include <SDL2/SDL_system.h>

#include "GameStateMsg.h"
#include "Worm.h"
#include "WormJump.h"
#include "WormStill.h"
#include "WormWalk.h"

Worm::Worm::Worm(const GUI::GameTextureManager &texture_mgr)
    : texture_mgr(texture_mgr), animation(texture_mgr.get(GUI::GameTextures::WormIdle)) {
    this->setState(::Worm::StateID::Still);
}

void Worm::Worm::handleKeyDown(SDL_Keycode key, IO::Stream<IO::PlayerInput> *out) {
    IO::PlayerInput i;
    switch (key) {
        case SDLK_RIGHT:
            i = this->state->moveRight(*this);
            if (i != IO::PlayerInput::moveNone)
                *out << i;
            break;
        case SDLK_LEFT:
            i = this->state->moveLeft(*this);
            if (i != IO::PlayerInput::moveNone)
                *out << i;
            break;
        case SDLK_a:
            i = this->state->jump(*this);
            if (i != IO::PlayerInput::moveNone)
                *out << i;
            break;
    }
}

void Worm::Worm::handleKeyUp(SDL_Keycode key, IO::Stream<IO::PlayerInput> *out) {
    IO::PlayerInput i;
    switch (key) {
        case SDLK_RIGHT:
            i = this->state->stopMove(*this);
            if (i != IO::PlayerInput::moveNone)
                *out << i;
            break;
        case SDLK_LEFT:
            i = this->state->stopMove(*this);
            if (i != IO::PlayerInput::moveNone)
                *out << i;
            break;
    }
}

void Worm::Worm::render(int x, int y, SDL_Renderer &renderer) {
    if (this->direction == Direction::left) {
        this->animation.setFlip(SDL_FLIP_NONE);
    } else {
        this->animation.setFlip(SDL_FLIP_HORIZONTAL);
    }

    this->animation.render(renderer, x, y);
}

void Worm::Worm::update(float dt) {
    this->state->update(dt);
    this->animation.update(dt);
}

GUI::Animation Worm::Worm::getAnimation(::Worm::StateID state) const {
    GUI::GameTextures texture_id;
    switch (state) {
        case StateID::Still:
            texture_id = GUI::GameTextures::WormIdle;
            break;
        case StateID::Walk:
            texture_id = GUI::GameTextures::WormWalk;
            break;
        case StateID::StartJump:
            texture_id = GUI::GameTextures::StartJump;
            break;
        case StateID::Jumping:
            texture_id = GUI::GameTextures::Jumping;
            break;
    }
    if (state == StateID::Still) {
        return GUI::Animation{this->texture_mgr.get(texture_id), true};
    }

    return GUI::Animation{this->texture_mgr.get(texture_id)};
}

void Worm::Worm::setState(StateID state) {
    if (this->state == nullptr || this->state->getState() != state) {
        this->animation = this->getAnimation(state);

        /* creates the right state type */
        switch (state) {
            case StateID::Still:
                this->state = std::shared_ptr<State>(new Still());
                break;
            case StateID::Walk:
                this->state = std::shared_ptr<State>(new Walk());
                break;
            case StateID::StartJump:
                this->state = std::shared_ptr<State>(new Jump());
                break;
            case StateID::Jumping:
                break;
        }
    }
}
