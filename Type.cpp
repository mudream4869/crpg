#include <cstdio>
#include <cmath>
#include "Type.h"

int __HexChToValue(char c){
    if(c <= '9' and c >= '0')
        return c - '0';
    else
        return c - 'a' + 10;
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
