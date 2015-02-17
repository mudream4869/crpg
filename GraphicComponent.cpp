#include "GraphicComponent.h"

GraphicComponent::GraphicComponent(Object* _obj){
    obj = _obj;
    for(int lx = 0;lx < 4;lx++){
        for(int ly = 0;ly < 4;ly++){
            walk_pos[lx][ly].x = ly;
            walk_pos[lx][ly].y = lx;
        }
    }
    return;
} 

void GraphicComponent::Render(float left, float top){
    int dir_x[] = {0, -1, 1, 0};
    int dir_y[] = {1, 0, 0, -1};
    if(obj->tile_use != nullptr){
        float paint_x = ((float)obj->status.x + obj->status.moving_step*dir_x[obj->status.moving_dir]/16.0)/10.0*2 + left;
        float paint_y = ((float)obj->status.y + obj->status.moving_step*dir_y[obj->status.moving_dir]/16.0)/10.0*2 + top;
        Vec2i sz = obj->tile_use->GetSize();
        paint_y = paint_y + 1/(float)5 - sz.y/(float)32*0.2;
        obj->tile_use->Render(
            paint_x, paint_y,
            sz.x/(float)32*0.2,
            sz.y/(float)32*0.2, 
            walk_pos[obj->status.face_dir][(obj->status.moving_step/2)%4].x,
            walk_pos[obj->status.face_dir][(obj->status.moving_step/2)%4].y,
        2);
    }
    return;
}
