#include "struct.h"
#include "element.h"

void Water(Element* e)
{
    e->id = WATER;
    e->lifetime = 0.0f;
    e->velocity = 1.5f;
    e->color = (vec4s){{0.05f,0.2f,0.9f, 1.0f}};
}

void updateWater(int x, int y)
{
}
