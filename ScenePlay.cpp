#include <map>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include "ScenePlay.h"
#include "WindowSelect.h"
#include "WindowGameObject.h"
#include "SysCall.h"
#include "Env.h"

ScenePlay::ScenePlay(Map* _map, Hero* _hero, int init_x, int init_y, float _screen_width, float _screen_height):
    Scene(_screen_width, _screen_height){
   
    fprintf(stderr, "Load map: %s\n", _map->GetName());
    this->SetMap(_map);
    
    hero_use = _hero;
    hero_status.x = init_x;
    hero_status.y = init_y;
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
                EnvSetCertainScene("scene_load");
                this->is_main_menu_open = false;
                return;
            }else if(index == 1){
                EnvSetCertainScene("scene_start");
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
    return;
}

char* ScenePlay::GetMapName(){
    return map_use->GetName();
}

bool ScenePlay::CanDo(int x, int y, int dir)const{
    static int dir_x[] = {0, -1, 1, 0};
    static int dir_y[] = {1, 0, 0, -1};
    for(int lx = 0;lx < events.size();lx++){
        if(events[lx]->IsSolid() == false) continue;
        Vec2i pos = events[lx]->Position();
        if(pos.x == x and pos.y == y) return false;
        if(pos.x == x + dir_x[dir] and pos.y ==  y + dir_y[dir]) return false;
    }
    return (map_use->CanDo(x, y, dir));
}

void ScenePlay::InputEvent(Input inp){
    if(inp.Key == 'q'){
        exit(0);
    }
    if(is_main_menu_open){
        if(inp.Key == 27){
            is_main_menu_open = false;
        }else{
            this->main_menu->InputEvent(inp);
        }
        return;
    }
    static int dir_x[] = {0, -1, 1, 0};
    static int dir_y[] = {1, 0, 0, -1};
    std::map<unsigned char, int> ch_dir_map;
    ch_dir_map['a'] = 1; ch_dir_map['s'] = 0;
    ch_dir_map['w'] = 3; ch_dir_map['d'] = 2;
    if(inp.InputType == INPUT_KEYPRESS){
        if(inp.Key == 27){
            is_main_menu_open = true; 
            this->obj_menu->Update();
            return;
        }else if(ch_dir_map.count(inp.Key)){
            // Moving on the map
            if(not is_win_menu_open){
                if(hero_status.status == 0){
                    int dir_index = ch_dir_map[inp.Key];
                    if(CanDo(hero_status.x, hero_status.y, dir_index)){
                        hero_status.status = 1;
                        hero_status.moving_step = 0;
                    }
                    hero_status.moving_dir = dir_index;
                }
            }
        }
        for(int lx = 0;lx < events.size();lx++){
            events[lx]->Action(hero_status, inp.Key == 13);
        }
    }
    return;
}

void ScenePlay::TickEvent(int delta_time){
    if(this->is_main_menu_open){
        this->main_menu->TickEvent(delta_time);
    }
    static int dir_x[] = {0, -1, 1, 0};
    static int dir_y[] = {1, 0, 0, -1};
    if(hero_status.status == 1){
        hero_status.moving_step = std::min(hero_status.moving_step + delta_time, 16);
        if(hero_status.moving_step == 16){ // TODO: make this constant
            hero_status.x += dir_x[hero_status.moving_dir];
            hero_status.y += dir_y[hero_status.moving_dir];
            hero_status.status = 0;
            hero_status.moving_step = 0;
        }
    }
    for(int lx = 0;lx < events.size();lx++)
        events[lx]->TickEvent(delta_time);
    return;
}

void ScenePlay::Render(){
    static int dir_x[] = {0, -1, 1, 0};
    static int dir_y[] = {1, 0, 0, -1};
    // TODO: change 10*10
    float hero_real_x = ((float)(hero_status.x) + 
                dir_x[hero_status.moving_dir]*hero_status.moving_step/(float)16)*screen_width/10,
          hero_real_y = ((float)(hero_status.y) +
                dir_y[hero_status.moving_dir]*hero_status.moving_step/(float)16)*screen_height/10;
    float start_x = 1 - hero_real_x;
    float start_y = 1 - hero_real_y;
    if(start_x > 0) start_x = 0;
    if(start_x < -2) start_x = -2;
    if(start_y > 0) start_y = 0;
    if(start_y < -2) start_y = -2;
    map_use->Render(start_x, start_y, screen_width*2, screen_height*2, 0, 0, 20, 20);
    //fprintf(stderr, "map render ok.\n");
    //fprintf(stderr, "hero_x = %d, hero_y = %d\n", hero_x, hero_y);
    hero_use->Render(
        hero_real_x + start_x,
        hero_real_y-0.2 + start_y,
        hero_status.moving_dir,
        (hero_status.moving_step/2)%4
    );
    
    for(int lx = 0;lx < events.size();lx++){
        events[lx]->Render(start_x, start_y);
    }
    int dir9_x[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
    int dir9_y[] = {-1, 1, 0, 1, -1, 0, -1, 1, 0};
    for(int lx = 0;lx < 9;lx++){
        int xx = hero_status.x + dir9_x[lx];
        int yy = hero_status.y + dir9_y[lx];
        // TODO:4 = level_count
        for(int ll = 0;ll < map_use->GetLevelCount();ll++){
            if(map_use->GetPriority(xx, yy, ll)){
                map_use->RenderATile(
                    start_x,
                    start_y,
                    screen_width*2, screen_height*2,
                    xx,
                    yy,
                    ll
                );
            }
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
