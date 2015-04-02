#ifndef OBJECT_DEF
#define OBJECT_DEF

#include "Type.h"
#include "Tile.h"

class Object{
public:
    Object();
    HeroStatus status;
    int speed;    
    
    Vec2i GetPosition();
    Vec2i GetNextPosition();
    void SetPosition(int x, int y);

    int priority;
    
    bool is_solid;
    bool fixed_direction;
    bool is_stay;
    Tile* tile_use;
};

#endif
