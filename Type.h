// Type definition

#ifndef TYPE_DEF
#define TYPE_DEF

const int INPUT_NULL = 0;
const int _INPUT_MOUSE = 1;
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

struct _vec2i{
    int x, y;
    _vec2i(int _x = 0, int _y = 0){
        x = _x, y = _y;
    }
};

typedef _vec2i Vec2i;

struct _hero_status{
    int status;
    int moving_dir;
    int face_dir;
    int moving_step;
    int sleep_ms;
    int x, y;
    _hero_status(){
        status = 0;
        moving_dir = 0;
        face_dir = 0;
        moving_step = 0;
        sleep_ms = 0;
        x = y = 0;
        return;
    }
};

typedef _hero_status HeroStatus;

typedef struct _mover_status{
    int status;
    int moving_dir;
    int moving_step;
    int x, y;
}MoverStatus;

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

WriteType NewWriteType(int type, int int_value, const char* string_value);

#endif
