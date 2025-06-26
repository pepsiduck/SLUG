#include "collisions.h"

void SLUG_BSTTreeUnload(SLUG_BSPTree *tree)
{
    free(tree->tab);
    free(tree->elements);
    free(tree);
}

bool SLUG_CheckCollisionPointLine(Vector2 point, Vector2 p1, Vector2 p2, float threshold)
{
    printf("%f %f %f %f %f %f\n",point.x, point.y, p1.x, p1.y, p2.x, p2.y);
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
    //printf("%d\n",collision);
    return collision;
}

bool SLUG_RecursiveCollisionCheck(int32_t node, Vector2 p1, Vector2 p2, SLUG_BSPTree *tree, Vector2 *intersection)
{
    //printf("\n");
    //printf("%d |", node);
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
    
    float t1 = Vector2DotProduct(tree->tab[tree->elements[node].segment].normal, p1) - tree->tab[tree->elements[node].segment].dist;
    float t2 = Vector2DotProduct(tree->tab[tree->elements[node].segment].normal, p2) - tree->tab[tree->elements[node].segment].dist;

    //printf("%f %f |", t1, t2);

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
    Vector2 mid = (Vector2) {
        .x = p1.x + frac*(p2.x - p1.x),
        .y = p1.y + frac*(p2.y - p1.y)
    };
    frac = frac < 0 ? 0 : (frac > 1 ? 1 : frac);
    int8_t side = (t1 >= 0);

    //near child then far child
    if (SLUG_RecursiveCollisionCheck(tree->elements[node].children[side], p1, mid, tree, intersection))
        return true;
    return SLUG_RecursiveCollisionCheck(tree->elements[node].children[1 - side], mid, p2, tree, intersection);
}
