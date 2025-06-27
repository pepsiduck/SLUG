#include "collisions.h"
#include "defines.h"

SLUG_BSPTree* SLUG_LoadBSPTreeDev()
{
    SLUG_BSPTree *tree = (SLUG_BSPTree *) malloc(sizeof(SLUG_BSPTree));
    if(tree == NULL)
        return NULL;
    tree->tab_size = 12;
    tree->elements_passed = (uint8_t *) malloc(((tree->tab_size / 8) + (tree->tab_size % 8 != 0)) * sizeof(uint8_t));
    if(tree->elements_passed == NULL)
        return NULL;
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

void SLUG_BSTTreeUnload(SLUG_BSPTree *tree)
{
    free(tree->tab);
    free(tree->elements);
    free(tree->elements_passed);
    free(tree);
}

bool SLUG_CheckCollisionPointLine(Vector2 point, Vector2 p1, Vector2 p2, float threshold)
{
    bool collision = false;
    float dxc = point.x - p1.x;
    float dyc = point.y - p1.y;
    float dxl = p2.x - p1.x;
    float dyl = p2.y - p1.y;
    float cross = dxc * dyl - dyc * dxl;
    if (abs(cross) < threshold * fmaxf(fabsf(dxl), fabsf(dyl))) {
        if (fabsf(dxl) >= fabsf(dyl))
        collision = dxl > 0 ? 
            p1.x <= point.x && point.x <= p2.x :
            p2.x <= point.x && point.x <= p1.x;
        else
        collision = dyl > 0 ? 
            p1.y <= point.y && point.y <= p2.y :
            p2.y <= point.y && point.y <= p1.y;
    }
    return collision;
}

bool SLUG_RecursiveCollisionCheck(int32_t node, Vector2 p1, Vector2 p2, SLUG_BSPTree *tree, Vector2 *intersection)
{
    if(node < 0)
    {
        if(node == SPACE_SOLID)
        {
            *intersection = p1;
            return true;
        }
        else if(node == SPACE_EMPTY)
            return false;
        else
            return false;
    }
    
    //errors
    if(node >= tree->tab_size)
        return false;
    if(tree->elements[node].segment < 0 || tree->elements[node].segment >= tree->tab_size)
        return false;

    //printf("%d\n",node);
    tree->elements_passed[tree->elements[node].segment >> 3] += 1 << (tree->elements[node].segment & 7);
    
    float t1 = Vector2DotProduct(tree->tab[tree->elements[node].segment].normal, p1) - tree->tab[tree->elements[node].segment].dist;
    float t2 = Vector2DotProduct(tree->tab[tree->elements[node].segment].normal, p2) - tree->tab[tree->elements[node].segment].dist;

    //in only one child
    if(t1 >= 0 && t2 >= 0)
        return SLUG_RecursiveCollisionCheck(tree->elements[node].children[1], p1, p2, tree, intersection);
    else if (t1 < 0 && t2 < 0)
        return SLUG_RecursiveCollisionCheck(tree->elements[node].children[0], p1, p2, tree, intersection);

    

    //find intersect beetween children
    float frac;
    if(t1 < 0)
        frac = (t1 + DIST_EPSILON) / (t1 - t2);
    else
        frac = (t1 - DIST_EPSILON) / (t1 - t2);
    frac = frac < 0 ? 0 : (frac > 1 ? 1 : frac);
    Vector2 mid = (Vector2) {
        .x = p1.x + frac*(p2.x - p1.x),
        .y = p1.y + frac*(p2.y - p1.y)
    };
    int8_t side = (t1 >= 0);

    //near child then far child
    if (SLUG_RecursiveCollisionCheck(tree->elements[node].children[side], p1, mid, tree, intersection))
        return true;
    return SLUG_RecursiveCollisionCheck(tree->elements[node].children[1 - side], mid, p2, tree, intersection);
}
