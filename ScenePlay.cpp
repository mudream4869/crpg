#include <map>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include "ScenePlay.h"
#include "WindowSelect.h"
#include "WindowGameObject.h"
#include "SysCall.h"
#include "Env.h"
#include "AudioSystem.h"

#include "SceneLoad.h"
#include "SceneStart.h"

#include "GlobalVariable.h"

#include "InputCtrl.h"

ScenePlay* ScenePlay::scene_play = nullptr;

ScenePlay::ScenePlay(){
    
    ScenePlay::scene_play = this;
    
    auto img1 = new Image("textures/hero.bmp");
    auto hero_tile = new Tile();
    hero_use = new Hero();
    hero_tile->SetImage(img1);
    hero_tile->SetSize(32, 48);
    hero_use->SetTile(hero_tile);
    hero_use->SetWalkPiece();

    hero_status.status = 0; // Stop
    hero_status.moving_dir = 0;
    hero_status.moving_step = 0;

    win_menu = new Window(0.1, 0.1, 1.8, 1.8);
    is_win_menu_open = false;
    is_main_menu_open = false;
    
    fprintf(stderr, "start to set up main menu\n");
    char* main_menu_string[3] = {new char[20], new char[20], new char[20]};
    strcpy(main_menu_string[0], "Load File");
    strcpy(main_menu_string[1], "Return Menu"); 
    strcpy(main_menu_string[2], "Exit Game"); 
    fprintf(stderr, "ready for string\n");
    main_menu = new WindowSelect(0.7, 0.75, 0.6, 0.55, 
        [this](int index){
            if(index == -1) this->is_main_menu_open = false;
            if(index == 0){
                SceneLoad::Call();
                this->is_main_menu_open = false;
                return;
            }else if(index == 1){
                SceneStart::Call();
                this->is_main_menu_open = false;
                return;
            }else if(index == 2){
                //TODO:Exit Game
                exit(0);
            }
            return;
        }, [this](int index){
            return;
        }, main_menu_string, 3); 
    delete[] main_menu_string[0];
    delete[] main_menu_string[1];
    delete[] main_menu_string[2];

    obj_menu = new WindowGameObject(0.1, 0.1);
    main_menu = obj_menu;
    return;
}

void ScenePlay::Call(Map* _map, int start_x, int start_y, int dir){
    Scene::scene_certain = (Scene*) ScenePlay::scene_play;
    fprintf(stderr, "here\n");
    ScenePlay::scene_play->ChangeMap(_map, start_x, start_y, dir);
    return;
}

void ScenePlay::Call(){
    Scene::scene_certain = (Scene*) ScenePlay::scene_play;
    return;
} 

void ScenePlay::ChangeMap(Map* _map, int start_x, int start_y, int dir){
    // Set up event
    hero_status.x = start_x, hero_status.y = start_y;
    if(dir != -1) // -1 -> remain same direction
        hero_status.moving_dir = dir;
    hero_status.moving_step = 0;
    hero_status.status = 0;
    this->SetMap(_map);
    return;
}

void ScenePlay::SetMap(Map* _map){
    map_use = _map;
    for(int lx = 0;lx < events.size();lx++){
        delete events[lx];
    }
    events.clear();
    
    auto event_pool = EnvGetEventPool();
    event_pool->clear();
    std::vector<EventData> event_datas = _map->GetEventDatas();
    
    for(int lx = 0;lx < event_datas.size();lx++){
        Event* new_event = new Event(_map->GetName(), event_datas[lx].name);
        new_event->SetPosition(event_datas[lx].x, event_datas[lx].y);   
        events.push_back(new_event);
    }
    if(map_use->GetMapBGM()[0] != 0){
        AudioSystem::PlayBGM(map_use->GetMapBGM());
    }
    return;
}

char* ScenePlay::GetMapName(){
    return map_use->GetName();
}

bool ScenePlay::CanDo(int x, int y, int dir)const{
    static int dir_x[] = {0, -1, 1, 0};
    static int dir_y[] = {1, 0, 0, -1};
    //printf("Vis ScenePlay : x, y = %d, %d\n", x, y);
    for(int lx = 0;lx < events.size();lx++){
        if(events[lx]->IsSolid() == false) continue;
        Vec2i pos = events[lx]->Position();
        if(pos.x == x and pos.y == y) return false;
        if(pos.x == x + dir_x[dir] and pos.y ==  y + dir_y[dir]) return false;
    }
    return (map_use->CanDo(x, y, dir));
}

