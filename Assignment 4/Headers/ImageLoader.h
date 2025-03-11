#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <iostream>
#include <fstream>

// Add inline to prevent duplicate symbols
inline void loadARGB_BMP(const char* imagepath, unsigned char** data, unsigned int* width, unsigned int* height) {
    printf("Reading image %s\n", imagepath);

    FILE * file = fopen(imagepath, "rb");
    if (!file) {
        printf("%s could not be opened. Are you in the right directory?\n", imagepath);
        return;
    }

    unsigned char header[54];
    fread(header, 1, 54, file);
    *width  = *(int*)&(header[0x12]);
    *height = *(int*)&(header[0x16]);
    
    int imageSize = (*width) * (*height) * 4;
    *data = new unsigned char[imageSize];

    fread(*data, 1, imageSize, file);
    fclose(file);
}

#endif // IMAGELOADER_H