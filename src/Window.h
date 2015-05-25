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

/**
 *  @brief Definition of basic window type
 */

class Window{
public:
    Window(float _left, float _top, float _width, float _height);
    ~Window();
    
    /**
     *  @brief Draw text in window
     *  @param
     *      x: left to window
     *      y: top to window
     *      str: text in c-string 
     */
    void DrawText(float x, float y, const char* str);

    /**
     *  @brief Draw wide text in window
     *  @param 
     *      x: left to window
     *      y: top to window
     *      wstr: wide string in c-string
     */
    void DrawWText(float x, float y, const wchar_t* wstr);

    /**
     *  @brief Draw Solid Rectangle
     *  @param 
     *      x: left to window
     *      y: top to window
     *      w: width
     *      h: height
     *      color: color in (r, g, b, a) form
     */
    void DrawBox(float x, float y, float w, float h, Color4f color);

    /**
     *  @brief Draw Image
     *  @param
     *      x: left to window
     *      y: top to window
     *      w: width
     *      h: height
     *      img: Image to draw
     */
    void DrawImage(float x, float y, float w, float h, Image* img);
    
    /**
     *  @brief Clear all drawed things
     */
    void Clear();
    
    /**
     *  @brief Draw at GUI Window 
     */
    virtual void Render();

    /**
     *  @brief Trigger InputEvent
     */
    virtual void InputEvent(Input inp);

    /**
     *  @brief Trigger TickEvent
     */
    virtual void TickEvent(int a); 

    /**
     *  @brief Update Content
     */
    virtual void Update();
    
    /**
     *  @brief Store using font in wide string
     */
    static minftgl::Font* use_font;

protected:
    float left, top, width, height;

    struct WindowDraw{
        int DrawId;
        char* Str;
        wchar_t* WStr;
        Vec2f Pos;
        Vec2f Size;
        Color4f Color;
        void* SpecialPointer;
    };
    std::vector<WindowDraw> window_draw;

    /**
     *  @brief Render Window Base Color
     */
    void RenderBase();
};

#endif
