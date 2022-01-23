#include "struct.h"
#include "element.h"

void Air(Element* e)
{
    e->id = AIR;
    e->velocity = 0.0f;
    e->lifetime = 0.0f;
    e->color = (vec4s){{0.0f,0.0f,0.0f,1.0f}};
}
