#include "vec.h"
#include "struct.h"
#include "element.h"

static const char* elementNames[] = {
    "Air",
    "Sand",
    "Stone",
    "Water"
};

typedef vec_t(Element) vec_element_t;

typedef struct ElementRegistry
{
    vec_element_t elements;
}ElementRegistry;

static ElementRegistry registry;

void elementsInit()
{
    vec_init(&registry.elements);
}

void elementsDeinit()
{
    vec_deinit(&registry.elements);
}

void elementAdd(CreateElemFN fCreate, UpdateElemFN fUpdate)
{
    Element e;
    fCreate(&e);
    e.update = fUpdate;
    vec_push(&registry.elements, e);
}

Element* elementGet(ElementType type)
{
    return &registry.elements.data[type];
}
