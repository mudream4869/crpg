#ifndef SCENE_GAME_OVER
#define SCENE_GAME_OVER

#include "Scene.h"
#include "Image.h"

class SceneGameOver: public Scene{
public:
    SceneGameOver();
    void InputEvent(Input inp);
    void Render();
    void Call();
    
    static Scene* scene_gameover;

private:
    Image* gameover_img;
};

#endif
