#ifndef SCENEPLAY_DEF
#define SCENEPLAY_DEF

#include <vector>
#include "Scene.h"
#include "Type.h"
#include "Map.h"
#include "Hero.h"
#include "Window.h"
#include "Event.h"

class ScenePlay: public Scene{
public:
    ScenePlay(Map* _map, Hero* hero_use, int init_x, int init_y, float screen_width, float screen_height);
    void InputEvent(Input inp);
    
    void ChangeMap(Map* _map, int start_x, int start_y, int dir);
    char* GetMapName();
    // Important Trigger Event
    // Should be called every tick
    void TickEvent(int delta_time);

    void Render();
     
    bool CanDo(int x, int y, int dir)const;
    
    HeroStatus GetHeroStatus()const;

private:

    void SetMap(Map* _map);

    Map* map_use;
    Hero* hero_use;
    HeroStatus hero_status;
    Window* win_menu;
    Window* main_menu;
    bool is_win_menu_open;
    bool is_main_menu_open;
    
    std::vector<Event*> events;
};

#endif
