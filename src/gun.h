#ifndef GUN_H
#define GUN_H

#include <inttypes.h>
#include <raylib.h>
#include <stdlib.h>
#include <math.h>

#include "animation.h"
#include "entity.h"

//hitscan
typedef struct SLUG_Hitscan SLUG_Hitscan;
struct SLUG_Hitscan
{
    uint8_t nb;

    uint32_t dmg;
    uint8_t  pierce;

    float range;
    float fall_off_factor;

    float spread_range;
    bool  random_spread;
    
};

typedef struct SLUG_HitscanGun SLUG_HitscanGun;
struct SLUG_HitscanGun
{
    SLUG_Hitscan hitscan;

    float firing_time; //time between 2 shots
    float reload_time; //time to reload a clip
    float time_last_fire;
    float time_last_reloaded;

    int16_t clip;
    int16_t clip_max;

    int16_t reserve;
    int16_t reserve_max;

    Sound *shoot_sfx;
    Sound *reload_sfx;

    SLUG_Animation *muzzle_flash;

};

SLUG_HitscanGun SLUG_DevShotgun(void);

//Explosion
typedef struct SLUG_Explosion SLUG_Explosion;
struct SLUG_Explosion
{
    Vector3 position;
    float radius;
    
    uint32_t dmg;
    float fall_off_factor;
};

//projectiles
typedef struct SLUG_Projectile SLUG_Projectile;
struct SLUG_Projectile
{
    Vector3 speed;
    bool gravity_affected;
    
    uint32_t dmg;
    float fall_off_factor;
    float fall_off_max_distance;
	
	uint32_t sprite_id;
};

typedef struct SLUG_ProjectileEntity SLUG_ProjectileEntity;
struct SLUG_ProjectileEntity
{
	SLUG_Entity e;
	
	Vector2 position;
	Vector3 speed;
	bool gravity_affected;
	
	uint32_t dmg;
	uint8_t team;
    float fall_off_factor;
    float fall_off_max_distance;
	
	uint32_t sprite_id;
}

typedef struct SLUG_ProjectileGun SLUG_ProjectileGun;
struct SLUG_ProjectileGun
{
    SLUG_Projectile projectile;

    float firing_time; //time between 2 shots
    float reload_time; //time to reload a clip
    float time_last_fire;
    float time_last_reloaded;

    int16_t clip;
    int16_t clip_max;

    int16_t reserve;
    int16_t reserve_max;

    Sound *shoot_sfx;
    Sound *reload_sfx;

    SLUG_Animation *muzzle_flash;

};


//Weapon
typedef enum {SLUG_WEAPON_HITSCAN, 
              SLUG_WEAPON_PROJECTILE,
              SLUG_WEAPON_MELEE,
              SLUG_WEAPON_NUMBER} SLUG_WeaponType;
              
typedef struct SLUG_Weapon SLUG_Weapon;
struct SLUG_Weapon
{
    SLUG_WeaponType type;
    void *weapon;
};
#endif
