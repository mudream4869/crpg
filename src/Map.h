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
    
    static std::map<const char*, Map*, StrComp> map_pool;

    char* GetName();

    bool CanDo(int x, int y, int dir) const ;
    int GetPriority(int x, int y, int l) const ; 
    int GetLevelCount()const;
    char* GetMapBGM();
    Vec2i GetMapSize();
 
    void RenderATile(float left, float top, float width, float height, int x, int y, int l);
    void Render(float left, float top, float width, float height);
    void RenderAtPriority(float left, float top, float width, float height, int priority);

    std::vector<EventData> GetEventDatas();

private:
    char map_name[20];
    char map_bgm[20];
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
