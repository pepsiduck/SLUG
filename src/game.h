#ifndef GAME_H
#define GAME_H

#include <inttypes.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include <stdio.h>

#include "map.h"
#include "player.h"
#include "defines.h"

int8_t SLUG_PlayerMove(SLUG_Player *player, SLUG_Map *map);

#endif
