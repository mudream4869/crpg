#ifndef HERO_DEF
#define HERO_DEF

#include "Tile.h"
#include "Object.h"
#include "Type.h"

#include "MoverComponent.h"

class Hero : public Object{
public:
    Hero();
    void SetTile(Tile* tile);

    void SetWalkPiece();
    // Use default setting

    void SetWalkPiece(int pos[4][4][2]);
    // As the direction 0 => up, 1 => down, 2 => left, 3 => right

    void Render(float left, float top);

    MoverComponent* mover_component;

private:
    Tile* tile_use;
    Vec2i walk_pos[4][4];
    
};

#endif
