#ifndef SANDSIM_ELEMENT_H
#define SANDSIM_ELEMENT_H

typedef enum ElementType
{
    AIR,
    SAND,
    STONE,
    WATER,
    LAST_ELEM
}ElementType;

typedef void (*UpdateElemFN)(int x, int y);

// elements
typedef struct Element
{
    unsigned char id;
    float lifetime;
    float velocity;
    vec4s color;
    UpdateElemFN update;
}Element;

typedef void (*CreateElemFN)(Element* e);

void elementsInit();
void elementsDeinit();
void elementAdd(CreateElemFN fCreate, UpdateElemFN fUpdate);
Element* elementGet(ElementType type);

void Air(Element* e);
void Sand(Element* e);
void Stone(Element* e);
void Water(Element* e);

void updateSand(int x, int y);
void updateWater(int x, int y);

#endif