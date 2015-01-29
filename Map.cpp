#include "inc_gl.h"
#include <cstdlib>
#include <cstdio>
#include <map>
#include <cstring>
#include <string>
#include "Map.h"
#include "Config.h"
#include "Tool.h"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"

Map::Map(){
    tile_use = nullptr;
    return;
}

void Map::SetTile(Tile* tile){
    tile_use = tile;
    return;
}

void Map::SetName(const char* name){
    map_name = new char[strlen(name) + 2];
    strcpy(map_name, name);
    return;
}

char* Map::GetName(){
    return map_name;
}

void Map::LoadMap(const char* path){

    fprintf(stderr, "Map:ready to load %s\n", path);
    // Read map by rapidxml
    rapidxml::xml_node<>* root_node;
    rapidxml::xml_document<> doc;
    rapidxml::file<> file(path);

    doc.parse<0>(file.data());
    root_node = doc.first_node("map");

    // TODO: Error Handling
    // Get Map INFO

    this->map_width = std::atoi(root_node->first_attribute("width")->value());
    this->map_height = std::atoi(root_node->first_attribute("height")->value());
    this->peice_width = std::atoi(root_node->first_attribute("tilewidth")->value());
    this->peice_height = std::atoi(root_node->first_attribute("tileheight")->value());
    
    map_bgm[0] = 0;
    rapidxml::xml_node<>* map_property_node = root_node->first_node("properties");
    if(map_property_node){
        for(auto property_node = map_property_node->first_node("property");property_node; property_node = property_node->next_sibling("property")){
            if(strcmp(property_node->first_attribute("name")->value(), "bgm") == 0){
                strcpy(this->map_bgm, property_node->first_attribute("value")->value());
            }
        }
    }

    // TODO: Multiple Tileset, Terrains, Firstgid
    
    rapidxml::xml_node<>* tileset_node = root_node->first_node("tileset");
    rapidxml::xml_node<>* tileset_image_node = tileset_node->first_node("image");
    bool img_is_trans = (tileset_image_node->first_attribute("trans") != 0);
    Color3i trans_color = {0, 0, 0};
    if(img_is_trans){
        trans_color = HexToColor3i(tileset_image_node->first_attribute("trans")->value());
    }
    
    char img_name[20];
    strcpy(img_name, tileset_image_node->first_attribute("source")->value());
    char full_img_name[40];
    sprintf(full_img_name, "textures/%s", GetFileName(img_name));
     
    //fprintf(stderr, "[%s]\n", full_img_name);
    Image* img = new Image(
        full_img_name,
        img_is_trans,
        trans_color
    );
    //fprintf(stderr, "img load ok\n");
    tile_use = new Tile();
    tile_use->SetImage(img);
    int img_pw = std::atoi(tileset_node->first_attribute("tilewidth")->value());
    int img_ph = std::atoi(tileset_node->first_attribute("tileheight")->value());
    int img_width_count = img->GetWidth()/img_pw;
    int img_height_count = img->GetHeight()/img_ph;
    tile_use->SetSize(img_pw, img_ph);

    fprintf(stderr, "ready to load terrain\n");
    for(auto terrain_node = tileset_node->first_node("tile"); terrain_node; terrain_node = terrain_node->next_sibling("tile")){
        int tile_id = std::atoi(terrain_node->first_attribute("id")->value());
        char tmp_str[20] = {0};
        int status = 0, cc = 0;
        if(terrain_node->first_attribute("terrain") != 0)
            strcpy(tmp_str, terrain_node->first_attribute("terrain")->value());
        for(int lx = 0;tmp_str[lx] != 0;lx++){
            if(tmp_str[lx] == ',') cc++;
            if(tmp_str[lx] == '0') status |= 1<<cc;
        }
        terrain[std::pair<int,int>(tile_id%img_width_count, tile_id/img_width_count)] = status;
        
        auto properties_node = terrain_node->first_node("properties");
        if(properties_node != 0){
            for(auto property_node = properties_node->first_node("property");
                    property_node; property_node = property_node->next_sibling("property")){
                if(strcmp("priority", property_node->first_attribute("name")->value()) == 0){
                    priority[std::pair<int,int>(tile_id%img_width_count, tile_id/img_width_count)]
                        = atoi(property_node->first_attribute("value")->value());
                }
            }
        }
    }

    fprintf(stderr, "ready to load level\n") ;

    //fprintf(stderr, "level new up ok\n");
    int tmp_value;
    for(auto level_node = root_node->first_node("layer"); level_node; level_node = level_node->next_sibling("layer")){
        point** prc = new point*[map_width];
        for(int ly = 0;ly < map_width;ly++)
            prc[ly] = new point[map_height];

        auto data_node = level_node->first_node("data");
        int lx = 0, ly = 0;
        for(auto grid_node = data_node->first_node("tile"); grid_node; grid_node = grid_node->next_sibling("tile")){
            tmp_value = std::atoi(grid_node->first_attribute("gid")->value())-1;
            if(tmp_value == -1)
                prc[lx][ly] = new_point(-1, -1);
            else
                prc[lx][ly] = new_point(tmp_value%img_width_count, tmp_value/img_width_count);
            lx++;
            if(lx == this->map_width){
                lx = 0, ly++;
            }
        }
        map_load.push_back(prc);
    }
    this->level_count = map_load.size();
    
    fprintf(stderr, "Map: Ready to load events in map.\n");
    // Load Events
    auto objectgroup_node = root_node->first_node("objectgroup");
    if(objectgroup_node != 0){
        for(auto event_node = objectgroup_node->first_node("object"); event_node; event_node = event_node->next_sibling("object")){
            if(strcmp(event_node->first_attribute("type")->value(), "Event") != 0) continue;
            EventData new_event_data;
            strcpy(new_event_data.name ,event_node->first_attribute("name")->value());
            new_event_data.x = std::atoi(event_node->first_attribute("x")->value())/img_pw;
            new_event_data.y = std::atoi(event_node->first_attribute("y")->value())/img_ph;
            event_datas.push_back(new_event_data);
        }
    }
 
    fprintf(stderr, "Map:load %s ok\n", path);
    return;
}

