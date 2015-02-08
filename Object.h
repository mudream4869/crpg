#ifndef OBJECT_DEF
#define OBJECT_DEF

#include "Type.h"
#include "Tile.h"

class Object{
public:
    Object();
    HeroStatus status;

    int priority;
    
    bool is_solid;
    bool fixed_direction;
    Tile* tile_use;
};

#endif
