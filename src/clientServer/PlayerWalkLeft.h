#ifndef _PLAYERWALKLEFT_H
#define _PLAYERWALKLEFT_H


#include "PlayerState.h"

namespace Worms {
    class WalkLeft : public State {
        float update() override;
        void moveRight(Player &p) override;
        void moveLeft(Player &p) override;
        void jumpRight(Player &p) override;
        void jumpLeft(Player &p) override;
        void stopMove(Player &p) override;
    };
}


#endif //_PLAYERWALKLEFT_H
