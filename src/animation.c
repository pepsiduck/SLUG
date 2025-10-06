#include "animation.h"

SLUG_Animation *SLUG_AnimationLoad(const char *loadAnim, Rectangle bounding_box, float *dt_tab, float *frame_tab)
{
	SLUG_Animation *anim = (SLUG_Animation *) malloc(sizeof(SLUG_Animation));
	if(anim == NULL)
		return NULL;
	
	
	
	return anim
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
