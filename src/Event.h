#ifndef EVENT_DEF
#define EVENT_DEF

#include <map>
#include <cstdlib>
#include <cstring>
#include <string>

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
const int COND_TYPE_PRIVATE_FLAG = 2; // TODO: what's this

class Event : public Object{
public:
    
    /**
     *  @brief Fetch the event functor by map name and class name
     *  @param 
     *      map_name : map's filename without prefix filename
     */
    Event(std::string map_name, const char* class_name);

    ~Event();
    
    /**
     *  @brief The events in this stage
     */
    static std::map<const char*, Event*, StrComp> event_pool;  
    
    /**
     *  @brief Trigger the Event 
     *  @param 
     *      is_enter : is the Enter key press
     */
    void Action(bool is_enter);

    // TODO: change name
    /**
     *  @brief The Event may fit condition that should be trigger
     *  @return
     *      is event should be trugger
     */
    bool Condition();
   
    /**
     *  @brief Trigger the Timer of this Event
     *  @param
     *      delta_time : the time walk through 
     */
    void TickEvent(int delta_time);
    
    /**
     *  @brief Render the Event 
     *  @param 
     *      left : the x-axis coordinate from lefttop corner
     *      top : the y-axis coordinate from lefttop corner
     */
    void Render(float left, float top);

    /**
     *  @return Get the priority of the Event
     */
    int GetPriority();
    
    /**
     *  @brief The event may be solid or not
     *  @return
     *      is this event solid?
     */
    bool IsSolid() const;
    
    MoverComponent* mover_component;
    GraphicComponent* graphic_component;

private:
    int trigger_condition;
    
    char event_name[20];
    
    struct cond{
        int type;
        char var_name[20];
        int limit_value;
    };
    std::vector<cond> display_cond;
    std::vector<cond> reject_cond;
    
    /**
     *  @brief Change PyList of Condition to Vector
     *  @param
     *      cond_list : PyList condition list 
     *  @return 
     *      Vector of condition
     */
    static std::vector<cond> CondList2Vector(PyObject* cond_list);
    
    // TODO: change char* to string

    /**
     *  @brief From PyObject to String
     *  @param 
     *      p_str : PyString
     *      str_ptr : c string pointer, the result will write here
     *      default_str : if p_str is null, then str_ptr will write this
     */
    static void PyObject2String(PyObject* p_str, char* str_ptr, const char* default_str = "");
    
    /** Script Object*/
    Script* script;
};

#endif
