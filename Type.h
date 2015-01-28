// Type definition

#ifndef TYPE_DEF
#define TYPE_DEF

const int INPUT_NULL = 0;
const int INPUT_MOUSE = 1;
const int INPUT_NORMAL_KEY_DOWN = 2;
const int INPUT_NORMAL_KEY_UP = 3;
const int INPUT_SPECIAL_KEY_DOWN = 4;
const int INPUT_SPECIAL_KEY_UP = 5;

typedef struct _input{
    int type;
    int mouse_x, mouse_y;
    unsigned char normal_key;
    int special_key;
}Input;

int Input2Dir(Input inp);

typedef struct _eventdata{
    char name[20];
    int x;
    int y;
}EventData;

typedef struct _color4f{
    float r, g, b, a;
}Color4f;

typedef struct _color3i{
    int r, g, b;
}Color3i;

typedef struct _vec2f{
    float x, y;
}Vec2f;

typedef struct _vec2i{
    int x, y;
}Vec2i;

typedef struct _hero_status{
    int status;
    int moving_dir;
    int moving_step;
    int x, y;
}HeroStatus;

Color3i HexToColor3i(const char* str);
Color3i operator-(const Color3i& a, const Color3i& b);
double LenOfColor3i(Color3i in);

Vec2i Str2Vec2i(const char* str);

const int WRITE_NULL = 0;
const int WRITE_INT = 1;
const int WRITE_STRING = 2;

struct WriteType{
    int type;
    int int_value;
    char string_value[20];
};

#endif
