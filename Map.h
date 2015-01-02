#ifndef MAP_DEF
#define MAP_DEF

#include<vector>
#include<utility>
#include<map>
#include "Tile.h"
#include "Type.h"

class Map{
public:
    Map();
    void SetTile(Tile* tile);
    void SetName(const char* name);
    char* GetName();
    void LoadMap(const char* path);
    void Render(float left, float top, float width, float height, int x, int y, int x_count, int y_count);
    bool CanDo(int x, int y, int dir) const ;
    
    std::vector<EventData> GetEventDatas();

private:
    char* map_name;
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
    point*** map_load;

    std::vector<EventData> event_datas;
};

#endif
