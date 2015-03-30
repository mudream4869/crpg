#include "inc_gl.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Window.h"

minftgl::Font* Window::use_font = nullptr;

Window::Window(float _left, float _top, float _width, float _height){
    left = _left,
    top = _top,
    width = _width,
    height = _height;
    return;
}

Window::~Window(){
    this->Clear();
    return;
}

void Window::DrawText(float x, float y, const char* str){
    float dy = 0.1;
    int pre_ptr = 0;
    char tmp[100]; strcpy(tmp, str);
    for(int lx = 0;;lx++){
        if(tmp[lx] == '\n'){
            WindowDraw windraw;
            windraw.DrawId = WINDOW_DRAW_TEXT;
            windraw.Pos = {x, y};
            windraw.Str = new char[lx - pre_ptr + 3];
            tmp[lx] = 0;
            strcpy(windraw.Str, tmp + pre_ptr);
            window_draw.push_back(windraw);
            pre_ptr = lx+1;
            y += dy;
        }else if(tmp[lx] == 0){
            WindowDraw windraw;
            windraw.DrawId = WINDOW_DRAW_TEXT;
            windraw.Pos = {x, y};
            windraw.Str = new char[lx - pre_ptr + 3];
            tmp[lx] = 0;
            strcpy(windraw.Str, tmp + pre_ptr);
            window_draw.push_back(windraw);
            break;
        }
    }
    return;
}

void Window::DrawWText(float x, float y, const wchar_t* wstr){
    WindowDraw windraw;
    windraw.DrawId = WINDOW_DRAW_WTEXT;
    windraw.Pos = {x, y};
    windraw.SpecialPointer = (void*)(new minftgl::Label(wstr, use_font));
    window_draw.push_back(windraw);
    return;
}

void Window::DrawBox(float x, float y, float w, float h, Color4f color){
    WindowDraw windraw;
    windraw.DrawId = WINDOW_DRAW_BOX;
    windraw.Pos = {x, y};
    windraw.Size = {w, h};
    windraw.Color = color;
    window_draw.push_back(windraw); 
    return;
}

void Window::DrawImage(float x, float y, float w, float h, Image* img){
    WindowDraw windraw;
    windraw.DrawId = WINDOW_DRAW_IMAGE;
    windraw.Pos = {x, y};
    windraw.Size = {w, h};
    windraw.SpecialPointer = (void *)img;
    window_draw.push_back(windraw); 
    return;
}

void Window::Clear(){
    for(int lx = 0;lx < window_draw.size();lx++){
        WindowDraw windraw = window_draw[lx];
        if(windraw.DrawId == WINDOW_DRAW_TEXT)
            delete[] windraw.Str;
        else if(windraw.DrawId == WINDOW_DRAW_WTEXT)
            delete (minftgl::Label*)(windraw.SpecialPointer);
    }
    window_draw.clear();
    return;
}

void Window::RenderBase(){
    float xs[] = {left, left + width, left + width, left};
    float xc[] = {0, 1, 1, 0};
    float ys[] = {top, top, top + height, top + height};
    float yc[] = {0, 0, 1, 1};

    //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_POLYGON);
    glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
    for(int lx = 3;lx >= 0;lx--){
		xs[lx] = xs[lx] - 1, ys[lx] = 1 - ys[lx];
		glVertex3f((GLfloat)(xs[lx]), (GLfloat)(ys[lx]), 0.01*(float)2);
	}
    glColor4f(1, 1, 1, 1);
    glEnd();
    return;
}

void Window::Update(){
    return;
}

void Window::Render(){
    this->RenderBase();
    for(int lx = 0;lx < this->window_draw.size();lx++){
        WindowDraw windraw = window_draw[lx];
        if(windraw.DrawId == WINDOW_DRAW_TEXT){
            glColor3f(1,1,1);
            float x = windraw.Pos.x + this->left, y = windraw.Pos.y + this->top;
            x = x - 1 , y = 1 - y;
            glRasterPos2f((GLfloat)x,(GLfloat)y);
            for(int c = 0; windraw.Str[c] != 0; c++)
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, windraw.Str[c]);
        }else if(windraw.DrawId == WINDOW_DRAW_WTEXT){
            ((minftgl::Label*)windraw.SpecialPointer)->Render(windraw.Pos.x, windraw.Pos.y); 
        }else if(windraw.DrawId == WINDOW_DRAW_BOX){
            Color4f col = windraw.Color;
            glColor4f(col.r, col.g, col.b, col.a);
            float _left = windraw.Pos.x + this->left, _top = windraw.Pos.y + this->top;
            float _width = windraw.Size.x, _height = windraw.Size.y;

            float xs[] = {_left, _left + _width, _left + _width, _left};
            float xc[] = {0, 1, 1, 0};
            float ys[] = {_top, _top, _top + _height, _top + _height};
            float yc[] = {0, 0, 1, 1};
            glBegin(GL_POLYGON);
            //glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
            for(int lx = 3;lx >= 0;lx--){
                xs[lx] = xs[lx] - 1, ys[lx] = 1 - ys[lx];
                glVertex3f((GLfloat)(xs[lx]), (GLfloat)(ys[lx]), 0.01*(float)2);
            }
            glColor4f(1, 1, 1, 1);
            glEnd();
        }else if(windraw.DrawId == WINDOW_DRAW_IMAGE){
            Image* img = (Image*) windraw.SpecialPointer;
            img->Render(windraw.Pos.x + this->left, windraw.Pos.y + this->top, windraw.Size.x, windraw.Size.y, 5);
        }
    }
    return;
}

void Window::InputEvent(Input inp){
    return;
}

void Window::TickEvent(int a){
    return;
} 
