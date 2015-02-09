#ifndef OBJECT_DEF
#define OBJECT_DEF

#include "Type.h"
#include "Tile.h"

class Object{
public:
    Object();
    HeroStatus status;
    
    Vec2i GetPosition();
    void SetPosition(int x, int y);

    int priority;
    
    bool is_solid;
    bool fixed_direction;
    Tile* tile_use;
};

#endif
