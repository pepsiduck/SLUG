#include "animation.h"

SLUG_Animation *SLUG_AnimationLoad(const char *loadAnim, Rectangle bounding_box, uint16_t frame_count, float frame_dt, float *dt_tab, float *frame_tab);
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
	anim->dt_tab = dt_tab;
	anim->frame_tab = frame_tab;
    anim->playing = 0;
    anim->time = 0;

    anim->curr_sprite.h = anim->sprite_sheet.h;
    anim->curr_sprite.w = anim->sprite_sheet.w / frame_count;
    anim->curr_sprite.x = 0;
    anim->curr_sprite.y = 0;
    
	return anim;
}

void SLUG_AnimationUnload(SLUG_Animation *animation)
{
	if(animation != NULL)
	{
		if(animation->dt_tab != NULL)
			free(animation->dt_tab);
		if(animation->frame_tab != NULL)
			free(animation->frame_tab);
		
		UnloadTexture(animation->sprite_sheet);
		
		free(anim);		
	}
}

int8_t SLUG_AnimStartPlay(SLUG_Animation *anim)
{
    if(anim == NULL)
        return -1;
    
    anim->time = GetTime();
    anim->curr_sprite.x = 0;
    anim->curr_sprite.y = 0;

    anim->curr_frame = 0;
    
    anim->playing = 1;

    return 0;
}

int8_t SLUG_AnimStopPlay(SLUG_Animation *anim)
{
    if(anim == NULL)
        return -1;
    
    anim->time = 0;
    anim->curr_sprite.x = 0;
    anim->curr_sprite.y = 0;

    anim->curr_frame = 0;
    
    anim->playing = 0;

    return 0;
}

int8_t SLUG_AnimUpdate(SLUG_Animation *anim)
{
    if(anim == NULL)
        return -1;
    
    if(anim->playing)
    {
        
    }

    return 0;
}
