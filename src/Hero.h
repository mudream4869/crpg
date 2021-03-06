#ifndef HERO_DEF
#define HERO_DEF

#include "Tile.h"
#include "Object.h"
#include "Type.h"

#include "MoverComponent.h"
#include "GraphicComponent.h"

class Hero : public Object{
public:
    Hero(Tile* _tile_use = nullptr);
    
    void TickEvent(int delta_time); 
    void Render(float left, float top);

    MoverComponent* mover_component;
    GraphicComponent* graphic_component;
};

#endif
