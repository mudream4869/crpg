#include "inc_gl.h"
#include <cstdio>
#include <cstdlib>
#include "SceneSave.h"

#include "WindowSelect.h"
#include "File.h"
#include "Env.h"
#include "Config.h"

#include "ScenePlay.h"

#include "loadpng/lodepng.h"

SceneSave* SceneSave::scene_save = nullptr;
unsigned char* SceneSave::snap_img;

SceneSave::SceneSave(){
    static const int SaveFileCount = 9;
    char* save_name[SaveFileCount];

    SceneSave::scene_save = this;
    snap_img = new unsigned char[600*600*4];
     
    for(int lx = 0;lx < SaveFileCount;lx++){
        save_name[lx] = new char[20];
        sprintf(save_name[lx], "SaveFile%d\n", lx+1);
    }
    
    win_title = new Window(0, 0, 2, 0.3);
    win_title->DrawText(0.2, 0.15, "Where to save your file?");

    win_select = new WindowSelect(0, 0.3, 1, 1.7,
        [this](int index){
            if(index == -1){
                ScenePlay::Call();
                return;
            }
            char tmp[20];
            sprintf(tmp, "file%d", index);
            
            unsigned char* rev_img = new unsigned char[600*600*4];
            for(int ly = 0;ly < 600;ly++)
                for(int lx = 0;lx < 600;lx++)
                    for(int i = 0;i < 4;i++)
                        rev_img[((600-ly)*600 + lx)*4 + i] = snap_img[(ly*600 + lx)*4 + i];
            std::vector<unsigned char> vec_raw_img(rev_img, rev_img + 600*600*4);
            delete rev_img;

            std::vector<unsigned char> vec_enc_img;
            lodepng::encode(vec_enc_img, vec_raw_img, 600, 600);
            File::SaveFile(tmp, vec_enc_img);
            ScenePlay::Call();
            return;
        },
        [this](int index){
            // TODO: change
            char tmp[20];
            sprintf(tmp, "file%d", index);
            //File::File* ret = File::PreloadFile(tmp);
            return;
        },
        save_name, SaveFileCount
    );
    win_show = new Window(1, 0.3, 1, 1.7);
    return;
}

void SceneSave::Snap(){
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, 600, 600, GL_RGBA, GL_UNSIGNED_BYTE, snap_img);
    return;
}

void SceneSave::Call(){
    // load screen
    // 600 should be width, height
    Scene::scene_certain = SceneSave::scene_save;
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
    win_title->Render();
    return;
}
