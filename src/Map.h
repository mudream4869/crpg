#ifndef MAP_DEF
#define MAP_DEF

#include <vector>
#include <map>
#include <cstdio>
#include <cstring>

#include "Tile.h"
#include "Type.h"
#include "Tool.h"

class Map{
public:
    Map(const char*);
    
    static std::map<std::string, Map*> map_pool;

    bool CanDo(int x, int y, int dir) const ;
    int GetPriority(int x, int y, int l) const ; 
    int GetLevelCount()const;
    std::string GetMapBGM()const;
    Vec2i GetMapSize();
    std::string GetName()const;
 
    void RenderATile(float left, float top, float width, float height, int x, int y, int l);
    void Render(float left, float top, float width, float height);
    void RenderAtPriority(float left, float top, float width, float height, int priority);

    std::vector<EventData> GetEventDatas();

private:
    std::string map_name;
    std::string map_bgm;
    Tile* tile_use;
    
    int map_width, map_height;
    int peice_width, peice_height;
    int level_count;
    
    // from point to terrain
    std::map<Vec2i, int> terrain;

    //from point to priority
    std::map<Vec2i, int> priority;

    std::vector<Vec2i**> map_load;

    std::vector<EventData> event_datas;
};

#endif
