#include "audioloader.h"

#include<vorbis/vorbisfile.h>

struct RIFF_Header {
    char chunkID[4];
    int chunkSize;//size not including chunkSize or chunkID
    char format[4];
};

struct WAVE_Format {
    char subChunkID[4];
    int subChunkSize;
    short audioFormat;
    short numChannels;
    int sampleRate;
    int byteRate;
    short blockAlign;
    short bitsPerSample;
};

struct WAVE_Data {
    char subChunkID[4]; //should contain the word data
    int subChunk2Size; //Stores the size of the data block
};

void CheckError(int op = -1, int _err = 0){
    int err;
    if(op == -1)
        err = alGetError(); // clear any error messages
    else 
        err = _err;
    if(err != AL_NO_ERROR){
        if(err == AL_INVALID_NAME)
            fprintf(stderr, "Error : Invalid Name\n");
        else if(err == AL_INVALID_ENUM)
            fprintf(stderr, "Error : Invalid Enum\n");
        else if(err == AL_INVALID_VALUE)
            fprintf(stderr, "Error : Invalid Value\n");
        else if(err == AL_INVALID_OPERATION)
            fprintf(stderr, "Error : Invalid Operation\n");
        else if(err == AL_OUT_OF_MEMORY)
            fprintf(stderr, "Error : Out of Memory\n");
        exit(1);
    }
    return;
}

bool _strcmp(const char* base, const char* cp){
    for(int lx = 0; base[lx] != 0;lx++){
        if(cp[lx] != base[lx])
            return false;
    }
    return true;
}

AudioFileData LoadWavFile(const char* filename){
    fprintf(stderr, "[1] filename = %s\n", filename);
    FILE* soundFile = NULL;
    WAVE_Format wave_format;
    RIFF_Header riff_header;
    WAVE_Data wave_data;
    unsigned char* data = 0;
    
    AudioFileData ret;

    ALsizei size;
    ALsizei frequency;
    Alenum format;
    
    try{
        soundFile = fopen(filename, "rb");
        if (!soundFile)
            throw (filename);

        // Read in the first chunk into the struct
        fread(&riff_header, sizeof(RIFF_Header), 1, soundFile);

        //check for RIFF and WAVE tag in memeory
        if (_strcmp("RIFF", riff_header.chunkID) == false or 
                _strcmp("WAVE", riff_header.format) == false)
            throw ("Invalid RIFF or WAVE Header");

        //Read in the 2nd chunk for the wave info
        fread(&wave_format, sizeof(WAVE_Format), 1, soundFile);
        //check for fmt tag in memory
        if(_strcmp("fmt ", wave_format.subChunkID) == false)
            throw ("Invalid Wave Format");

        //check for extra parameters;
        if (wave_format.subChunkSize > 16)
            fseek(soundFile, sizeof(short), SEEK_CUR);

        //Read in the the last byte of data before the sound file
        fread(&wave_data, sizeof(WAVE_Data), 1, soundFile);
        //check for data tag in memory
        if(_strcmp("data", wave_data.subChunkID) == false)
            throw ("Invalid data header");

        //Allocate memory for data
        data = new unsigned char[wave_data.subChunk2Size];

        // Read in the sound data into the soundData variable
        if (!fread(data, wave_data.subChunk2Size, 1, soundFile))
            throw ("error loading WAVE data into struct!");

        //Now we set the variables that we passed in with the
        //data from the structs
        size = wave_data.subChunk2Size;
        frequency = wave_format.sampleRate;
        //The format is worked out by looking at the number of
        //channels and the bits per sample.
        if(wave_format.numChannels == 1) {
            if(wave_format.bitsPerSample == 8 )
                format = AL_FORMAT_MONO8;
            else if(wave_format.bitsPerSample == 16)
                format = AL_FORMAT_MONO16;
        }else if(wave_format.numChannels == 2) {
            if(wave_format.bitsPerSample == 8 )
                format = AL_FORMAT_STEREO8;
            else if(wave_format.bitsPerSample == 16)
                format = AL_FORMAT_STEREO16;
        }
        //create our openAL buffer and check for success
        alGenBuffers(1, &ret.buffer);
        CheckError(); 
        //now we put our data into the openAL buffer and
        //check for success
        alBufferData(ret.buffer, format, (void*)data, size, frequency);
        CheckError(); 
        //clean up and return true if successful
        fclose(soundFile);
        fprintf(stderr, "load ok\n");
        delete[] data;
        ret.isok = true;
        return ret;
    }catch(const char* err){
        //printf("Error Occur: %s\n", err);
        if(soundFile != NULL)
            fclose(soundFile);
        if(data)
            delete[] data;
        //return false to indicate the failure to load wave
        ret.isok = false;
        return ret;
    }
}

AudioFileData LoadOggFile(const char* filename){
    AudioFileData ret;
    
    FILE* file = fopen(filename, "rb") ;
    rewind(file);
    
    OggVorbis_File ogg_file;
    unsigned int size = 0;
 
    if (ov_open(file, &ogg_file, NULL, 0) < 0){
        ret.isok = false;
        fclose(file);
        return ret;
    }
    
    vorbis_info* info = ov_info(&ogg_file, -1);

    if (info->channels == 1)
        format = AL_FORMAT_MONO16;
    else
        format = AL_FORMAT_STEREO16;

    // buffer size = (no. of channels) * (no. of samples) * 2 (for 16 bit)
    unsigned int data_size = ov_pcm_total(&ogg_file, -1) * info->channels * 2;

    char* data = new char[data_size];

    // Read the Ogg file into audio buffer
    while (size < data_size) {
        int section;
        result = ov_read(&ogg_file, data + size, data_size - size, 0, 2, 1, &section);
        if (result > 0)
            size += result;
        else if (result < 0) {
            delete data;
            ret.isok = false;
            return ret;
        }else{
            break;
        }
    }
    // Load PCM data into OpenAL buffer.
    alGenBuffers(1, &ret.buffer);
    alBufferData(buffer[0], ret.format, data, data_size, info->rate);
    return ret;
}
