/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 20/05/18
 */

#include <vector>
#include <Box2D/Dynamics/b2Body.h>
#include <iostream>
#include "PlayerJumping.h"
#include "Player.h"

Worms::Jumping::Jumping(): State(Worm::StateID::Jumping){}

void Worms::Jumping::update(Worms::Player &p, float dt, b2Body *body){
    /*
     * when the worm lands (there was a collision between the worm and the
     * girder) it has to changes its state to endJump, and take an impulse
     * of equal absolute value and different sign of the impulse taken in
     * startJump stage (remember, the worm has a friction coefficient 0).
     *
     * In the y-axis there will be no impulse because its velocity was
     * cancelled because of the collision with the girder.
     */
    if (p.getContactCount() > 0){
        float32 mass = body->GetMass();
        b2Vec2 previousVel = body->GetLinearVelocity();
        b2Vec2 impulses = {mass * (0.0f - previousVel.x), 0.0f};
        body->ApplyLinearImpulseToCenter(impulses, true);

        p.setState(Worm::StateID::EndJump);
    }
}

void Worms::Jumping::moveRight(Worms::Player &p) {}

void Worms::Jumping::moveLeft(Worms::Player &p) {}

void Worms::Jumping::jump(Worms::Player &p) {}

void Worms::Jumping::stopMove(Worms::Player &p) {}

void Worms::Jumping::backFlip(Worms::Player &p) {}

void Worms::Jumping::bazooka(Worms::Player &p) {}

void Worms::Jumping::pointUp(Worms::Player &p){}

void Worms::Jumping::pointDown(Worms::Player &p){}

void Worms::Jumping::startShot(Worms::Player &p) {}
