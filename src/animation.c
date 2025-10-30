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
    anim->curr_sprite.width = (float) anim->sprite_sheet.width / (float) frame_count;
    anim->curr_sprite.height = anim->sprite_sheet.height;
    
	return anim;
}

SLUG_Animation *SLUG_AnimationHorizontalFlip(SLUG_Animation *anim, Rectangle *bounding_box)
{
    if(anim == NULL)
        return NULL;

    if(anim->sprite_sheet.id <= 0)
    {
        printf("Argument does not have a valid spritesheet\n");
        return NULL;
    }

    SLUG_Animation *new_anim = (SLUG_Animation *) malloc(sizeof(SLUG_Animation));
    if(new_anim == NULL)
        return NULL;

    new_anim->bounding_box = bounding_box;
    new_anim->frame_count = anim->frame_count;
    new_anim->curr_frame = 0;
    new_anim->frame_dt = anim->frame_dt;
    new_anim->playing = 0;
    new_anim->time = 0;

	new_anim->curr_sprite.x = 0;
    new_anim->curr_sprite.y = 0;
    new_anim->curr_sprite.width = anim->curr_sprite.width;
    new_anim->curr_sprite.height = anim->curr_sprite.height;
    
    Image sprite_sheet = LoadImageFromTexture(anim->sprite_sheet); 
    Image new_sprite_sheet = GenImageColor(sprite_sheet.width, sprite_sheet.height, BLANK);
    Image buffer;
    for(uint16_t i = 0; i < anim->frame_count; ++i)
    {
        buffer = ImageFromImage(sprite_sheet, (Rectangle) {.x = i * anim->curr_sprite.width, .y = 0, .width = anim->curr_sprite.width, .height = anim->curr_sprite.height});
        ImageFlipHorizontal(&buffer);
        ImageDraw(&new_sprite_sheet, buffer, 
            (Rectangle) {.x = 0, .y = 0, .width = anim->curr_sprite.width, .height = anim->curr_sprite.height}, 
            (Rectangle) {.x = i * anim->curr_sprite.width, .y = 0, .width = anim->curr_sprite.width, .height = anim->curr_sprite.height}, 
            WHITE);
        UnloadImage(buffer);
    }

    new_anim->sprite_sheet = LoadTextureFromImage(new_sprite_sheet);
    
    UnloadImage(sprite_sheet);
    UnloadImage(new_sprite_sheet);
    
    return new_anim;
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
