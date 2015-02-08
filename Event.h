#ifndef EVENT_DEF
#define EVENT_DEF

#include <map>
#include <cstdlib>
#include <cstring>

#include "Tile.h"
#include "Script.h"
#include "Type.h"

#include "Tool.h"

#include "Object.h"
#include "MoverComponent.h"
#include "GraphicComponent.h"

const int TRIGGER_CONDITION_NULL = 0;
const int TRIGGER_CONDITION_ON_CHAT = 1;
const int TRIGGER_CONDITION_ON_STAND= 2;
const int TRIGGER_CONDITION_AUTO = 3;
const int TRIGGER_CONDITION_SYNC = 4;

const int COND_TYPE_FLAG = 0;
const int COND_TYPE_VALUE = 1;
const int COND_TYPE_PRIVATE_FLAG = 2; // TODO

class Event : public Object{
public:
    Event(const char* map_name, const char* str);
    ~Event();
    
    static std::map<const char*, Event*, StrComp> event_pool;  
     
    void Action(HeroStatus hero_status, bool is_enter);
    bool Condition();
    
    void TickEvent(int delta_time);
    
    void Render(float left, float top);
    int GetPriority();

    bool IsSolid() const;
    
    Vec2i Position() const;
    void SetPosition(int x, int y);
    
    int trigger_condition;
    
    HeroStatus GetStatus();
    void SetStatus(HeroStatus status);
    
    MoverComponent* mover_component;
    GraphicComponent* graphic_component;

private:
    char event_name[20];

    struct cond{
        int type;
        char var_name[20];
        int limit_value;
    };
    std::vector<cond> display_cond;
    std::vector<cond> reject_cond;

    Script* script;
};

#endif
