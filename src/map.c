#include "map.h"

SLUG_BSPTree* SLUG_LoadBSPTreeDev()
{
    SLUG_BSPTree *tree = (SLUG_BSPTree *) malloc(sizeof(SLUG_BSPTree));
    if(tree == NULL)
        return NULL;
    tree->tab_size = 12;
    tree->tab = (SLUG_SegmentExtended *) malloc(tree->tab_size * sizeof(SLUG_SegmentExtended));
    if(tree->tab == NULL)
        return NULL;
    tree->tab[0] = (SLUG_SegmentExtended) {
        .A = (Vector2) {
            .x = 64,
            .y = 64
        },
        .B = (Vector2) {
            .x = 3947,
            .y = 64
        }, 
        .normal = (Vector2) {
            .x = 0,
            .y = 1
        },
        .dist = 0
    };
    tree->tab[1] = (SLUG_SegmentExtended) {
        .A = (Vector2) {
            .x = 3947,
            .y = 64
        },
        .B = (Vector2) {
            .x = 3947,
            .y = 3266
        }, 
        .normal = (Vector2) {
            .x = -1,
            .y = 0
        },
        .dist = 0
    };
    tree->tab[2] = (SLUG_SegmentExtended) {
        .A = (Vector2) {
            .x = 3947,
            .y = 3266
        },
        .B = (Vector2) {
            .x = 64,
            .y = 3266
        }, 
        .normal = (Vector2) {
            .x = 0,
            .y = -1
        },
        .dist = 0
    };
    tree->tab[3] = (SLUG_SegmentExtended) {
        .A = (Vector2) {
            .x = 64,
            .y = 3266
        },
        .B = (Vector2) {
            .x = 64,
            .y = 64
        }, 
        .normal = (Vector2) {
            .x = 1,
            .y = 0
        },
        .dist = 0
    };
    tree->tab[4] = (SLUG_SegmentExtended) {
        .A = (Vector2) {
            .x = 1000,
            .y = 1449
        },
        .B = (Vector2) {
            .x = 1494,
            .y = 1449
        }, 
        .normal = (Vector2) {
            .x = 0,
            .y = -1
        },
        .dist = 0
    };
    tree->tab[5] = (SLUG_SegmentExtended) {
        .A = (Vector2) {
            .x = 1494,
            .y = 1449
        },
        .B = (Vector2) {
            .x = 1494,
            .y = 1750
        }, 
        .normal = (Vector2) {
            .x = 1,
            .y = 0
        },
        .dist = 0
    };
    tree->tab[6] = (SLUG_SegmentExtended) {
        .A = (Vector2) {
            .x = 1494,
            .y = 1750
        },
        .B = (Vector2) {
            .x = 1000,
            .y = 1750
        }, 
        .normal = (Vector2) {
            .x = 0,
            .y = 1
        },
        .dist = 0
    };
    tree->tab[7] = (SLUG_SegmentExtended) {
        .A = (Vector2) {
            .x = 1000,
            .y = 1750
        },
        .B = (Vector2) {
            .x = 1000,
            .y = 1449
        }, 
        .normal = (Vector2) {
            .x = -1,
            .y = 0
        },
        .dist = 0
    };
    tree->tab[8] = (SLUG_SegmentExtended) {
        .A = (Vector2) {
            .x = 1885,
            .y = 1324
        },
        .B = (Vector2) {
            .x = 2232,
            .y = 1671
        }, 
        .normal = (Vector2) {
            .x = 0.70710678,
            .y = -0.70710678
        },
        .dist = 0
    };
    tree->tab[9] = (SLUG_SegmentExtended) {
        .A = (Vector2) {
            .x = 2232,
            .y = 1671
        },
        .B = (Vector2) {
            .x = 2011,
            .y = 1880
        }, 
        .normal = (Vector2) {
            .x = 0.70710678,
            .y = 0.70710678
        },
        .dist = 0
    };
    tree->tab[10] = (SLUG_SegmentExtended) {
        .A = (Vector2) {
            .x = 2011,
            .y = 1880
        },
        .B = (Vector2) {
            .x = 1675,
            .y = 1534
        }, 
        .normal = (Vector2) {
            .x = -0.70710678,
            .y = 0.70710678
        },
        .dist = 0
    };
    tree->tab[11] = (SLUG_SegmentExtended) {
        .A = (Vector2) {
            .x = 1675,
            .y = 1534
        },
        .B = (Vector2) {
            .x = 1885,
            .y = 1324
        }, 
        .normal = (Vector2) {
            .x = -0.70710678,
            .y = -0.70710678
        },
        .dist = 0
    };
    for(int32_t i = 0; i < tree->tab_size; ++i)
        tree->tab[i].dist = Vector2DotProduct(tree->tab[i].normal, tree->tab[i].A);
    tree->elements = (SLUG_BSPTreeElement *) malloc((tree->tab_size) * sizeof(SLUG_BSPTreeElement));
    tree->elements[0] = (SLUG_BSPTreeElement) {
        .segment = 0,
        .children = {SPACE_SOLID, 1}
    };
    tree->elements[1] = (SLUG_BSPTreeElement) {
        .segment = 2,
        .children = {SPACE_SOLID, 2}
    };
    tree->elements[2] = (SLUG_BSPTreeElement) {
        .segment = 5,
        .children = {3, 4}
    };
    tree->elements[3] = (SLUG_BSPTreeElement) {
        .segment = 7,
        .children = {5, 6}
    };
    tree->elements[4] = (SLUG_BSPTreeElement) {
        .segment = 8,
        .children = {7, 8}
    };
    tree->elements[5] = (SLUG_BSPTreeElement) {
        .segment = 6,
        .children = {9, SPACE_EMPTY}
    };
    tree->elements[6] = (SLUG_BSPTreeElement) {
        .segment = 3,
        .children = {SPACE_SOLID, SPACE_EMPTY}
    };
    tree->elements[7] = (SLUG_BSPTreeElement) {
        .segment = 10,
        .children = {10, SPACE_EMPTY}
    };
    tree->elements[8] = (SLUG_BSPTreeElement) {
        .segment = 1,
        .children = {SPACE_SOLID, SPACE_EMPTY}
    };
    tree->elements[9] = (SLUG_BSPTreeElement) {
        .segment = 4,
        .children = {SPACE_SOLID, SPACE_EMPTY}
    };
    tree->elements[10] = (SLUG_BSPTreeElement) {
        .segment = 9,
        .children = {11, SPACE_EMPTY}
    };
    tree->elements[11] = (SLUG_BSPTreeElement) {
        .segment = 11,
        .children = {SPACE_SOLID, SPACE_EMPTY}
    };
    return tree;
}

