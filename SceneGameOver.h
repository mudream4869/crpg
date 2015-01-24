#ifndef SCENE_GAME_OVER
#define SCENE_GAME_OVER

#include "Scene.h"
#include "Image.h"

class SceneGameOver: public Scene{
public:
    SceneGameOver();
    void CallScene();
    void InputEvent(Input inp);
    void Render();
private:
    Image* gameover_img;
};

#endif
