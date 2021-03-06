//
// Created by rodrigo on 10/06/18.
//

#ifndef INC_4_WORMS_STARTTURN_H
#define INC_4_WORMS_STARTTURN_H

#include "../../../libs/Observer.h"
#include "GameTurnState.h"

namespace Worms {
class StartTurn : public GameTurnState {
   public:
    StartTurn();
    ~StartTurn() = default;

    void endTurn(GameTurn &gt) override;
    void update(float dt) override;
    void wormHit(GameTurn &gt, uint8_t wormId) override;
    void wormEndHit(GameTurn &gt, uint8_t wormId) override;
    void wormDrowning(GameTurn &gt, uint8_t wormId) override;
    void wormDrowned(GameTurn &gt, uint8_t wormId) override;
    void explosion() override;
    void wormDisconnectedDying(uint8_t wormId) override;
    void wormDisconnectedDead(uint8_t wormId) override;
};
}

#endif  // INC_4_WORMS_STARTTURN_H
