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
    map->fixed_sprite = LoadTexture("assets/dev_map.jpg");
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

    char fixed_sprite[len + 37];
    strcpy(fixed_sprite, loadMap);
    strcat(fixed_sprite, "/assets/sprites/map_fixed_sprite.png");
    map->fixed_sprite = LoadTexture(fixed_sprite);
    if(map->fixed_sprite.id <= 0)
    {
        printf("Error while loading map sprite.\n");
        SLUG_MapUnload(map);
        map = NULL;
        return NULL;
    }
    SetTextureWrap(map->fixed_sprite, 1);
    map->w = (uint32_t) map->fixed_sprite.width;
    map->h = (uint32_t) map->fixed_sprite.height;

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

    unsigned char signature[7];
    if(fread((void *) signature, sizeof(unsigned char), 7, f) != 7)
    {
        printf("File incomplete or error.\n");
        SLUG_MapUnload(map);
        map = NULL;
        return NULL;
    }
    unsigned char test[7] = {0x53, 0x4C, 0x55, 0x47, 0x4D, 0x41, 0x50};
    if(memcmp(signature, test, 7) != 0)
    {
        printf("File signature is wrong.\n");
        SLUG_MapUnload(map);
        map = NULL;
        return NULL;
    }

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

        int32_t garbage;
        for(int32_t i = 0; i < map->player_BSP->tab_size; ++i)
        {
            if(fread((void *) &garbage, sizeof(int32_t), 1, f) != 1)
            {
                printf("File incomplete or error.\n");
                SLUG_MapUnload(map);
                map = NULL;
                return NULL;
            }
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
        UnloadTexture(map->fixed_sprite);
        SLUG_BSTTreeUnload(map->player_BSP);
        free(map);
    }
}


