#ifndef SANDSIM_WORLD_H
#define SANDSIM_WORLD_H

#define GRAVITY  1.0f;

//grid
typedef struct World
{
    //screen coords
    int xmin;
    int xmax;
    int ymin;
    int ymax;
    int width;
    int height;
    char* elementsGrid;
}World;

World* worldCreate(int width, int height);
void worldDestroy(World* world);
ElementType worldElementAt(World* world, int x, int y);
void worldElementSet(World* world, int x, int y, ElementType type);

#endif