bool Map::CanDo(int xx, int yy, int dir)const{
    static int dir_x[] = {0, -1, 1, 0};
    static int dir_y[] = {1, 0, 0, -1};
    int nxx = xx + dir_x[dir], nyy = yy + dir_y[dir];
    if(xx < 0 or xx >= map_width or yy < 0 or yy >= map_height or 
       nxx < 0 or nxx >= map_width or nyy < 0 or nyy >= map_height)
        return false;
    for(int lc = 0;lc < map_load.size();lc++){
        int terrain_now = 0;
        int x = map_load[lc][xx][yy].x , y = map_load[lc][xx][yy].y;
        int nx = map_load[lc][nxx][nyy].x, ny = map_load[lc][nxx][nyy].y;
        if(terrain.count(std::pair<int,int>(x, y)))
            terrain_now = terrain.at(std::pair<int,int>(x, y));
        int terrain_next = 0;
        if(terrain.count(std::pair<int,int>(nx, ny)))
            terrain_next = terrain.at(std::pair<int,int>(nx ,ny));
        if(terrain_next || terrain_now){
            return false;
        }
    }
    return true;
}

char* Map::GetMapBGM(){
    return this->map_bgm;
}
Vec2i Map::GetMapSize(){
    return {this->map_width, this->map_height};
}
 
int Map::GetPriority(int x, int y, int l)const{
    if(x < 0 or y < 0 or x >= map_width or y >= map_height)
        return 0;  
    int xx = map_load[l][x][y].x,
        yy = map_load[l][x][y].y;
    if(priority.count(std::pair<int,int>(xx, yy)) == 0)
        return 0;
    return priority.at(std::pair<int,int>(xx, yy));
}

void Map::RenderATile(float left, float top, float width, float height, int x, int y, int l){
    if(map_load[l][x][y].x == -1) return;
    float delta_x = CONFIG_DELTA_X;
    float delta_y = CONFIG_DELTA_Y;
    tile_use->Render(
        left + (float)x*delta_x,
        top + (float)y*delta_y,
        delta_x, delta_y,
        map_load[l][x][y].x,
        map_load[l][x][y].y,
        l + 1
    );
    return; 
}

void Map::Render(float left, float top, float width, float height){
    float delta_x = CONFIG_DELTA_X;
    float delta_y = CONFIG_DELTA_Y;
    for(int l = 0;l < this->level_count;l++){
        for(int lx = 0;lx < map_width;lx++){
            for(int ly = 0;ly < map_height;ly++){
                if(map_load[l][lx][ly].x == -1) continue;
                tile_use->Render(
                    left + (float)lx*delta_x,
                    top + (float)ly*delta_y,
                    delta_x, delta_y, // TODO: change
                    map_load[l][lx][ly].x,
                    map_load[l][lx][ly].y,
                    l + 1
                );  
            }
        }
    }
    return;
}

void Map::RenderAtPriority(float left, float top, float width, float height, int priority){
    float delta_x = CONFIG_DELTA_X;
    float delta_y = CONFIG_DELTA_Y;
    for(int l = 0;l < this->level_count;l++){
        for(int lx = 0;lx < map_width;lx++){
            for(int ly = 0;ly < map_height;ly++){
                if(map_load[l][lx][ly].x == -1) continue;
                if(GetPriority(lx, ly, l) != priority) continue;
                tile_use->Render(
                    left + (float)lx*delta_x,
                    top + (float)ly*delta_y,
                    delta_x, delta_y, // TODO: change
                    map_load[l][lx][ly].x,
                    map_load[l][lx][ly].y,
                    l + 1
                );  
            }
        }
    }
    return;
}

std::vector<EventData> Map::GetEventDatas(){
    return event_datas;
}

int Map::GetLevelCount()const{
    return this->level_count;
}
