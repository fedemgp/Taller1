/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 26/05/18
 */

#include <cmath>
#include <iostream>

#include "../Config/Config.h"
#include "Bullet.h"
#include "Weapon.h"
#include "../Physics.h"
#include "../PhysicsEntity.h"

Worms::Bullet::Bullet(BulletInfo &info, Worms::Physics &physics, Worm::WeaponID weapon)
    : PhysicsEntity(Worms::EntityID::EtBullet), physics(physics), weaponID(weapon), info(info) {
    float distance = info.safeNonContactDistance + info.radius;
    this->bodyDef.type = b2_dynamicBody;
    this->bodyDef.position.Set(info.point.x + distance * cos(info.angle * PI / 180.0f),
                               info.point.y + distance * sin(info.angle * PI / 180.0f));
    this->bodyDef.fixedRotation = true;

    this->body = this->physics.createBody(this->bodyDef);
    this->shape.m_p.Set(0.0f, 0.0f);
    this->shape.m_radius = info.radius;
    this->fixture.shape = &this->shape;
    this->fixture.density = 1.0f;
    this->fixture.restitution = info.restitution;
    this->fixture.friction = info.friction;

    this->body->CreateFixture(&this->fixture);
    this->body->SetUserData(this);

    //    this->body->SetTransform(this->body->GetPosition(), info.angle);
}

void Worms::Bullet::update(float dt, Config::Wind wind) {
    if (this->keepUpdating) {
        this->timeElapsed += dt;
        if (!this->impulseApplied) {
            float32 mass = this->body->GetMass();
            b2Vec2 impulses = {mass * float32(this->info.power * this->info.dampingRatio *
                                              cos(this->info.angle * PI / 180.0f)),
                               mass * float32(this->info.power * this->info.dampingRatio *
                                              sin(this->info.angle * PI / 180.0f))};
            b2Vec2 position = this->body->GetWorldCenter();
            this->body->ApplyLinearImpulse(impulses, position, true);
            this->impulseApplied = true;
        } else {
            b2Vec2 velocity = this->body->GetLinearVelocity();
            this->info.angle = atan2(velocity.y, velocity.x) * 180.0f / PI;
            if (this->info.angle < 0) {
                this->info.angle += 360.0f;
            }
        }

        if (this->info.windAffected) {
            this->body->ApplyForceToCenter(b2Vec2{wind.instensity * wind.xDirection, 0.0f}, true);
        }

        if (this->hasExploded()) {
            this->notify(*this, this->info.explodeEvent);
            this->weaponID = Worm::WeaponID::WExplode;
            this->keepUpdating = false;
            b2Vec2 lastP = this->body->GetPosition();
            this->lastPosition = {lastP.x, lastP.y};
            this->destroyBody();
        }
    }
}

Math::Point<float> Worms::Bullet::getPosition() const {
    if (this->keepUpdating) {
        b2Vec2 p = this->body->GetPosition();
        return Math::Point<float>(p.x, p.y);
    } else {
        return this->lastPosition;
    }
}

float Worms::Bullet::getAngle() const {
    return (this->info.angle >= 0 && this->info.angle < 90) ? this->info.angle + 360.0f
                                                            : this->info.angle;
}

void Worms::Bullet::startContact(Worms::PhysicsEntity *physicsEntity) {
    this->madeImpact = true;
}

void Worms::Bullet::endContact(Worms::PhysicsEntity *physicsEntity) {}

Worms::Bullet::~Bullet() {
    this->destroyBody();
}

bool Worms::Bullet::hasExploded() const {
    if (this->getPosition().y < Game::Config::getInstance().getWaterLevel()) {
        return true;
    }
    if (this->info.explotionTimeout > 0) {
        return this->timeElapsed >= this->info.explotionTimeout;
    } else {
        return this->madeImpact;
    }
}

Config::Bullet::DamageInfo Worms::Bullet::getDamageInfo() const {
    return this->info.dmgInfo;
}

bool Worms::Bullet::operator<(Worms::Bullet &other) {
    return this->timeElapsed > other.timeElapsed;
}

Worm::WeaponID Worms::Bullet::getWeaponID() const {
    return this->weaponID;
}

void Worms::Bullet::destroyBody() {
    if (this->body != nullptr) {
        this->body->GetWorld()->DestroyBody(this->body);
        this->body = nullptr;
    }
}