void ScenePlay::InputEvent(Input inp){
    if(is_main_menu_open){
        if(inp.Key == 27){
            is_main_menu_open = false;
        }else{
            if(inp.Key == 13)
                is_main_menu_open = false;
            this->main_menu->InputEvent(inp);
        }
        return;
    }

    if(inp.InputType == INPUT_KEYPRESS){
        if(inp.Key == 27){
            is_main_menu_open = true; 
            this->obj_menu->Update();
            return;
        }
        for(int lx = 0;lx < events.size();lx++){
            events[lx]->Action(hero_status, inp.Key == 13);
        }
    }
    return;
}

void ScenePlay::TickEvent(int delta_time){
    if(this->is_main_menu_open){
        // block
        this->main_menu->TickEvent(delta_time);
        return;
    }
    if(hero_status.status == 1){
        hero_status.moving_step = std::min(hero_status.moving_step + delta_time, 16);
        if(hero_status.moving_step == 16){ // TODO: make this constant
            int dir_x[] = {0, -1, 1, 0};
            int dir_y[] = {1, 0, 0, -1};
            hero_status.x += dir_x[hero_status.moving_dir];
            hero_status.y += dir_y[hero_status.moving_dir];
            hero_status.status = 0;
            hero_status.moving_step = 0;
        }
    }else if(hero_status.status == 0){
        int arr_index = InputCtrl::GetArrowCommand();
        if(arr_index != -1){
            if(CanDo(hero_status.x, hero_status.y, arr_index)){
                hero_status.status = 1;
                hero_status.moving_step = 0;
            }
            hero_status.moving_dir = arr_index;
        }
    }
    for(int lx = 0;lx < events.size();lx++){
        events[lx]->TickEvent(delta_time);
        // TODO: weird part: how to control auto event
        events[lx]->Action({-1, -1}, 0);
    }
    return;
}

void ScenePlay::Render(){
    static int dir_x[] = {0, -1, 1, 0};
    static int dir_y[] = {1, 0, 0, -1};
    
    float hero_real_x = ((float)(hero_status.x) + 
                dir_x[hero_status.moving_dir]*hero_status.moving_step/(float)16)*screen_width/10,
          hero_real_y = ((float)(hero_status.y) +
                dir_y[hero_status.moving_dir]*hero_status.moving_step/(float)16)*screen_height/10 + 1/(float)5 - 0.3;
    
    float start_x = 1 - hero_real_x;
    float start_y = 1 - hero_real_y;
    
    auto map_size = map_use->GetMapSize();
    
    if(start_x > 0) start_x = 0;
    if(start_y > 0) start_y = 0;
    if(map_size.x*0.2 + start_x < 2) start_x = 2 - map_size.x*0.2;
    if(map_size.y*0.2 + start_y < 2) start_y = 2 - map_size.y*0.2;
    
    // Priority = 0
    map_use->Render(start_x, start_y, screen_width*2, screen_height*2);
    
    // Priority = 1
    map_use->RenderAtPriority(start_x, start_y, screen_width*2, screen_height*2, 1);
    for(int ly = 0;ly < map_size.y;ly++){
        for(int lx = 0;lx < events.size();lx++)
            if(events[lx]->GetPriority() == 1 and events[lx]->Position().y == ly)
                events[lx]->Render(start_x, start_y);
        if(ly == hero_status.y)
            hero_use->Render(
                hero_real_x + start_x,
                hero_real_y + start_y,
                hero_status.moving_dir,
                (hero_status.moving_step/2)%4
            );
    }

    // Prioroty > 1
    for(int priority = 2; priority <= 5;priority++){
        map_use->RenderAtPriority(start_x, start_y, screen_width*2, screen_height*2, priority);
        for(int ly = 0;ly < map_size.y;ly++){
            for(int lx = 0;lx < events.size();lx++)
                if(events[lx]->GetPriority() == priority and events[lx]->Position().y == ly)
                    events[lx]->Render(start_x, start_y);
        }
    }

    if(is_win_menu_open)
        win_menu->Render();

    if(is_main_menu_open)
        main_menu->Render();
    return;
}

HeroStatus ScenePlay::GetHeroStatus()const{
    return hero_status;
}