SLUG_map* SLUG_LoadMapDev()
{
    SLUG_map *map = (SLUG_map*) malloc(sizeof(SLUG_map));
    if(map == NULL)
        return NULL;
    map->fixed_sprite = LoadTexture("assets/dev_map.jpg");
    map->w = 4011;
    map->h = 3330;
    map->player_BSP = SLUG_LoadBSPTreeDev();
    return map;
}

void SLUG_MapUnload(SLUG_map *map)
{
    UnloadTexture(map->fixed_sprite);
    SLUG_BSTTreeUnload(map->player_BSP);
    free(map);
}

SLUG_camera SLUG_DefaultCamera(SLUG_map *map, SLUG_Player *player)
{
    SLUG_camera camera;
    camera.map = map;
    camera.player = player;
    camera.display = &display;
    camera.camera.x = 0;
    camera.camera.y = 0;
    camera.camera.width = 1680;
    camera.camera.height = 1050;
    camera.wanted_pos.x = 1680/2;
    camera.wanted_pos.y = 1050/2;
    camera.ratio_fix_x = display.width / camera.camera.width;
    camera.ratio_fix_y = display.height / camera.camera.height;
    return camera;
}

void SLUG_CameraScrolling(SLUG_camera *cam)
{
    cam->camera.x = cam->player->position.x - cam->wanted_pos.x;
    cam->camera.y = cam->player->position.y - cam->wanted_pos.y;

    cam->camera.x = fmax(cam->camera.x, 0);
    cam->camera.x = fmin(cam->camera.x, cam->map->w - 1680);
    cam->camera.y = fmax(cam->camera.y, 0);
    cam->camera.y = fmin(cam->camera.y, cam->map->h - 1050);
}

