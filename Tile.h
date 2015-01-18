#ifndef TILE_DEF
#define TILE_DEF

#include "Image.h"
#include "Type.h"

class Tile{
public:
    Tile();
    
    void SetSize(int w, int h);
    Vec2i GetSize();

    void SetImage(Image* img);
    Image* GetImage();
    void Render(float left, float top, float width, float height, int x, int y, int level);

private:
    int piece_width;
    int piece_height;
    Image* image_use;
};

#endif
