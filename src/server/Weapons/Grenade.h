/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 03/06/18
 */

#ifndef __GRENADE_H__
#define __GRENADE_H__

#include "Weapon.h"

namespace Weapon {
class Grenade : public Worms::Weapon {
   public:
    Grenade(float angle);
    ~Grenade() override = default;
    void update(float dt) override;
    void startShot(Worms::Player *player) override;
    void endShot() override;
    void setTimeout(uint8_t time) override;
    std::list<Worms::Bullet> onExplode(const Worms::Bullet &bullet,
                                       Worms::Physics &physics) override;
    void positionSelected(Worms::Player &p, Math::Point<float> point) override;

   private:
    float powerChargeTime{0.0f};
};
}  // namespace Weapon

#endif  //__GRENADE_H__
