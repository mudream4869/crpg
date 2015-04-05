#include "inc_gl.h"
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "Image.h"
#include "Tool.h"

#include "lodepng/lodepng.h"
#include "debugger/debugger.h"

#define __BMPSHIFT 54

Image::Image(const char* path, bool is_trans, Color3i trans_color){
    fprintf(stderr,"Image: ready to load %s\n", path);
    int sl = strlen(path);

    // allocate a texture name
    glGenTextures( 1, &this->texture_id);
    // select our current texture
    glBindTexture( GL_TEXTURE_2D, texture_id);

    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    // when texture area is small, bilinear filter the closest MIP map
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // when texture area is large, bilinear filter the first MIP map
    //glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // build our texture MIP maps
     
    if(strcmp(path+sl-3, "bmp") == 0)
        this->__LoadBmp(path, is_trans, trans_color);
    else if(strcmp(path+sl-3, "png") == 0)
        this->__LoadPng(path);
    
    fprintf(stderr,"Image: load %s ok\n", path);
    return;
}

void Image::__LoadBmp(const char* path, bool is_trans, Color3i trans_color){
    FILE* file = fopen(path, "rb");
    // open texture data
    if (file == NULL){ 
	    fprintf(stderr, "Fail to load bmp file!\n");
        exit(1);
        return;
    }

    fseek(file, 18, SEEK_SET);
    fread(&width, sizeof(width), 1, file);
    fread(&height, sizeof(height), 1, file);

    bool HeightNeg = false;
    if(height < 0){
        HeightNeg = true;
        height = (~height) + 1;
    }
 
    fseek(file, 0x1C, SEEK_SET);
    fread(&bits, sizeof(bits), 1, file);
 
    Debugger::Print("Load img, width = %d, height = %d\n", width, height);
    Debugger::Print("Img bits = %d\n", (int)bits);

    int byte_count = (int)this->bits/8;
    unsigned char* data = (unsigned char *)malloc(width*height*byte_count + __BMPSHIFT);

    // allocate buffer
    fseek(file, 0, SEEK_SET);
    fread(data, width*height*byte_count + __BMPSHIFT, 1, file);
    fclose(file);
    //BMP
    
    unsigned char* datt4 = (unsigned char *)malloc(width*height*4);
    bool last_trans = false;
    bool now_trans = false;
    for(int lx = 0;lx < width*height;++lx){
        datt4[4*lx + 0] = data[lx*byte_count + __BMPSHIFT + 2];
        datt4[4*lx + 1] = data[lx*byte_count + __BMPSHIFT + 1];
        datt4[4*lx + 2] = data[lx*byte_count + __BMPSHIFT + 0];
        last_trans = now_trans;
        now_trans = Absi(trans_color.r - (int)datt4[4*lx + 0]) <= 1
                   and Absi(trans_color.g - (int)datt4[4*lx + 1]) <= 1
                   and Absi(trans_color.b - (int)datt4[4*lx + 2]) <= 1;
        if(is_trans and (now_trans) )
            datt4[4*lx + 3] = 0;
        else{
            if(byte_count == 4)
                datt4[4*lx + 3] = data[lx*byte_count + 3 + __BMPSHIFT];
            else
                datt4[4*lx + 3] = 255;
        }
    }
    free(data);

    if(not HeightNeg){
        unsigned char* datt = (unsigned char *)malloc(width*height*4);
        for(int lx = 0;lx < height;lx++)
            for(int ly = lx*width*4;ly < (lx + 1)*width*4;ly++)
                datt[(height - 1 - lx)*width*4 + (ly - lx*width*4)] = datt4[ly];
        gluBuild2DMipmaps( GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, datt);
        free(datt);
    }else
        gluBuild2DMipmaps( GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, datt4);
    
    free(datt4);
    return;
}

void Image::__LoadPng(const char* path){
    fprintf(stderr, "To Load Png\n");
    std::vector<unsigned char> get_image;
    unsigned int _width, _height;
    unsigned err = lodepng::decode(get_image, _width, _height, path);
    if(err){
        fprintf(stderr, "LoadPng: %s error", path);
        exit(1);
    }
    this->width = (signed int)(_width);
    this->height = (signed int)(_height);
    unsigned char* datt = (unsigned char *)malloc(width*height*4);
    for(int lx = 0;lx < get_image.size();lx++)
        datt[lx] = get_image[lx];
    gluBuild2DMipmaps( GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, datt);
    free(datt);
    return;
}

Image::~Image(){
    glDeleteTextures(1, &this->texture_id);
    return;
}

int Image::GetHeight(){
    return height;
}

int Image::GetWidth(){
    return width;
}

GLuint Image::GetTextureId(){
    return texture_id;
}

short int Image::GetBits(){
    return bits;
}

void Image::Render(float x, float y, float draw_width, float draw_height, int level){
    float xs[] = {x, x + draw_width, x + draw_width, x};
    float xc[] = {0, 1, 1, 0};
    float ys[] = {y, y, y + draw_height, y + draw_height};
    float yc[] = {0, 0, 1, 1};
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glBegin(GL_POLYGON);
    for(int lx = 3;lx >= 0;lx--){
		xs[lx] = xs[lx] - 1, ys[lx] = 1 - ys[lx];
        glTexCoord2d((GLfloat)(xc[lx]), (GLfloat)(yc[lx]));
		glVertex3f((GLfloat)(xs[lx]), (GLfloat)(ys[lx]), 0.01*(float)level);
	}
    glEnd();
    glDisable(GL_TEXTURE_2D);
    return;
}
