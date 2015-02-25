#ifndef SCENEPLAY_DEF
#define SCENEPLAY_DEF

#include <vector>
#include "Scene.h"
#include "Type.h"
#include "Map.h"
#include "Hero.h"
#include "Window.h"
#include "Event.h"

#include "Object.h"

class ScenePlay: public Scene{
public:
    ScenePlay();
    void InputEvent(Input inp);
    
    void ChangeMap(Map* _map, int start_x, int start_y, int dir);
    char* GetMapName();
    // Important Trigger Event
    // Should be called every tick
    void TickEvent(int delta_time);

    void Render();
     
    bool CanDo(int x, int y, int dir, Object* self = nullptr)const;
     
    HeroStatus GetHeroStatus()const;

    void Call();
    void Call(Map*, int, int, int);
    
    static ScenePlay* scene_play;
    Hero* hero_use;

private:

    void SetMap(Map* _map);

    Map* map_use;
    
    Window* main_menu;
    Window* obj_menu;

    bool is_main_menu_open;
    bool is_obj_menu_open; 

    std::vector<Event*> events;
};

#endif
