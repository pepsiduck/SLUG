#include "animation.h"
#include "defines.h"

SLUG_Animation *SLUG_AnimationLoad(const char *loadAnim, Rectangle *bounding_box, uint16_t frame_count, float frame_dt)
{
	SLUG_Animation *anim = (SLUG_Animation *) malloc(sizeof(SLUG_Animation));
	if(anim == NULL)
		return NULL;
	
	anim->sprite_sheet = LoadTexture(loadAnim);
    if(anim->sprite_sheet.id <= 0)
    {
        printf("Error while loading animation.\n");
        free(anim);
        return NULL;
    }
	
    anim->bounding_box = bounding_box;
    anim->frame_count = frame_count;
	anim->curr_frame = 0;
	anim->frame_dt = frame_dt;
    anim->playing = 0;
    anim->time = 0;

	anim->curr_sprite.x = 0;
    anim->curr_sprite.y = 0;
    anim->curr_sprite.height = anim->sprite_sheet.height;
    anim->curr_sprite.width = (float) anim->sprite_sheet.width / (float) frame_count;
    
	return anim;
}

void SLUG_AnimationUnload(SLUG_Animation *animation)
{
	if(animation != NULL)
	{		
		UnloadTexture(animation->sprite_sheet);
		
		free(animation);		
	}
}

int8_t SLUG_AnimStartPlay(SLUG_Animation *anim)
{
    if(anim == NULL)
        return -1;
    
    if(anim->frame_count > 1)
    {
		anim->time = 0;
		anim->curr_sprite.x = 0;
		anim->curr_sprite.y = 0;
		anim->curr_frame = 0;
    }
    
    anim->playing = 1;

    return 0;
}

int8_t SLUG_AnimStopPlay(SLUG_Animation *anim)
{
    if(anim == NULL)
        return -1;
    
    if(anim->frame_count > 1)
    {
		anim->time = 0;
		anim->curr_sprite.x = 0;
		anim->curr_sprite.y = 0;
		anim->curr_frame = 0;
    }
    
    anim->playing = 0;

    return 0;
}

int8_t SLUG_AnimFrameUpdate(SLUG_Animation *anim)
{
    if(anim == NULL)
        return -1;
    
    if(anim->frame_count == 1)
    	return 0;
    
    if(anim->playing)
    {
        anim->time += dt;
        anim->curr_sprite.x = anim->curr_sprite.width * ((uint16_t) (floor(anim->time / anim->frame_dt)) % anim->frame_count);
    }

    return 0;
}
