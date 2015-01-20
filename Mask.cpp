#include <cstdio>
#include <cstdlib>
#include <OpenGL/gl.h> 
#include <OpenGL/glu.h> 
#include <GLUT/glut.h>
#include "Mask.h"

static Color4f start_color, end_color;
static int tick_ms;
static int all_ms;
static bool is_masking;

void Mask::InitMask(){
    is_masking = 0;
    return;
}

void Mask::SetMask(Color4f st, Color4f ed, int time){
    fprintf(stderr, "setmask!!\n");
    start_color = st;
    end_color = ed;
    tick_ms = 0;
    all_ms = time;
    is_masking = true;
    return;
}

bool Mask::IsMasking(){
    return is_masking;
}

void Mask::Clear(){
    is_masking = false;
    return;
}

void Mask::TickEvent(int ms){
    if(tick_ms < all_ms){
        fprintf(stderr, "!!Masking\n");
        tick_ms += 12;
    }
    return;
}

void Mask::Render(){
    fprintf(stderr, "Render mask\n");
    float xs[] = {0, 2, 2, 0};
    float ys[] = {0, 0, 2, 2};

    Color4f cal_color;
    if(tick_ms >= all_ms){
        fprintf(stderr, "end color\n");
        cal_color = end_color;
    }else{
        float all = (float) all_ms;
        float mid = (float) tick_ms;
        cal_color.r = (start_color.r*(all-mid) + end_color.r*mid)/all;
        cal_color.g = (start_color.g*(all-mid) + end_color.g*mid)/all;
        cal_color.b = (start_color.b*(all-mid) + end_color.b*mid)/all;
        cal_color.a = (start_color.a*(all-mid) + end_color.a*mid)/all;
    }
    fprintf(stderr, "%.3f, %.3f, %.3f, %.3f\n", cal_color.r, cal_color.g, cal_color.b, cal_color.a);
    glBegin(GL_POLYGON);
    glColor4f(cal_color.r, cal_color.g, cal_color.b, cal_color.a);

    for(int lx = 3;lx >= 0;lx--){
		xs[lx] = xs[lx] - 1, ys[lx] = 1 - ys[lx];
		glVertex3f((GLfloat)(xs[lx]), (GLfloat)(ys[lx]), 0.01*(float)2);
	}
    glColor4f(1, 1, 1, 1);
    glEnd();
    return;
}

