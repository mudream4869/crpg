#include <cstdio>
#include <cstdlib>
#include "SceneLoad.h"

#include "WindowSelect.h"
#include "File.h"
#include "Env.h"
#include "Config.h"

#include "ScenePlay.h"

#include "GlobalVariable.h"

Scene* SceneLoad::scene_load = nullptr;

SceneLoad::SceneLoad(){
    static const int SaveFileCount = 10;
    
    SceneLoad::scene_load = this;

    char* save_name[SaveFileCount];
    for(int lx = 0;lx < SaveFileCount;lx++){
        save_name[lx] = new char[20];
        sprintf(save_name[lx], "SaveFile%d\n", lx+1);
    }

    win_title = new Window(0, 0, 2, 0.3);
    win_title->DrawText(0.2, 0.15, "Where to load your file?");
    win_show = new Window(0.6, 0.3, 1.4, 1.7);
    
    win_select = new WindowSelect(0, 0.3, 0.6, 1.7,
        [this](int index){
            if(index == -1){
                // TODO: Scene Stack
                ScenePlay::Call();
                return;
            }
            fprintf(stderr, "%d\n", index);
            char tmp[20];
            sprintf(tmp, "file%d", index);
            File::LoadFile(tmp);
            ScenePlay::Call();
            return;
        },
        [this](int index){
            // TODO: change
            char tmp[20];
            sprintf(tmp, "file%d", index);
            fprintf(stderr, "%d\n", index);
            File::File* get_file_preload = File::PreloadFile(tmp);
            if(get_file_preload != nullptr){
                win_show->Clear();
                win_show->DrawImage(0, 0.1, 1.3, 1.3, get_file_preload->GetImage());
            }else{
                win_show->Clear();
            }
            //File::File* ret = File::PreloadFile(tmp);
            return;
        },
        save_name, SaveFileCount
    );
    return;
}

void SceneLoad::Call(){
    Scene::scene_certain = SceneLoad::scene_load;
    return;
}

void SceneLoad::InputEvent(Input inp){
    win_select->InputEvent(inp);
    win_show->InputEvent(inp);
    return;
}

void SceneLoad::Render(){
    win_select->Render();
    win_show->Render();
    win_title->Render();
    return;
}