int8_t SLUG_Display(SLUG_camera *cam) // ptet autre part après et avec d'autres arguments
{
    cam->ratio_fix_x = display.width / cam->camera.width;
    cam->ratio_fix_y = display.height / cam->camera.height;
    SLUG_CameraScrolling(cam);
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexturePro(cam->map->fixed_sprite,cam->camera,*(cam->display),Vector2_0,0,WHITE);
    if(CheckCollisionRecs(cam->camera, cam->player->bounding_box))
    {
        Rectangle p = GetCollisionRec(cam->camera, cam->player->bounding_box);
        //printf("Camera position : %f, %f\n", cam->camera.x, cam->camera.y);
        DrawTexturePro(cam->player->sprite,(Rectangle) {.x= p.x - cam->player->bounding_box.x,.y=p.y - cam->player->bounding_box.y,.width=p.width, .height=p.height},
                        (Rectangle) {.x=cam->display->x + (p.x - cam->camera.x)*cam->ratio_fix_x, 
                                     .y=cam->display->y + (p.y - cam->camera.y)*cam->ratio_fix_y, 
                                     .width=p.width * cam->ratio_fix_x, 
                                     .height=p.height * cam->ratio_fix_y} ,Vector2_0,0,WHITE);
    }
    EndDrawing();
    return 0;
}

void SLUG_PlayerMove(SLUG_Player *player, SLUG_map *map, Vector2 wantedMove, uint32_t count)
{   

    if(count >= 2)
        return;

    Vector2 intersection;
    Vector2 p2 = (Vector2) {
        .x = player->position.x + wantedMove.x,
        .y = player->position.y + wantedMove.y
    };

    
    if(SLUG_RecursiveCollisionCheck(0, player->position, p2, map->player_BSP,&intersection))
    {
        //printf("Intersection : %f, %f, %d\n", intersection.x, intersection.y, segment_hit);
        Vector2 v = (Vector2) {
            .x = intersection.x - player->position.x,
            .y = intersection.y - player->position.y
        };
        player->position.x += v.x;
        player->position.y += v.y;
        player->hitbox.x += v.x;
        player->hitbox.y += v.y;
        player->bounding_box.x += v.x;
        player->bounding_box.y += v.y;

        int32_t index = -1;
        
        for(int32_t i = 0; i < map->player_BSP->tab_size; ++i)
        {
            if(Vector2DotProduct(map->player_BSP->tab[i].normal, wantedMove) < 0)
            {
                if(SLUG_CheckCollisionPointLine(intersection, map->player_BSP->tab[i].A, map->player_BSP->tab[i].B, 8.5)) //pas 8.5 mais DIST_EPSILON. Faire gaffe à avoir des normales précices pour résoudre le bug, sinon ça foire sur les coins.
                {
                    index = i;
                    break;
                }
            }
        }

        if(index == -1)
            return;

        v = (Vector2) {
            .x =  -1* map->player_BSP->tab[index].normal.y * (-1*map->player_BSP->tab[index].normal.y * (p2.x - intersection.x) + map->player_BSP->tab[index].normal.x * (p2.y - intersection.y)),
            .y =  map->player_BSP->tab[index].normal.x * (-1*map->player_BSP->tab[index].normal.y * (p2.x - intersection.x) + map->player_BSP->tab[index].normal.x * (p2.y - intersection.y))
        };
        //printf("%d %f %f %f %f\n",index,map->player_BSP->tab[index].normal.y*map->player_BSP->tab[index].normal.y, map->player_BSP->tab[index].normal.x * map->player_BSP->tab[index].normal.x, v.x, v.y);
        SLUG_PlayerMove(player, map, v, count + 1);

    }
    else
    {
        player->position.x += wantedMove.x;
        player->position.y += wantedMove.y;
        player->hitbox.x += wantedMove.x;
        player->hitbox.y += wantedMove.y;
        player->bounding_box.x += wantedMove.x;
        player->bounding_box.y += wantedMove.y;
    }

}
