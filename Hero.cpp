#include <cstdio>
#include "Hero.h"

Hero::Hero(Tile* _tile_use){
    tile_use = _tile_use;
    mover_component = new MoverComponent(this);
    graphic_component = new GraphicComponent(this);
    return;
}

void Hero::Render(float left, float top){
    graphic_component->Render(left, top);
    return;
}
