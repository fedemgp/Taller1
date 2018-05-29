/*
 *  Created by Rodrigo.
 *  date: 21/05/18
 */

#ifndef __PLAYER_END_BACKFLIP_H__
#define __PLAYER_END_BACKFLIP_H__

#include "PlayerState.h"

#define BACK_FLIP_LAND_TIME 0.4f

namespace Worms {
class EndBackFlip : public State {
   public:
    EndBackFlip();
    ~EndBackFlip() = default;
    void update(Player &p, float dt, b2Body *body) override;
    void moveRight(Player &p) override;
    void moveLeft(Player &p) override;
    void jump(Player &p) override;
    void backFlip(Player &p) override;
    void stopMove(Player &p) override;
    void bazooka(Player &p) override;
    void startShot(Player &p) override;
    void endShot(Player &p) override;
    void pointUp(Player &p) override;
    void pointDown(Player &p) override;

   private:
    float timeElapsed{0.0f};
};
}  // namespace Worms

#endif  //__PLAYER_END_BACKFLIP_H__