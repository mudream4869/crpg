#include <cstdio>
#include "Hero.h"

#include "InputCtrl.h"
#include "ScenePlay.h"

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

void Hero::TickEvent(int delta_time){
    if(InputCtrl::IsNormalKeyPress('z'))
        speed = 2;
    else
        speed = 0;

    if(mover_component->IsQueued() or status.status){
        mover_component->TickEvent(delta_time);
    }else if(status.status == 0){
        int arr_index = InputCtrl::GetArrowCommand();
        if(arr_index != -1){
            if(ScenePlay::scene_play->CanDo(status.x, status.y, arr_index, this)){
                status.status = 1;
                status.moving_step = 0;
            }
            status.moving_dir = arr_index;
            status.face_dir = arr_index;
        }
    }
    return;
} 
