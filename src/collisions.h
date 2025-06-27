#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <inttypes.h>
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

#define SPACE_SOLID -1
#define SPACE_EMPTY -2
#define DIST_EPSILON 0.03125

typedef struct SLUG_SegmentExtended SLUG_SegmentExtended;
struct SLUG_SegmentExtended
{
    Vector2 A; 
    Vector2 B;
    Vector2 normal; //norm = 1
    float dist; //distance de la droite représentée par le segment ar rapport à 0, 0
};

typedef struct SLUG_BSPTreeElement SLUG_BSPTreeElement;
struct SLUG_BSPTreeElement
{
    int32_t segment;
    int32_t children[2];
};

typedef struct SLUG_BSPTree SLUG_BSPTree;
struct SLUG_BSPTree
{
    SLUG_SegmentExtended *tab; 
    SLUG_BSPTreeElement *elements; //tree trunk is always element index 0
    uint8_t *elements_passed; //tabsize/8 + 1
    int32_t tab_size;
    
};

SLUG_BSPTree* SLUG_LoadBSPTreeDev();
void SLUG_BSTTreeUnload(SLUG_BSPTree *tree);

bool SLUG_CheckCollisionPointLine(Vector2 point, Vector2 p1, Vector2 p2, float threshold);
bool SLUG_RecursiveCollisionCheck(int32_t node, Vector2 p1, Vector2 p2, SLUG_BSPTree *tree, Vector2 *intersection);



#endif
