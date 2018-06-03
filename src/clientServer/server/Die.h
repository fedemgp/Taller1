/*
 *  Created by Rodrigo.
 *  date: 28/05/18
 */

#ifndef __DIE_H__
#define __DIE_H__

#include "Config.h"
#include "PlayerState.h"

namespace Worms {
class Die : public State {
   public:
    Die();
    ~Die() = default;
    void update(Player &p, float dt, b2Body *body) override;
    void moveRight(Player &p) override;
    void moveLeft(Player &p) override;
    void jump(Player &p) override;
    void backFlip(Player &p) override;
    void stopMove(Player &p) override;

    void bazooka(Player &p) override;
    void grenade(Player &p) override;

    void startShot(Player &p) override;
    void endShot(Player &p) override;
    void pointUp(Player &p) override;
    void pointDown(Player &p) override;

private:
    float timeElapsed{0.0f};
    float dyingTime{Game::Config::getInstance().getDyingTime()};
};
}  // namespace Worms

#endif  //__DIE_H__
