#include "struct.h"
#include "element.h"

void Sand(Element* e)
{
    e->id = SAND;
    e->lifetime = 0.0f;
    e->velocity = 1.0f;
    e->color = (vec4s){{0.9f,0.76f,0.16f, 1.0f}};
}

void updateSand(int x, int y)
{
}
