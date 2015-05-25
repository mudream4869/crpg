#ifndef IMAGE_DEF
#define IMAGE_DEF

#include "inc_gl.h"
#include "Type.h"

class Image{
public:
    Image(const char* path, bool is_trans = false, Color3i trans_color={0,0,0});
    ~Image();
    
    int GetHeight() const;
    int GetWidth() const;
    short int GetBits() const;
    GLuint GetTextureId() const;
    
    /**
     *  @brief Render image
     *  @param
     *      x: left
     *      y: top
     *      draw_width: width
     *      draw_height: height
     *      level: z-axis value
     */
    void Render(float x, float y, float draw_width, float draw_height, int level);
    
private:
    
    /**
     *  @brief Load image by bmp method
     *  @param
     *      path: file path with filename
     *      is_trans: is transition
     *      trans_color: transition color
     */
    void __LoadBmp(const char* path, bool is_trans, Color3i trans_color);

    /**
     *  @brief Load image by png method
     *  @param
     *      path: file path with filename
     */
    void __LoadPng(const char* path);
    
    /** Image file info */
    int height;
    int width;
    short int bits;
    GLuint texture_id; 
};

#endif
