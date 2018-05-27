/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __PLAYER_H__
#define __PLAYER_H__

#define MIN_ANGLE -90
#define MAX_ANGLE 84.375f
#define ANGLE_STEP 5.625f

#include "GameStateMsg.h"
#include "Physics.h"
#include "PlayerState.h"
#include "Point.h"
#include "Stream.h"
#include "Bullet.h"

enum class PlayerState { movingRight, movingLeft, still };

namespace Worms {
enum class Direction { right, left, up, down };

class Player: public Entity{
   public:
    Direction direction;
    explicit Player(Physics &physics, bool active);
    ~Player() = default;
    void update(float dt);
    bool isActive() const;
    float getAngle() const;
    void serialize(IO::Stream<IO::GameStateMsg> &s) const {}
    void setPosition(const Math::Point<float> &newPos);
    Math::Point<float> getPosition() const;
    void handleState(IO::PlayerInput pi);
    Worm::StateID getStateId() const;
    void setState(Worm::StateID stateID);
    void increaseAngle();
    void decreaseAngle();
    int getContactCount();
    void startContact();
    void endContact();
    void shoot(int shotPower);
    std::shared_ptr<Worms::Bullet> getBullet() const;

private:
    std::shared_ptr<Worms::State> state{nullptr};
    b2Body *body{nullptr};
    b2BodyDef bodyDef;
    b2PolygonShape shape;
    b2FixtureDef fixture;
    Physics &physics;
    std::shared_ptr<Worms::Bullet> bullet{nullptr};
    float angle{0};
    bool active{false};
    int numContacts{0};
    float width{0};
    float height{0};
};
}

#endif  //__PLAYER_H__
