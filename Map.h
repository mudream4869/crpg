#ifndef MAP_DEF
#define MAP_DEF

#include <vector>
#include <utility>
#include <map>
#include <cstdio>
#include <cstring>
#include "Tile.h"
#include "Type.h"

struct StrComp1{
    bool operator()(const char* str1, const char* str2) const{
        return strcmp(str1, str2) < 0;
    }
};

class Map{
public:
    Map(const char*);
    
    static std::map<const char*, Map*, StrComp1> map_pool;

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
    struct point {int x, y;};
    point new_point(int _x, int _y){
        point ret;
        ret.x = _x, ret.y = _y;
        return ret;
    }
    int map_width, map_height;
    int peice_width, peice_height;
    int level_count;

    std::map<std::pair<int,int>, int> terrain;
    std::map<std::pair<int,int>, int> priority;
    std::vector<point**> map_load;

    std::vector<EventData> event_datas;
};

#endif
