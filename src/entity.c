#include "entity.h"
#include "gun.h"

SLUG_EntityCreate(SLUG_EntityType type, uint32_t iD, uint64_t size)
{
    SLUG_Entity *e = (SLUG_Entity *) malloc(size);
    e->type = type;
    e->alive = 1;
    e->iD = iD;
    return e;
}

void (*SLUG_EntityUpdateFunctions[SLUG_ENTITY_NUMBER]) (SLUG_Entity *entity) = {
    jaaj
};

void (*SLUG_EntityDieFunctions[SLUG_ENTITY_NUMBER]) (SLUG_Entity *entity) = {
    jaaj
};

void (*SLUG_EntityFreeFunctions[SLUG_ENTITY_NUMBER])(SLUG_Entity *entity) = {
    jaaj
};

SLUG_Entity* SLUG_EntityTab[OBJECT_LIMIT];
uint32_t     SLUG_CurrentEntityFreePlace = 0;

void SLUG_EntityTabInit()
{
    for(uint32_t i = 0; i < OBJECT_LIMIT; ++i)
        SLUG_EntityTab[i] = NULL;
}

void SLUG_EntityTabClear()
{
    for(uint32_t i = 0; i < OBJECT_LIMIT; ++i)
    {
    	SLUG_Entity* entity = SLUG_EntityTab[i];
        if(entity != NULL) 
        {
            SLUG_EntityFreeFunctions[entity->type](entity);
            SLUG_EntityTab[i] = NULL;
        }
    }
    SLUG_CurrentEntityFreePlace = 0;
}

void SLUG_EntityTabUpdate() 
{
    SLUG_Entity* entity = SLUG_EntityTab;
    for(uint32_t i = 0; i < SLUG_CurrentEntityFreePlace; ++i)
    {
        if(entity->alive == 1)
            SLUG_EntityUpdateFunctions[entity->type](entity);
    
    	entity += 1;
    }
}

int8_t SLUG_EntityTabIsFull()
{
    return SLUG_CurrentEntityFreePlace >= OBJECT_LIMIT; 
}

uint32_t SLUG_EntityTabSize()
{
    return SLUG_CurrentEntityFreePlace;
}

int8_t SLUG_EntityTabAdd(SLUG_Entity* entity)
{
    if(entity == NULL)
        return -1;

    if(SLUG_CurrentEntityFreePlace < OBECT_LIMIT)
    {
        SLUG_EntityTab[SLUG_CurrentEntityFreePlace] = entity;
        SLUG_CurrentEntityFreePlace += 1;
        
        return 1;
    }
    
    return 0;
}

void SLUG_EntityTabFreeDead()
{
    uint32_t i = 0;
    while(i < SLUG_CurrentEntityFreePlace)
    {
        SLUG_Entity *entity = SLUG_EntityTab[i];
    
        if(entity == NULL)
            break;      
        if(entity->alive == 0)
        {
            SLUG_EntityFreeFunctions[entity->type](entity);
            if(i == SLUG_CurrentEntityFreePlace - 1)
                SLUG_EntityTab[i] = NULL;
            else
            {
                SLUG_EntityTab[i] = SLUG_EntityTab[SLUG_CurrentEntityFreePlace - 1];
                SLUG_EntityTab[SLUG_CurrentEntityFreePlace - 1] = NULL;
            }
        
            SLUG_CurrentEntityFreePlace -= 1;
        }
        else
            i += 1;
    }
}

