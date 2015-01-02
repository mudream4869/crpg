#ifndef FILE_DEF
#define FILE_DEF

#include "Image.h"
namespace File{
    class File;
    void LoadFile(const char*);
    void SaveFile(const char*);
    File* PreloadFile(const char*);
};

class File::File{
public:
    File(Image* _img);
    bool HasImage()const;
    Image* GetImage();

private:
    Image* img;
};

#endif
