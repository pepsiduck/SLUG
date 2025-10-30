#ifndef ANIMATION_H
#define ANIMATION_H

#include <inttypes.h>
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct SLUG_Animation SLUG_Animation;
struct SLUG_Animation
{
	Texture2D sprite_sheet;
	
	uint16_t frame_count;
	float frame_dt;
	Rectangle curr_sprite;
	uint16_t curr_frame;
	
    int8_t playing;
    double time;
    
    Rectangle *bounding_box;
};

SLUG_Animation *SLUG_AnimationLoad(const char *loadAnim, Rectangle *bounding_box, uint16_t frame_count, float frame_dt);
SLUG_Animation *SLUG_AnimationHorizontalFlip(SLUG_Animation *anim, Rectangle *bounding_box);
void SLUG_AnimationUnload(SLUG_Animation *animation);

int8_t SLUG_AnimStartPlay(SLUG_Animation *anim);
int8_t SLUG_AnimStopPlay(SLUG_Animation *anim);

int8_t SLUG_AnimFrameUpdate(SLUG_Animation *anim);

#endif
