#include "inc_gl.h"

#include <cstdio>
#include <cstring>
#include <cmath>

#include "Type.h"
#include "Constant.h"

int __HexChToValue(char c){
    if(c <= '9' and c >= '0')
        return c - '0';
    else
        return c - 'a' + 10;
}


int Input2Dir(Input inp){
    if(inp.type == INPUT_NORMAL_KEY_DOWN){
        if(inp.normal_key == 'a') return DIR_LEFT;
        if(inp.normal_key == 'w') return DIR_UP;
        if(inp.normal_key == 's') return DIR_DOWN;
        if(inp.normal_key == 'd') return DIR_RIGHT;
    }else if(inp.type == INPUT_SPECIAL_KEY_DOWN){
        if(inp.special_key == GLUT_KEY_UP) return DIR_UP;
        if(inp.special_key == GLUT_KEY_DOWN) return DIR_DOWN;
        if(inp.special_key == GLUT_KEY_LEFT) return DIR_LEFT;
        if(inp.special_key == GLUT_KEY_RIGHT) return DIR_RIGHT;
    }
    return DIR_NONE;
}

Color3i HexToColor3i(const char* str){
    Color3i ret_col;
    ret_col.r = (__HexChToValue(str[0])*16 + __HexChToValue(str[1]));
    ret_col.g = (__HexChToValue(str[2])*16 + __HexChToValue(str[3]));
    ret_col.b = (__HexChToValue(str[4])*16 + __HexChToValue(str[5]));
    return ret_col;
}

Color3i operator-(const Color3i& a, const Color3i& b){
    Color3i ret_col;
    ret_col.r = a.r + b.r;
    ret_col.g = a.g + b.g;
    ret_col.b = a.b + b.b;
    return ret_col;
}

double LenOfColor3i(Color3i in){
   return std::sqrt(in.r*in.r + in.g*in.g + in.b*in.b);
}

Vec2i Str2Vec2i(const char* str){
    int x, y;
    sscanf(str, "(%d,%d)", &x, &y);
    return {x, y};
}

WriteType NewWriteType(int type, int int_value, const char* string_value){
    WriteType ret;
    ret.type = type;
    ret.int_value = int_value;
    strcpy(ret.string_value, string_value);
    return ret;
}

bool operator==(Vec2i a, Vec2i b){
    return a.x == b.x and a.y == b.y;
}
