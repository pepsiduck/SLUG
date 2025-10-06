#ifndef ANIMATION_H
#define ANIMATION_H

#include <inttypes.h>
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct SLUG_Animation SLUG_Animation;
struct Animation
{
	Texture2D sprite_sheet;
	Rectangle curr_sprite;

	Rectangle bounding_box;
	uint16_t frame_count;
	uint16_t curr_frame;
	float dt;
	
	float *dt_tab;
	float *frame_tab;
};

SLUG_Animation *SLUG_AnimationLoad(const char *loadAnim, Rectangle bounding_box, float *dt_tab, float *frame_tab);
void SLUG_AnimationUnload(SLUG_Animation *animation);

#endif
