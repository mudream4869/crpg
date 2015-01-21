#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mutex>

#include "ImgCtrl.h"

static struct{
    std::mutex mutlock;
    bool to_display;
    char img_fn[20];
    Image* img;
    Vec2f pos;
    Vec2f rect;
}img_table[100];

void ImgCtrl::InitImgCtrl(){
    for(int lx = 0;lx < 100;lx++){
        img_table[lx].to_display = false;
        img_table[lx].img = nullptr;
    }
    return;
}

void ImgCtrl::ShowImg(int index, const char* img_fn, Vec2f pos, Vec2f rect){
    if(index < 0 or index >= 100){
        fprintf(stderr, "ImgCtrl Error=\"index should in [0, 100)\"\n");
        return;
    }
    img_table[index].mutlock.lock();
    if(img_table[index].img != nullptr)
        delete img_table[index].img;
    img_table[index].img = nullptr;
    
    strcpy(img_table[index].img_fn, img_fn);
    img_table[index].pos = pos;
    img_table[index].rect = rect;
    img_table[index].to_display = true;
    img_table[index].mutlock.unlock();
    return;
}

void ImgCtrl::KillImg(int index){
    img_table[index].mutlock.lock();
    img_table[index].to_display = false;
    img_table[index].mutlock.unlock();
    return;
}

// main thread
void ImgCtrl::Render(){
    for(int lx = 0;lx < 100;lx++){
        if(img_table[lx].to_display == false) continue;
        img_table[lx].mutlock.lock();
        if(img_table[lx].img == nullptr){
            img_table[lx].img = new Image(img_table[lx].img_fn);
        }
        img_table[lx].img->Render(
            img_table[lx].pos.x, 
            img_table[lx].pos.y,
            img_table[lx].rect.x,
            img_table[lx].rect.y,
            lx + 5
        );
        img_table[lx].mutlock.unlock();
    }
    return;
}
