#include <cstdio>
#include <cstdlib>
#include "SceneSave.h"

#include "WindowSelect.h"
#include "File.h"
#include "Env.h"
#include "Config.h"

SceneSave::SceneSave():Scene(2, 2){
    static const int SaveFileCount = 12;
    char* save_name[SaveFileCount];
    for(int lx = 0;lx < SaveFileCount;lx++){
        save_name[lx] = new char[20];
        sprintf(save_name[lx], "SaveFile%d\n", lx+1);
    }
    win_select = new WindowSelect(0, 0, 1, 2,
        [this](int index){
            if(index == -1){
                EnvSetCertainScene("scene_play");
                return;
            }
            // TODO:choose
            fprintf(stderr, "%d\n", index);
            char tmp[20];
            sprintf(tmp, "file%d", index);
            File::SaveFile(tmp);
            EnvSetCertainScene("scene_play");
            return;
        },
        [this](int index){
            // TODO: change
            char tmp[20];
            sprintf(tmp, "file%d", index);
            fprintf(stderr, "%d\n", index);
            //File::File* ret = File::PreloadFile(tmp);
            return;
        },
        save_name, SaveFileCount
    );
    win_show = new Window(1, 0, 1, 2);
    return;
}
void SceneSave::InputEvent(Input inp){
    win_select->InputEvent(inp);
    win_show->InputEvent(inp);
    return;
}
void SceneSave::Render(){
    win_select->Render();
    win_show->Render();
    return;
}
