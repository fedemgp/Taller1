/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */
#ifndef __GAME_STATE_MSG_H__
#define __GAME_STATE_MSG_H__

#define WORMS_QUANTITY 20

#include <stdint.h>

namespace Worm {
enum class StateID {
    Walk,
    Still,
    StartJump,
    Jumping,
    EndJump,
    StartBackFlip,
    BackFlipping,
    EndBackFlip,
    Hit,
    Die,
    Dead,
    Drown
};
enum WeaponID { WNone, WBazooka };
}  // namespace Worm

namespace IO {
enum class PlayerInput {
    moveNone,
    moveRight,
    moveLeft,
    startJump,
    stopMove,
    startBackFlip,
    bazooka,
    pointUp,
    pointDown,
    startShot,
    endShot
};
// TODO protocol?
struct GameStateMsg {
    uint8_t elapsedTurnSeconds;
    uint8_t currentWorm;
    uint8_t num_worms;
    float wormsHealth[WORMS_QUANTITY];
    float positions[WORMS_QUANTITY * 2];
    Worm::StateID stateIDs[WORMS_QUANTITY];
    Worm::WeaponID activePlayerWeapon;
    float activePlayerAngle;
    bool shoot;
    float bullet[2];
    float bulletAngle;
    bool processingInputs;
    float currentPlayerTurnTime;
};
}  // namespace IO

#endif  //__GAME_STATE_MSG_H__
