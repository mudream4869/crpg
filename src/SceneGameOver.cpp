#include "SceneGameOver.h"
#include "AudioSystem.h"

#include "SceneStart.h"

#include "Config.h"

Scene* SceneGameOver::scene_gameover;

SceneGameOver::SceneGameOver(){
    SceneGameOver::scene_gameover = this;
    char fn[40];
    sprintf(fn, "%s/gameover.png", Config::PATH_PICTUREFILE); 
    this->gameover_img = new Image(fn);
    return;
}

void SceneGameOver::Call(){
    AudioSystem::PlayBGM("Reflection_Pool.wav") ;
    Scene::scene_certain = SceneGameOver::scene_gameover;
    return;
}

void SceneGameOver::InputEvent(Input inp){
    if(inp.type != INPUT_NORMAL_KEY_DOWN) return;
    SceneStart::scene_start->Call();
    return;
}

void SceneGameOver::Render(){
    this->gameover_img->Render(0, 0, 2, 2, 1);
    return;
}

