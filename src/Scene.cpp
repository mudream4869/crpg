#include <map>
#include "Scene.h"
#include "Constant.h"

Scene* Scene::scene_certain = nullptr;

Scene::Scene(){
    screen_width = Constant::WINDOW_WIDTH;
    screen_height = Constant::WINDOW_HEIGHT;
    return;
}

void Scene::InputEvent(Input inp){
    return; 
}

void Scene::TickEvent(int delta_time){
    return;
}

void Scene::Render(){
    return;
}

void Scene::Call(){
    Scene::scene_certain = this;
    return;
}
