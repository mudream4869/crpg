#include <cstdio>
#include "Hero.h"

Hero::Hero(){
    tile_use = nullptr;
    mover_component = new MoverComponent(this);
    return;
}

void Hero::SetTile(Tile* tile){
    tile_use = tile;
    return;
}

void Hero::SetWalkPiece(){
    // Default setting
    for(int lx = 0;lx < 4;lx++){
        for(int ly = 0;ly < 4;ly++){
            walk_pos[lx][ly].x = ly;
            walk_pos[lx][ly].y = lx;
        }
    }
    return;
}

void Hero::SetWalkPiece(int pos[4][4][2]){
    for(int lx = 0;lx < 4;lx++){
        for(int ly = 0;ly < 4;ly++){
            walk_pos[lx][ly].x = pos[lx][ly][0];
            walk_pos[lx][ly].y = pos[lx][ly][1];
        }
    }
    return;
}

void Hero::Render(float left, float top){
    //fprintf(stderr, "rx = %d ry = %d\n", this->walk_pos[dir][render_index].x, this->walk_pos[dir][render_index].y);
    int render_index = (status.moving_step/2)%4;
    this->tile_use->Render(
        left, top, 0.2, 0.3, 
        this->walk_pos[status.moving_dir][render_index].x,
        this->walk_pos[status.moving_dir][render_index].y,
        1
    );
    return;
}
