#include <cstdio>
#include "Hero.h"

Hero::Hero(){
    tile_use = nullptr;
    mover_component = new MoverComponent(this);
    graphic_component = new GraphicComponent(this);
    return;
}

void Hero::SetTile(Tile* tile){
    tile_use = tile;
    return;
}

void Hero::Render(float left, float top){
    graphic_component->Render(left, top);
    return;
}
