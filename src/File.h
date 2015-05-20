#ifndef FILE_DEF
#define FILE_DEF

#include <vector>
#include "Image.h"


namespace File{
    class File;

    /**
     *  @brief Load a Game File 
     *  @param
     *      filename: the file from 'saves/'
     */
    void LoadFile(const char* filename);

    /**
     *  @brief Save the file with screen  capture
     *  @param 
     *      filename: 
     */
    void SaveFile(const char* filename, std::vector<unsigned char>& enc_png);

    /**
     *  @brief Load the file's screen capture
     *  @param
     *      filename : The save file's filename
     *  @return 
     *      A File pointer
     */
    File* PreloadFile(const char* filename);
};

class File::File{
public:
    
    /**
     *  @brief Initialize the file
     *  @param 
     *      Screen Capture file
     */
    File(Image* _img);

    /**
     *  @return is img nullptr? 
     */
    bool HasImage()const;

    /**
     *  @return Get img Pointer 
     */
    Image* GetImage();

private:
    Image* img;
};

#endif
