#ifndef HERO_DEF
#define HERO_DEF

#include "Tile.h"
class Hero{
public:
    Hero();
    void SetTile(Tile* tile);

    void SetWalkPiece();
    // Use default setting

    void SetWalkPiece(int pos[4][4][2]);
    // As the direction 0 => up, 1 => down, 2 => left, 3 => right

    void Render(float x, float y, int dir, int render_index);

private:
    Tile* tile_use;
    struct point{ int x, y;};
    point walk_pos[4][4];

};

#endif
