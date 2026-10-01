#ifndef DISPLAY_H
#define DISPLAY_H

#include <inttypes.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include <stdio.h>

#include "player.h"
#include "animation.h"
#include "map.h"
#include "camera.h"

//!Display
int8_t SLUG_DisplaySprite(SLUG_Camera *cam, Texture2D *sprite, Rectangle *sprite_box);
int8_t SLUG_DisplayAnim(SLUG_Camera *cam, SLUG_Animation *anim);
int8_t SLUG_DisplayPlayerAim(SLUG_Camera *cam, SLUG_PlayerAim *aim);
int8_t SLUG_DisplayPlayer(SLUG_Camera *cam, SLUG_Player *player);

int8_t SLUG_Display(SLUG_Camera *cam); // ptet autre part après et avec d'autres arguments

#endif
