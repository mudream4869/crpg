#include <map>
#include "Scene.h"
#include "Config.h"

Scene* Scene::scene_certain = nullptr;

Scene::Scene(){
    screen_width = Config::WINDOW_WIDTH;
    screen_height = Config::WINDOW_HEIGHT;
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
