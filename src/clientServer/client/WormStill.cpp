/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include "WormStill.h"
#include "Texture.h"

Worm::Still::Still() : State(StateID::Still) {}

Worm::Still::~Still() {}

void Worm::Still::update(float dt) {}

IO::PlayerInput Worm::Still::moveRight(Worm &w) {
    w.setState(StateID::Walk);
    w.direction = ::Worm::Direction::right;
    return IO::PlayerInput::moveRight;
}

IO::PlayerInput Worm::Still::moveLeft(Worm &w) {
    w.setState(StateID::Walk);
    w.direction = ::Worm::Direction::left;
    return IO::PlayerInput::moveLeft;
}

IO::PlayerInput Worm::Still::stopMove(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Still::jump(Worm &w) {
    w.setState(StateID::StartJump);
    return IO::PlayerInput::startJump;
}

IO::PlayerInput Worm::Still::backFlip(Worm &w) {
    w.setState(StateID::StartBackFlip);
    return IO::PlayerInput::startBackFlip;
}

IO::PlayerInput Worm::Still::bazooka(Worm &w) {
    w.setState(StateID::Bazooka);
    return IO::PlayerInput::bazooka;
}

IO::PlayerInput Worm::Still::pointUp(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Still::pointDown(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Still::startShot(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Still::endShot(Worm &w) {
    return IO::PlayerInput::moveNone;
}