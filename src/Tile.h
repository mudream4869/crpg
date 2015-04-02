#ifndef TILE_DEF
#define TILE_DEF

#include "Image.h"
#include "Type.h"

class Tile{
public:
    Tile(int w, int h, Image* img);
    
    Vec2i GetSize();

    Image* GetImage();
    void Render(float left, float top, float width, float height, int x, int y, int level);

private:
    int piece_width;
    int piece_height;
    Image* image_use;
};

#endif
