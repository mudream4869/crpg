#ifndef WINDOW_DEF
#define WINDOW_DEF
#include <vector>
#include <cwchar>

#include "Type.h"
#include "Image.h"

#include "minftgl/minftgl.h"

const int WINDOW_DRAW_NULL = 0;
const int WINDOW_DRAW_TEXT = 1;
const int WINDOW_DRAW_WTEXT = 2;
const int WINDOW_DRAW_BOX = 3;
const int WINDOW_DRAW_IMAGE = 4;

class Window{
public:
    Window(float _left, float _top, float _width, float _height);
    ~Window();

    void DrawText(float x, float y, const char* str);
    void DrawWText(float x, float y, const wchar_t* wstr);
    void DrawBox(float x, float y, float w, float h, Color4f color);
    void DrawImage(float x, float y, float w, float h, Image* img);

    void Clear();
    
    virtual void Render();
    virtual void InputEvent(Input inp);
    virtual void TickEvent(int a); 
    virtual void Update();

    static minftgl::Font* use_font;

protected:
    float left, top, width, height;
    struct WindowDraw{
        int DrawId;
        char* Str;
        Vec2f Pos;
        Vec2f Size;
        Color4f Color;
        void* SpecialPointer;
    };
    std::vector<WindowDraw> window_draw;
    void RenderBase();
};

#endif
