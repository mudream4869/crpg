#ifndef HERO_DEF
#define HERO_DEF

#include "Tile.h"
#include "Object.h"
#include "Type.h"

#include "MoverComponent.h"
#include "GraphicComponent.h"

class Hero : public Object{
public:
    Hero();
    void SetTile(Tile* tile);

    void Render(float left, float top);

    MoverComponent* mover_component;
    GraphicComponent* graphic_component;
};

#endif
