#include <cstdio>
#include <cstdlib>
#include "SceneLoad.h"

#include "WindowSelect.h"
#include "File.h"
#include "Config.h"

#include "ScenePlay.h"

#include "GlobalVariable.h"

SceneLoad* SceneLoad::scene_load = nullptr;

SceneLoad::SceneLoad(){
    static const int SaveFileCount = 10;
    
    SceneLoad::scene_load = this;

    std::vector<std::wstring> save_name;
    for(int lx = 0;lx < SaveFileCount;lx++){
        wchar_t str[20];
        swprintf(str, 20, L"SaveFile%d\n", lx+1);
        save_name.push_back(str);
    }

    win_title = new Window(0, 0, 2, 0.3);
    win_title->DrawText(0.2, 0.15, "Where to load your file?");
    win_show = new Window(0.6, 0.3, 1.4, 1.7);
    
    win_select = new WindowSelect(0, 0.3, 0.6, 1.7,
        [this](int index){
            if(index == -1){
                // TODO: Scene Stack
                scene_ret->Call();
                return;
            }
            char tmp[20];
            sprintf(tmp, "file%d", index);
            
            File::File* get_file_preload  = File::PreloadFile(tmp);
            if(get_file_preload == nullptr)
                return;

            File::LoadFile(tmp);
            ScenePlay::scene_play->Call();
            return;
        },
        [this](int index){
            // function change
            char tmp[20];
            sprintf(tmp, "file%d", index);
            File::File* get_file_preload = File::PreloadFile(tmp);
            if(get_file_preload != nullptr){
                win_show->Clear();
                win_show->DrawImage(0, 0.1, 1.3, 1.3, get_file_preload->GetImage());
            }else{
                win_show->Clear();
                win_show->DrawText(0.5, 0.3, "No file ._.");
            }
            return;
        },
        save_name
    );
    return;
}

void SceneLoad::Call(Scene* ret){
    Scene::scene_certain = SceneLoad::scene_load;
    scene_ret = ret;
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
