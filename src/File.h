#ifndef FILE_DEF
#define FILE_DEF

#include <vector>
#include "Image.h"

namespace File{
    class File;
    void LoadFile(const char*);
    void SaveFile(const char* filename, std::vector<unsigned char>& enc_png);
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
