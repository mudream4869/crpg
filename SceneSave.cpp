#include "inc_gl.h"
#include <cstdio>
#include <cstdlib>
#include "SceneSave.h"

#include "WindowSelect.h"
#include "File.h"
#include "Config.h"

#include "ScenePlay.h"

#include "loadpng/lodepng.h"

SceneSave* SceneSave::scene_save = nullptr;
unsigned char* SceneSave::snap_img;

SceneSave::SceneSave(){
    static const int SaveFileCount = 10;
    char* save_name[SaveFileCount];

    SceneSave::scene_save = this;
    snap_img = new unsigned char[600*600*4];
     
    for(int lx = 0;lx < SaveFileCount;lx++){
        save_name[lx] = new char[20];
        sprintf(save_name[lx], "SaveFile%d\n", lx+1);
    }
    
    win_title = new Window(0, 0, 2, 0.3);
    win_title->DrawText(0.2, 0.15, "Where to save your file?");
    win_show = new Window(0.6, 0.3, 1.4, 1.7);

    win_select = new WindowSelect(0, 0.3, 0.6, 1.7,
        [this](int index){
            // choose function
            if(index == -1){
                ScenePlay::scene_play->Call();
                return;
            }
            char tmp[20];
            sprintf(tmp, "file%d", index);
            unsigned char* rev_img = new unsigned char[600*600*4];
           
            snap_lock.lock(); 
            for(int ly = 0;ly < 600;ly++)
                for(int lx = 0;lx < 600;lx++)
                    for(int i = 0;i < 4;i++)
                        rev_img[((599-ly)*600 + lx)*4 + i] = snap_img[(ly*600 + lx)*4 + i];
            snap_lock.unlock();
            
            std::vector<unsigned char> vec_raw_img(rev_img, rev_img + 600*600*4);
            delete rev_img;

            std::vector<unsigned char> vec_enc_img;
            lodepng::encode(vec_enc_img, vec_raw_img, 600, 600);
            File::SaveFile(tmp, vec_enc_img);
            ScenePlay::scene_play->Call();
            return;
        },
        [this](int index){
            // select function
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
        save_name, SaveFileCount
    );
    return;
}

void SceneSave::Snap(){
    if(snap_lock.try_lock() == false) return;
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, 600, 600, GL_RGBA, GL_UNSIGNED_BYTE, snap_img);
    snap_lock.unlock();
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
