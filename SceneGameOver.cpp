#include "SceneGameOver.h"
#include "AudioSystem.h"

#include "SceneStart.h"

Scene* SceneGameOver::scene_gameover;

SceneGameOver::SceneGameOver(){
    SceneGameOver::scene_gameover = this;
    this->gameover_img = new Image("pictures/gameover.png");
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

