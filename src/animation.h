#ifndef ANIMATION_H
#define ANIMATION_H

#include <inttypes.h>
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct SLUG_Animation SLUG_Animation;
struct SLUG_Animation
{
	Texture2D sprite_sheet;
	Rectangle curr_sprite;

	Rectangle bounding_box;
	uint16_t frame_count;
	uint16_t curr_frame;
	float frame_dt;
	
	float *dt_tab;
	float *frame_tab;

    int8_t playing;
    double time;
};

SLUG_Animation *SLUG_AnimationLoad(const char *loadAnim, Rectangle bounding_box, uint16_t frame_count, float frame_dt, float *dt_tab, float *frame_tab);
void SLUG_AnimationUnload(SLUG_Animation *animation);

int8_t SLUG_AnimStartPlay(SLUG_Animation *anim);
int8_t SLUG_AnimStopPlay(SLUG_Animation *anim);

int8_t SLUG_AnimUpdate(SLUG_Animation *anim);

#endif
