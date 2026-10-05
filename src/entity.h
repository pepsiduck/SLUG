#ifndef ENTITY_H
#define ENTITY_H

#define OBJECT_LIMIT 2048

#include <stdlib.h>
#include <inttypes.h>

typedef enum {SLUG_ENTITY_ROCKET, 
              SLUG_ENTITY_NUMBER} SLUG_EntityType;
              
typedef struct SLUG_Entity SLUG_Entity;
struct SLUG_Entity
{
    //--- Universal
    EntityType type;
    int8_t alive;
    uint32_t iD;
    //---    
};


SLUG_Entity* p_entity_create(SLUG_EntityType type, uint32_t iD, uint64_t size);

extern void (*SLUG_EntityUpdateFunctions[ENTITY_NUMBER])(SLUG_Entity *entity);
extern void (*SLUG_EntityFreeFunctions[ENTITY_NUMBER])(SLUG_Entity *entity);


extern SLUG_Entity* SLUG_EntityTab[OBJECT_LIMIT]; //AN EMPTY ELEMENT MUST BE NULL
void SLUG_EntityTabInit();
void SLUG_EntityTabClear(); //To free the whole tab. WE FREE -> WE SET NULL 
void SLUG_EntityTabUpdate();
int8_t SLUG_EntityTabIsFull();
uint32_t SLUG_EntityTabSize(); //Returns the number of elements in the entity tab
int8_t SLUG_EntityTabAdd(SLUG_Entity* entity);
void SLUG_EntityTabFreeDead();

#endif
