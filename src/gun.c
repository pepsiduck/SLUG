#include "gun.h"

SLUG_HitscanGun SLUG_DevShotgun(void)
{
    SLUG_HitscanGun gun;

    gun.hitscan = (SLUG_Hitscan) {

        .nb = 10,
        .dmg = 9,
        .pierce = false,
        .range = 1000.0f,
        .fall_off_factor = logf(0.33333f) / 1000.0f,
        .spread_range = 400.0f,
        .random_spread = false
    };

    gun.firing_time = 0.625f;
    gun.reload_time = 0.51f;

    gun.time_last_fire = -1.f * gun.firing_time;
    gun.time_last_reloaded = -1.f * gun.reload_time;

    gun.clip = 6;
    gun.clip_max = 6;
    gun.reserve = 36;
    gun.reserve_max = 36;
    gun.shoot_sfx = NULL;
    gun.reload_sfx = NULL;
    gun.muzzle_flash = NULL;

    return gun;
}
