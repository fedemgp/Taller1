/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 01/06/18
 */

#ifndef __GAMECONSTANTS_H__
#define __GAMECONSTANTS_H__
// Wind
#define MIN_WIND_INTENSITY 0.2f
#define MAX_WIND_INTENSITY 10.0f
// Jumping
#define START_JUMP_TIME 0.6f
#define JUMP_LAND_TIME 0.3f
#define JUMP_VEL_X 4.0f
#define JUMP_VEL_Y 7.0f
#define BACKFLIP_VEL_X (-1.2f)
#define BACKFLIP_VEL_Y 9.4f
// Moving
#define WALK_VELOCITY 3.0f
// Stage and general game config
#define TURN_TIME 10
#define EXTRA_TURN_TIME 3
#define WAIT_FOR_NEXT_TURN_TIME 3.0f
#define NUM_TEAMS 2
#define GAME_HEIGHT 30.0f
#define GAME_WIDTH 30.0f
#define DYING_TIME 2.6f
#define DROWNING_TIME 1.0f
#define TELEPORT_TIME 2.0f
#define WATER_LEVEL (-2)
#define WORM_HEALTH 100
#define POWER_CHARGE_MAX_TIME 1.0f
// Weapons
#define IMPULSE_DAMPING_RATIO 0.4f
// Bazooka
#define BAZOOKA_DAMAGE 50
#define BAZOOKA_DAMAGE_RADIUS 2.0f
#define BAZOOKA_MIN_ANGLE -90
#define BAZOOKA_MAX_ANGLE 84.375f
#define BAZOOKA_RESTITUTION 0.1f
#define BAZOOKA_FRICTION 0.0f
#define BAZOOKA_INITIAL_TIMEOUT 0
#define BAZOOKA_BULLET_RADIUS 0.5f
#define BAZOOKA_DAMPING_RATIO 1.0f
// Grenade
#define GRENADE_DAMAGE 30
#define GRENADE_RADIUS 2.0f
#define GRENADE_MIN_ANGLE -84.375f
#define GRENADE_MAX_ANGLE 90
#define GRENADE_RESTITUTION 0.4f
#define GRENADE_FRICTION 0.4f
#define GRENADE_INITIAL_TIMEOUT 5
#define GRENADE_BULLET_RADIUS 0.5f
#define GRENADE_DAMPING_RATIO 1.0f
// Cluster
#define CLUSTER_DAMAGE 30
#define CLUSTER_RADIUS 2.0f
#define CLUSTER_MIN_ANGLE -84.375f
#define CLUSTER_MAX_ANGLE 90
#define CLUSTER_RESTITUTION 0.3f
#define CLUSTER_FRICTION 0.4f
#define CLUSTER_INITIAL_TIMEOUT 5
#define CLUSTER_BULLET_RADIUS 0.5f
#define CLUSTER_DAMPING_RATIO 1.0f
// Cluster's fragments
#define CLUSTER_FRAGMENT_DAMAGE 10
#define CLUSTER_FRAGMENT_RADIUS 2.0f
#define CLUSTER_FRAGMENT_MIN_ANGLE 40
#define CLUSTER_FRAGMENT_MAX_ANGLE 140
#define CLUSTER_FRAGMENT_RESTITUTION 0.1f
#define CLUSTER_FRAGMENT_FRICTION 0.1f
#define CLUSTER_FRAGMENT_TIMEOUT 0
#define CLUSTER_FRAGMENT_ANGLE_STEP 20.0f
#define CLUSTER_FRAGMENT_SHOT_POWER 50
#define CLUSTER_FRAGMENT_QUANTITY 6
#define CLUSTER_FRAGMENT_BULLET_RADIUS 0.1f
#define CLUSTER_FRAGMENT_DAMPING_RATIO 0.1f
// Mortar's fragments
#define MORTAR_FRAGMENT_DAMAGE 10
#define MORTAR_FRAGMENT_RADIUS 2.0f
#define MORTAR_FRAGMENT_MIN_ANGLE 40
#define MORTAR_FRAGMENT_MAX_ANGLE 140
#define MORTAR_FRAGMENT_RESTITUTION 0.1f
#define MORTAR_FRAGMENT_FRICTION 0.1f
#define MORTAR_FRAGMENT_TIMEOUT 0
#define MORTAR_FRAGMENT_ANGLE_STEP 20.0f
#define MORTAR_FRAGMENT_SHOT_POWER 50
#define MORTAR_FRAGMENT_QUANTITY 6
#define MORTAR_FRAGMENT_BULLET_RADIUS 0.1f
#define MORTAR_FRAGMENT_DAMPING_RATIO 0.1f
// Mortar
#define MORTAR_DAMAGE 50
#define MORTAR_RADIUS 2.0f
#define MORTAR_MIN_ANGLE -90
#define MORTAR_MAX_ANGLE 84.375f
#define MORTAR_RESTITUTION 0.1f
#define MORTAR_FRICTION 0.0f
#define MORTAR_INITIAL_TIMEOUT 0
#define MORTAR_BULLET_RADIUS 0.5f
#define MORTAR_DAMPING_RATIO 1.0f
// Mortar
#define BANANA_DAMAGE 70
#define BANANA_RADIUS 4.0f
#define BANANA_MIN_ANGLE -78.75f
#define BANANA_MAX_ANGLE 95.625f
#define BANANA_RESTITUTION 1.1f
#define BANANA_FRICTION 0.2f
#define BANANA_INITIAL_TIMEOUT 5
#define BANANA_BULLET_RADIUS 0.5f
#define BANANA_DAMPING_RATIO 1.0f
// Grenade
#define HOLY_DAMAGE 110
#define HOLY_RADIUS 8.0f
#define HOLY_MIN_ANGLE -84.375f
#define HOLY_MAX_ANGLE 90
#define HOLY_RESTITUTION 0.1f
#define HOLY_FRICTION 0.4f
#define HOLY_INITIAL_TIMEOUT 5
#define HOLY_BULLET_RADIUS 0.5f
#define HOLY_DAMPING_RATIO 1.0f
// AerialAttack
#define AERIAL_ATTACK_DAMAGE 40
#define AERIAL_ATTACK_RADIUS 2.0f
#define AERIAL_ATTACK_MIN_ANGLE 0.0f
#define AERIAL_ATTACK_MAX_ANGLE 0.0f
#define AERIAL_ATTACK_RESTITUTION 0.1f
#define AERIAL_ATTACK_FRICTION 0.0f
#define AERIAL_ATTACK_TIMEOUT 0
#define AERIAL_ATTACK_BULLET_RADIUS 0.5f
#define AERIAL_ATTACK_DAMPING_RATIO 1.0f
#define AERIAL_ATTACK_ANGLE_STEP 0.0f
#define AERIAL_ATTACK_SHOT_POWER 0
#define AERIAL_ATTACK_MISSILE_QUANTITY 6
#define AERIAL_ATTACK_MISSILE_SEPARATION 2.0f
#define AERIAL_ATTACK_LAUNCH_HEIGHT 60.0f
// Dynamite
#define DYNAMITE_DAMAGE 50
#define DYNAMITE_RADIUS 4.0f
#define DYNAMITE_MIN_ANGLE 0.0f
#define DYNAMITE_MAX_ANGLE 0.0f
#define DYNAMITE_ANGLE_STEP 0.0f
#define DYNAMITE_RESTITUTION 0.0f
#define DYNAMITE_FRICTION 0.0f
#define DYNAMITE_INITIAL_TIMEOUT 5
#define DYNAMITE_BULLET_RADIUS 0.5f
#define DYNAMITE_DAMPING_RATIO 1.0f
#define DYNAMITE_MAX_SHOT_POWER 1
// Baseball Bat
#define BASEBALL_BAT_DAMAGE 10
#define BASEBALL_BAT_DAMAGE_RADIUS 2.0f
#define BASEBALL_BAT_MIN_ANGLE -90
#define BASEBALL_BAT_MAX_ANGLE 84.375f
#define BASEBALL_BAT_RESTITUTION 0.1f
#define BASEBALL_BAT_FRICTION 0.0f
#define BASEBALL_BAT_INITIAL_TIMEOUT 0
#define BASEBALL_BAT_BULLET_RADIUS 0.5f
#define BASEBALL_BAT_DAMPING_RATIO 1.0f
#define BASEBALL_IMPULSE_DAMPING_RATIO 1.0f

#define ANGLE_STEP 5.625f
#define MAX_SHOT_POWER 50

#endif  //__GAMECONSTANTS_H__
