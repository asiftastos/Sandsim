#include <stdlib.h>
#include <assert.h>
#include "struct.h"
#include "gfx.h"
#include "element.h"
#include "world.h"

static int Index(World* world, int x, int y)
{
    return y * world->width + x;
}

World* worldCreate(int width, int height)
{
    World* w = calloc(1, sizeof(World));
    assert(w != NULL);

    w->width = width;
    w->height = height;

    w->xmin = 0.0f;
    w->xmax = w->xmin + w->width;
    w->ymin = 0.0f;
    w->ymax = w->ymin + w->height;

    w->elementsGrid = calloc(width * height, sizeof(char));
    assert(w->elementsGrid != NULL);

    elementAdd(Air, NULL);
    elementAdd(Stone, NULL);
    elementAdd(Sand, updateSand);
    elementAdd(Water, updateWater);

    return w;
}

void worldDestroy(World* world)
{
    if(world)
    {
        if(world->elementsGrid)
            free(world->elementsGrid);
        
        free(world);
    }
}

ElementType worldElementAt(World* world, int x, int y)
{
    int i = Index(world, x, y);
    return world->elementsGrid[i];
}

void worldElementSet(World* world, int x, int y, ElementType type)
{
    int i = Index(world, x, y);
    world->elementsGrid[i] = (char)type;
}