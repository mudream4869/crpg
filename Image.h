#ifndef IMAGE_DEF
#define IMAGE_DEF

#include "inc_gl.h"
#include "Type.h"

class Image{
public:
    Image(const char* path, bool is_trans = false, Color3i trans_color={0,0,0});
    ~Image();
    int GetHeight();

    int GetWidth();
    short int GetBits();
    GLuint GetTextureId();

    // Rename to Render
    void Render(float x, float y, float draw_width, float draw_height, int level);
    
private:

    void __LoadBmp(const char* path, bool is_trans, Color3i trans_color);
    void __LoadPng(const char* path);

    int height;
    int width;
    short int bits;
    GLuint texture_id; 
};

#endif  
