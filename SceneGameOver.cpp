#include "SceneGameOver.h"
#include "AudioSystem.h"
#include "Env.h"

SceneGameOver::SceneGameOver(){
    this->gameover_img = new Image("pictures/gameover.png");
    return;
}

void SceneGameOver::CallScene(){
    AudioSystem::PlayBGM("Reflection_Pool.wav") ;
    return;
}

void SceneGameOver::InputEvent(Input inp){
    if(inp.InputType != INPUT_KEYPRESS) return;
    EnvSetCertainScene("scene_start");
    // TODO: Call SceneStart
    return;
}

void SceneGameOver::Render(){
    this->gameover_img->Render(0, 0, 2, 2, 1);
    return;
}

