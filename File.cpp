#include <cstdio>
#include <cstdlib>
#include <fstream>
#include "File.h"

#include "SysCall.h"
#include "Env.h"
#include "GlobalVariable.h"
#include "Config.h"
#include "ScenePlay.h"

#include "GameObject.h"

#include "loadpng/lodepng.h"

// TODO: script's status?
// TODO: certain scene

static bool __FileCheckExist(const char* filename){
    std::ifstream ifile(filename);
    return ifile.fail() == false;
}

File::File* File::PreloadFile(const char* filename){
    char full_filename[20];
    sprintf(full_filename,"%s%s", CONFIG_PATH_SAVEFILE, filename);
    
    // chekc if file exists
    // TODO: may use stat under mac?
    if(__FileCheckExist(full_filename) == false)
        return nullptr;

    char img_filename[20];
    sprintf(img_filename, "%s.png", full_filename);

    Image* img = nullptr;
    if(__FileCheckExist(img_filename))
        img = new Image(img_filename);

    return new File(img);
}

void File::LoadFile(const char* filename){
    char full_filename[20];
    sprintf(full_filename, "%s%s", CONFIG_PATH_SAVEFILE, filename);
    FILE* fp = fopen(full_filename, "r");
    
    int g_value_count, g_flag_count;
    char name[20]; int value;
    
    GlobalVariable::ClearValue();
    GlobalVariable::ClearFlag();

    fscanf(fp, "%d", &g_value_count);
    for(int lx = 0;lx < g_value_count;lx++){
        fscanf(fp, "%s %d", name, &value);
        GlobalVariable::SetValue(name, value);
    }

    fscanf(fp, "%d", &g_flag_count);
    for(int lx = 0;lx < g_flag_count;lx++){
        fscanf(fp, "%s %d", name, &value);
        GlobalVariable::SetFlag(name, value);
        fprintf(stderr, "load %s -> %d\n", name, value);
    }

    int g_obj_count;
    fscanf(fp, "%d", &g_obj_count);
    for(int lx = 0;lx < g_obj_count;lx++){
        fscanf(fp, "%s %d\n", name, &value);
        GameObjectData::SetGameObjectCount(name, value);
    }

    // Map 
    ScenePlay* scene_play = ScenePlay::scene_play;
    HeroStatus hero_status;
    char get_map_name[20];
    fscanf(fp, "%s", get_map_name);
    fscanf(fp, "%d %d %d", &hero_status.x, &hero_status.y, &hero_status.moving_dir);
    scene_play->ChangeMap(Map::map_pool[get_map_name], hero_status.x, hero_status.y, hero_status.moving_dir);
    
    int event_size;
    fscanf(fp, "%d", &event_size);
    for(int lx = 0;lx < event_size;lx++){
        char event_name[20];
        HeroStatus get_event_status;
        fscanf(fp, "%s", event_name);
        fscanf(fp, "%d %d %d %d %d", &get_event_status.status, 
            &get_event_status.x, &get_event_status.y, 
            &get_event_status.moving_dir, &get_event_status.moving_step);
        Event::event_pool[event_name]->SetStatus(get_event_status);
    }
    return;
}

void File::SaveFile(const char* filename, std::vector<unsigned char>& enc_png){
    char path_fn[20];
    sprintf(path_fn, "%s%s", CONFIG_PATH_SAVEFILE, filename);
    FILE* fp = fopen(path_fn, "w");

    auto& g_value = GlobalVariable::global_value;
    fprintf(fp, "%d\n", (int)g_value.size());
    for(auto it = g_value.begin(); it != g_value.end(); it++){
        fprintf(fp, "%s %d\n", it->first, it->second);
    }
    
    auto& g_flag = GlobalVariable::global_flag;
    fprintf(fp, "%d\n", (int)g_flag.size());
    for(auto it = g_flag.begin(); it != g_flag.end(); it++){
        fprintf(fp, "%s %d\n", it->first, it->second);
    }

    auto& g_object = GameObjectData::gameobject_count;
    fprintf(fp, "%d\n", (int)g_object.size());
    for(auto it = g_object.begin(); it != g_object.end(); it++){
        fprintf(fp, "%s %d\n", it->first, it->second);
    }

    // Map 
    ScenePlay* scene_play = ScenePlay::scene_play;
    HeroStatus hero_status = scene_play->GetHeroStatus();
    fprintf(fp, "%s ", scene_play->GetMapName());
    fprintf(fp, "%d %d %d\n", hero_status.x, hero_status.y, hero_status.moving_dir);
    fprintf(fp, "%d\n", (int) Event::event_pool.size());
    for(auto it = Event::event_pool.begin(); it != Event::event_pool.end(); it++){
        Event* get_event = it->second;
        HeroStatus get_event_status = get_event->GetStatus();
        fprintf(fp, "%s ", it->first);
        fprintf(fp, "%d %d %d %d %d\n", get_event_status.status, 
            get_event_status.x, get_event_status.y, 
            get_event_status.moving_dir, get_event_status.moving_step);
        // the moving queue
    }
    fclose(fp);
    
    char png_filename[20];
    sprintf(png_filename, "%s.png", path_fn); 
    lodepng::save_file(enc_png, png_filename);
    return;
}

//File::File class

File::File::File(Image* _img){
    this->img = _img;
}

bool File::File::HasImage()const{
    return img != nullptr;
}

Image* File::File::GetImage(){
    return img;
}
