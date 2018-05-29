/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __PLAYER_H__
#define __PLAYER_H__

#define PLAYER_WIDTH 0.8f

#define PLAYER_HEIGHT 2.0f

#include "Bullet.h"
#include "GameStateMsg.h"
#include "Physics.h"
#include "PlayerState.h"
#include "Point.h"
#include "Stream.h"
#include "Weapon.h"

enum class PlayerState { movingRight, movingLeft, still };

namespace Worms {
enum class Direction { right, left, up, down };

class Player : public PhysicsEntity {
   public:
    Direction direction;

    explicit Player(Physics &physics);
    ~Player() = default;

    void update(float dt);
    void serialize(IO::Stream<IO::GameStateMsg> &s) const {}
    void setPosition(const Math::Point<float> &newPos);
    Math::Point<float> getPosition() const;
    void handleState(IO::PlayerInput pi);
    Worm::StateID getStateId() const;
    void setState(Worm::StateID stateID);
    int getContactCount();
    void startContact() override;
    void endContact() override;
    float getWeaponAngle() const;
    const Worm::WeaponID &getWeaponID() const;
    void setWeaponID(const Worm::WeaponID &id);
    void increaseWeaponAngle();
    void decreaseWeaponAngle();
    void startShot();
    void endShot();
    void shoot(int shotPower);
    std::shared_ptr<Worms::Bullet> getBullet() const;
    void destroyBullet();
    void acknowledgeDamage(Worms::DamageInfo damageInfo, Math::Point<float> epicenter);
    float getLife() const;

   private:
    std::shared_ptr<Worms::State> state{nullptr};
    b2Body *body{nullptr};
    b2BodyDef bodyDef;
    b2PolygonShape shape;
    b2FixtureDef fixture;
    Physics &physics;
    std::shared_ptr<Worms::Bullet> bullet{nullptr};
    Worms::Weapon weapon;
    int numContacts{0};
    float life{100.0f};
};
}  // namespace Worms

#endif  //__PLAYER_H__
