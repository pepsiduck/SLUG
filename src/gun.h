#ifndef GUN_H
#define GUN_H

#include <inttypes.h>
#include <raylib.h>
#include <stdlib.h>
#include <math.h>

#include "animation.h"
#include "entity.h"

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

typedef struct SLUG_Gun SLUG_Gun;
struct SLUG_Gun
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

SLUG_Gun SLUG_DevShotgun(void);

#endif
