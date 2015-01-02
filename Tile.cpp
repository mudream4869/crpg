#include <OpenGL/gl.h> 
#include <OpenGL/glu.h> 
#include <GLUT/glut.h>
#include <cstdio>
#include "Tile.h"

Tile::Tile(){
    piece_width = 32;
    piece_height = 32;
    image_use = nullptr;
    return;
} 

void Tile::SetSize(int w, int h){
    this->piece_width = w;
    this->piece_height = h;
    return;
}

void Tile::SetImage(Image* img){
    this->image_use = img;
    return;
} 

Image* Tile::GetImage(){
    return this->image_use;
}

void Tile::Render(float left, float top, float width, float height, int x, int y, int level){
    // AABB
    //fprintf(stderr, "Width = %d, Height = %d\n", image_use->GetWidth(), image_use->GetHeight());

    float x1 = left, x2 = left + width;
    float y1 = top, y2 = top + height;
    
    float xc1 = this->piece_width*(float)x/(float)this->image_use->GetWidth() + 0.002,
          xc2 = this->piece_width*(float)(x+1)/(float)this->image_use->GetWidth() - 0.002;

    float yc1 = this->piece_height*(float)y/(float)this->image_use->GetHeight() + 0.002,
          yc2 = this->piece_height*(float)(y+1)/(float)this->image_use->GetHeight() - 0.002;
    
    //fprintf(stderr, "xc1 = %f, xc2 = %f, yc1 = %f, yc2 = %f\n", xc1, xc2, yc1, yc2);
    //fprintf(stderr, "x1 = %f, x2 = %f, y1 = %f, y2 = %f\n", x1, x2, y1, y2);
     
    float xs[] = {x1, x2, x2, x1},
          xc[] = {xc1, xc2, xc2, xc1};
    float ys[] = {y1, y1, y2, y2},
          yc[] = {yc1, yc1, yc2, yc2};

    glEnable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, this->image_use->GetTextureId());
    
    glBegin(GL_POLYGON);
    for(int lx = 3;lx >= 0;lx--){
		xs[lx] = xs[lx] - 1, ys[lx] = 1 - ys[lx];
        glTexCoord2d((GLfloat)(xc[lx]), (GLfloat)(yc[lx]));
        glVertex3f((GLfloat)(xs[lx]), (GLfloat)(ys[lx]), 0.01*(float)(level));
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    return;
}
