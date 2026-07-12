#include "map.h"
#include "defines.h"

SLUG_Map* SLUG_LoadMapDev()
{
    SLUG_Map *map = (SLUG_Map*) malloc(sizeof(SLUG_Map));
    if(map == NULL)
    {
        printf("Malloc error\n");
        return NULL;
    }

    char buffer[256];
    
    map->loaded_sprites_nb = 1;
    map->fixed_sprites = (Texture2D *) malloc(sizeof(Texture2D));
    map->fixed_sprites[0] = LoadTexture(SLUG_GetFilePath("assets/dev_map.jpg",buffer));

    map->sprite_nb = 1;
    map->sprites = (SLUG_PlacableSprite *) malloc(sizeof(SLUG_PlacableSprite));
    map->sprites[0] = (SLUG_PlacableSprite) {
        .sprite_index = 0,
        .zone = (Rectangle) {
            .x = 0,
            .y = 0,
            .width = 4011.0f,
            .height = 3330.0f
        }
    };

    map->w = 4011;
    map->h = 3330;
    map->player_BSP = SLUG_LoadBSPTreeDev();
    return map;
}

SLUG_Map* SLUG_LoadMap(const char *loadMap)
{
    if(loadMap == NULL)
    {
        printf("no filepath bruh\n");
        return NULL;
    }

    uint32_t len = strlen(loadMap);
    if(len == 0)
        return NULL;

    SLUG_Map *map = (SLUG_Map*) malloc(sizeof(SLUG_Map));
    if(map == NULL)
    {
        printf("Malloc error\n");
        return NULL;
    }
    map->fixed_sprites = NULL;
    map->loaded_sprites_nb = 0;
    map->sprites = NULL;
    map->sprite_nb = 0;
    map->player_BSP = NULL;

    //load sprites

    map->fixed_sprites = (Texture2D *) malloc(MAX_SPRITES * sizeof(Texture2D));
    if(map->fixed_sprites == NULL)
    {
        printf("Malloc error.\n");
        SLUG_MapUnload(map);
        map = NULL  ;
        return NULL;
    }

    char sprite_file_name[len + 32];
    sprintf(sprite_file_name,"%s/assets/sprites/sprite_names.txt",loadMap);
    FILE *sprite_file = fopen(sprite_file_name,"r");
    if(sprite_file == NULL)
    {
        printf("No sprite name file.\n");
        SLUG_MapUnload(map);
        map = NULL;
        return NULL;
    }

    char line[MAX_MAP_CHAR];
    char sprite_name[271 + len];
    int16_t counter = 0;
    while(counter < MAX_SPRITES && fgets(line, sizeof(line), sprite_file))
    {   
        if(line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';

        if(strlen(line) > 0)
        {
            sprintf(sprite_name,"%s/assets/sprites/%s",loadMap,line);
            map->fixed_sprites[counter] = LoadTexture(sprite_name);
            if(map->fixed_sprites[counter].id <= 0)
            {
                printf("Warning : incorrect sprite file name.\n");
                map->fixed_sprites[counter] = LoadTexture("assets/sprites/missing.jpg");
            }
        }
        
        counter++;
    }
    map->loaded_sprites_nb = counter;

    map->fixed_sprites = (Texture2D *) realloc(map->fixed_sprites, counter*sizeof(Texture2D));
    if(map->fixed_sprites == NULL)
    {
        printf("Realloc error.\n");
        SLUG_MapUnload(map);
        map = NULL  ;
        return NULL;
    }

    //load file
    char mapslug[len + 10];
    strcpy(mapslug, loadMap);
    strcat(mapslug, "/map.slug");
    FILE *f = fopen(mapslug, "r");
    if(f == NULL)
    {
        printf("Error while loading file.\n");
        SLUG_MapUnload(map);
        map = NULL;
        return NULL;
    }

    //signature test
    unsigned char signature[13];
    if(fread((void *) signature, sizeof(unsigned char), 13, f) != 13)
    {
        printf("File incomplete or error.\n");
        SLUG_MapUnload(map);
        map = NULL;
        return NULL;
    }
    unsigned char test[13] = {0x53, 0x4C, 0x55, 0x47, 0x45, 0x58, 0x50, 0x4F, 0x52, 0x54, 0x4D, 0x41, 0x50};
    if(memcmp(signature, test, 13) != 0)
    {
        printf("File signature is wrong.\n");
        SLUG_MapUnload(map);
        map = NULL;
        return NULL;
    }

    //map size
    if(fread((void *) &(map->w), sizeof(uint32_t), 1, f) != 1)
    {
        printf("File incomplete or error.\n");
        SLUG_MapUnload(map);
        map = NULL;
        return NULL;
    }

    if(fread((void *) &(map->h), sizeof(uint32_t), 1, f) != 1)
    {
        printf("File incomplete or error.\n");
        SLUG_MapUnload(map);
        map = NULL;
        return NULL;
    }
    
    //sprite rects
    if(fread((void *) &(map->sprite_nb), sizeof(int16_t), 1, f) != 1)
    {
        printf("File incomplete or error.\n");
        SLUG_MapUnload(map);
        map = NULL;
        return NULL;
    }

    if(map->sprite_nb > 0)
	{
        map->sprites = (SLUG_PlacableSprite *) malloc(map->sprite_nb * sizeof(SLUG_PlacableSprite));
        if(fread((void *) map->sprites, sizeof(SLUG_PlacableSprite), map->sprite_nb, f) != map->sprite_nb)
        {
            printf("File incomplete or error.\n");
            SLUG_MapUnload(map);
            map = NULL;
            return NULL;
        }
    }

    //walls
    size_t s;
    if(fread((void *) &s, sizeof(size_t), 1, f) != 1)
    {
        printf("File incomplete or error.\n");
        SLUG_MapUnload(map);
        map = NULL;
        return NULL;
    }

    if(s > 0)
    {
        map->player_BSP = (SLUG_BSPTree *) malloc(sizeof(SLUG_BSPTree));
        if(map->player_BSP == NULL)
        {
            printf("Malloc error\n");
            SLUG_MapUnload(map);
            map = NULL;
            return NULL;
        }
        
        if(fread((void *) &map->player_BSP->tab_size, sizeof(int32_t), 1, f) != 1)
        {
            printf("File incomplete or error.\n");
            SLUG_MapUnload(map);
            map = NULL;
            return NULL;
        }

        if(map->player_BSP->tab_size <= 0)
        {
            printf("WTF there is no walls ????\n");
            SLUG_MapUnload(map);
            map = NULL;
            return NULL;
        }

        map->player_BSP->elements_passed = malloc(((map->player_BSP->tab_size / 8) + (map->player_BSP->tab_size % 8 != 0)) * sizeof(uint8_t));
        if(map->player_BSP->elements_passed == NULL)
        {
            printf("Malloc error\n");
            SLUG_MapUnload(map);
            map = NULL;
            return NULL;
        }
        for(uint32_t i = 0; i < (map->player_BSP->tab_size >> 3) + ((map->player_BSP->tab_size & 7) != 0); ++i)
            map->player_BSP->elements_passed[i] = 0;

        map->player_BSP->tab = (SLUG_SegmentExtended *) malloc(map->player_BSP->tab_size * sizeof(SLUG_SegmentExtended));
        if(map->player_BSP->tab == NULL)
        {
            printf("Malloc error\n");
            SLUG_MapUnload(map);
            map = NULL;
            return NULL;
        }

        if(fread((void *) map->player_BSP->tab, sizeof(SLUG_SegmentExtended), map->player_BSP->tab_size, f) != map->player_BSP->tab_size)
        {
            printf("File incomplete or error.\n");
            SLUG_MapUnload(map);
            map = NULL;
            return NULL;
        }

        if(fread((void *) &map->player_BSP->elements_size, sizeof(int32_t), 1, f) != 1)
        {
            printf("File incomplete or error.\n");
            SLUG_MapUnload(map);
            map = NULL;
            return NULL;
        }
        
        if(map->player_BSP->elements_size <= 0)
        {
            printf("Wtf you have walls but no BSP Tree structure ???\n");
            SLUG_MapUnload(map);
            map = NULL;
            return NULL;
        }

        map->player_BSP->elements = (SLUG_BSPTreeElement *) malloc(map->player_BSP->elements_size * sizeof(SLUG_BSPTreeElement));
        if(map->player_BSP->elements == NULL)
        {
            printf("Malloc error\n");
            SLUG_MapUnload(map);
            map = NULL;
            return NULL;
        }    
        
        if(fread((void *) map->player_BSP->elements, sizeof(SLUG_BSPTreeElement), map->player_BSP->elements_size, f) != map->player_BSP->elements_size)
        {
            printf("File incomplete or error.\n");
            SLUG_MapUnload(map);
            map = NULL;
            return NULL;
        }

    }
    else
        map->player_BSP = NULL;

    if(fread((void *) &map->player_spawn, sizeof(Vector2), 1, f) != 1)
    {
        printf("File incomplete or error.\n");
        SLUG_MapUnload(map);
        map = NULL;
        return NULL;
    }

    return map;
}

void SLUG_MapUnload(SLUG_Map *map)
{
    if(map != NULL)
    {
        if(map->fixed_sprites != NULL)
        {
            for(int16_t i = 0; i < map->loaded_sprites_nb; ++i)
                UnloadTexture(map->fixed_sprites[i]);

            free(map->fixed_sprites);
        }

        if(map->sprites != NULL)
            free(map->sprites);        


        SLUG_BSTTreeUnload(map->player_BSP);
        free(map);
    }
}


