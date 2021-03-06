#ifndef GAME_TEXTURES_H_
#define GAME_TEXTURES_H_

#include "TextureManager.h"
#include "utils.h"

namespace GUI {
/** Different kinds of textures. */
enum class GameTextures {
    WormWalk,
    WormIdle,
    LongGirder,
    ShortGirder,
    StartJump,
    Jumping,
    EndJump,
    BackFlipping,
    Bazooka,
    Missile,
    Fly,
    Die,
    Dead,
    Sliding,
    StaticBackground,
    Background1,
    Background2,
    Background3,
    WormGrenade,
    Grenade,
    WormCluster,
    Cluster,
    Mortar,
    Bazooka2,
    WormBanana,
    Banana,
    WormHoly,
    Holy,
    Explosion,
    Flame,
    Smoke,
    Falling,
    Scope,
    PowerBar,
    Fragment,
    BazookaIcon,
    GrenadeIcon,
    ClusterIcon,
    MortarIcon,
    BananaIcon,
    HolyIcon,
    WormAirAttack,
    AirMissile,
    AirIcon,
    WormDynamite,
    Dynamite,
    DynamiteIcon,
    WormTeleport,
    WormTeleporting,
    TeleportIcon,
    WormBaseballBat,
    WormBaseballBatting,
    BaseballBatIcon,
    WindLeft,
    WindRight,
    CurrentPlayerArrow,
    Water,
};

/** Specialized TextureManager class. */
using GameTextureManager = TextureManager<GameTextures, Utils::EnumClassHash>;
}  // namespace GUI

#endif
