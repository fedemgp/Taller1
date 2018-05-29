/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 26/05/18
 */

#ifndef __BULLET_H__
#define __BULLET_H__

#include "Physics.h"
#include "PhysicsEntity.h"
#include "Point.h"

#define PI 3.14159265
#define DAMAGE 50.0f
#define DAMAGE_RADIUS 2.0f

namespace Worms {
struct DamageInfo {
    float damage;
    float radius;
};

class Bullet : public PhysicsEntity {
   public:
    Bullet(Math::Point<float> p, float safeNonContactDistance, float angle, int power,
           Worms::Physics &physics);
    ~Bullet();
    void update(float dt);
    Math::Point<float> getPosition() const;
    float getAngle() const;
    virtual void startContact() override;
    virtual void endContact() override;
    bool madeImpact();
    DamageInfo getDamageInfo();

   private:
    b2Body *body{nullptr};
    b2BodyDef bodyDef;
    b2CircleShape shape;
    b2FixtureDef fixture;
    Worms::Physics &physics;
    float angle{0};
    int numContacts{0};
    bool impulseApplied{false};
    float radius{0.5f};
    int power{0};
    DamageInfo damageInfo;
};
}  // namespace Worms

#endif  //__BULLET_H__