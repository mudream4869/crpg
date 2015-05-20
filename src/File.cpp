#include <cstdio>
#include <cstdlib>
#include <fstream>
#include "File.h"

#include "SysCall.h"
#include "GlobalVariable.h"
#include "Config.h"
#include "ScenePlay.h"

#include "GameObject.h"

#include "lodepng/lodepng.h"

// TODO: script's status?

static bool __FileCheckExist(const char* filename){
    std::ifstream ifile(filename);
    return ifile.fail() == false;
}

File::File* File::PreloadFile(const char* filename){
    char full_filename[20];
    sprintf(full_filename,"%s/%s", Config::PATH_SAVEFILE, filename);
    
    // chekc if file exists
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
    sprintf(full_filename, "%s/%s", Config::PATH_SAVEFILE, filename);
    FILE* fp = fopen(full_filename, "r");
    
    int g_value_count, g_flag_count;
    char name[20]; int value;
    
    GlobalVariable::ClearValue();
    GlobalVariable::ClearFlag();
    
    /** Read values */
    fscanf(fp, "%d", &g_value_count);
    for(int lx = 0;lx < g_value_count;lx++){
        fscanf(fp, "%s %d", name, &value);
        GlobalVariable::SetValue(name, value);
    }
    
    /** Read flags */
    fscanf(fp, "%d", &g_flag_count);
    for(int lx = 0;lx < g_flag_count;lx++){
        fscanf(fp, "%s %d", name, &value);
        GlobalVariable::SetFlag(name, value);
        fprintf(stderr, "load %s -> %d\n", name, value);
    }
    
    /** Read GameObject */
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
    
    /** Read Event Setting */
    int event_size;
    fscanf(fp, "%d", &event_size);
    for(int lx = 0;lx < event_size;lx++){
        char event_name[20];
        HeroStatus get_event_status;
        fscanf(fp, "%s", event_name);
        fscanf(fp, "%d %d %d %d %d", &get_event_status.status, 
            &get_event_status.x, &get_event_status.y, 
            &get_event_status.moving_dir, &get_event_status.moving_step);
        Event::event_pool[event_name]->status = get_event_status;
    }
    fclose(fp);
    return;
}

void File::SaveFile(const char* filename, std::vector<unsigned char>& enc_png){
    char path_fn[20];
    sprintf(path_fn, "%s/%s", Config::PATH_SAVEFILE, filename);
    FILE* fp = fopen(path_fn, "w");
    
    /** Write values */
    auto get_values = GlobalVariable::DumpValues();
    fprintf(fp, "%d\n", (int)get_values.size());
    for(auto it : get_values){
        fprintf(fp, "%s %d\n", it.first.c_str(), it.second);
    }
    
    /** Write flags */
    auto get_flags = GlobalVariable::DumpFlags();
    fprintf(fp, "%d\n", (int)get_flags.size());
    for(auto it : get_flags){
        fprintf(fp, "%s %d\n", it.first.c_str(), it.second);
    }
    
    /** Write GameObject */
    auto get_objects = GameObjectData::DumpCounts();
    fprintf(fp, "%d\n", (int)get_objects.size());
    for(auto it : get_objects){
        fprintf(fp, "%s %d\n", it.first.c_str(), it.second);
    }

    // Map 
    ScenePlay* scene_play = ScenePlay::scene_play;
    HeroStatus hero_status = scene_play->hero_use->status;
    fprintf(fp, "%s ", scene_play->GetMapName().c_str());
    fprintf(fp, "%d %d %d\n", hero_status.x, hero_status.y, hero_status.moving_dir);
    
    /** Write Event Setting */
    fprintf(fp, "%d\n", (int) Event::event_pool.size());
    for(auto it = Event::event_pool.begin(); it != Event::event_pool.end(); it++){
        Event* get_event = it->second;
        HeroStatus get_event_status = get_event->status;
        fprintf(fp, "%s ", it->first);
        fprintf(fp, "%d %d %d %d %d\n", get_event_status.status, 
            get_event_status.x, get_event_status.y, 
            get_event_status.moving_dir, get_event_status.moving_step);
        //TODO: the moving queue
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
