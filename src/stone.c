#include "struct.h"
#include "element.h"

void Stone(Element* e)
{
    e->id = STONE;
    e->lifetime = 0.0f;
    e->velocity = 0.0f;
    e->color= (vec4s){{0.35f,0.35f,0.40f, 1.0f}};
}
