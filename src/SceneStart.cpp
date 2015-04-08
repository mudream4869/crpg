#include <cstdlib>
#include <cwchar>

#include "SceneStart.h"
#include "Image.h"

#include "AudioSystem.h"
#include "ScenePlay.h"
#include "SceneLoad.h"

#include "Config.h"

#include "Constant.h"

Scene* SceneStart::scene_start = nullptr;

SceneStart::SceneStart(){

    SceneStart::scene_start = this;

    select_box = new Window(0.7, 1, 0.6, 0.53);
    select_index = 0;
    bg = new Image(Config::SCENESTART_IMG_NAME);
    UpdateSelectBox();
    return;
}

void SceneStart::Call(){
    AudioSystem::StopBGM();
    if(Config::SCENESTART_BGM_NAME[0])
        AudioSystem::PlayBGM(Config::SCENESTART_BGM_NAME); 
    Scene::scene_certain = SceneStart::scene_start;
    return;
}

void SceneStart::UpdateSelectBox(){
    select_box->Clear();
    const wchar_t str[][10] = {L"新的故事", L"舊的日記", L"離開"};
    for(int lx = 0;lx < 3;lx++){
        if(lx == select_index)
            select_box->DrawBox(0.08, 0.16*lx + 0.03, 0.4, 0.14, {0.7, 0.3, 0.4, 0.5});
        select_box->DrawWText(0.1, 0.16*lx + 0.135, str[lx]);
    }
    return;
}

void SceneStart::InputEvent(Input inp){
    if(inp.type == INPUT_NORMAL_KEY_DOWN){
        if(inp.normal_key == 13){
            AudioSystem::PlaySE("item_choose.ogg");
            if(select_index == 0){
                int dir = 0;
                if(strcmp(Config::GAME_START_DIR, "left") == 0){
                    dir = 1;
                }else if(strcmp(Config::GAME_START_DIR, "right") == 0 ){
                    dir = 2;
                }else if(strcmp(Config::GAME_START_DIR, "up") == 0){
                    dir = 3;
                }else
                    dir = 0;
                ScenePlay::scene_play->Call(
                    Map::map_pool[Config::GAME_START_MAP_NAME],
                    Config::GAME_START_POS.x,
                    Config::GAME_START_POS.y,
                    dir
                );
                return;
            }else if(select_index == 1){
                SceneLoad::scene_load->Call(this);
                return; 
            }else if(select_index == 2){
                exit(0);
            }
        }
    }
    int dir = Input2Dir(inp);
    bool change = false;
    if(dir == Constant::DIR_UP and select_index > 0)
        select_index--, change = true, AudioSystem::PlaySE("item_switch.ogg");
    else if(dir == Constant::DIR_DOWN and select_index < 2)
        select_index++, change = true, AudioSystem::PlaySE("item_switch.ogg");
    if(change)
        UpdateSelectBox();
    return;
}

void SceneStart::TickEvent(int delta_time){
    return;
}

void SceneStart::Render(){
    bg->Render(0, 0, screen_width, screen_height, 1);
    select_box->Render();
    return;
}
