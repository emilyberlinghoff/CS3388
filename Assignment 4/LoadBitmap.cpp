#include <cstdio>
#include <cstdlib>

// This function loads a BMP file that may be 24-bit or 32-bit.
// It returns the raw image data, width, height, bits-per-pixel (bpp),
// and sets the external (GL_BGR/GL_BGRA) and internal (GL_RGB/GL_RGBA) formats.
void loadAutoBMP(const char* imagePath,
                 unsigned char** data,
                 unsigned int* width,
                 unsigned int* height,
                 unsigned short* bpp,
                 unsigned int* format,
                 unsigned int* internalFormat)
{
    printf("Reading image %s\n", imagePath);
    FILE* file = fopen(imagePath, "rb");
    if (!file) {
        printf("Error: Could not open %s\n", imagePath);
        return;
    }
    
    unsigned char header[54];
    if (fread(header, 1, 54, file) != 54) {
        printf("Error: Not a correct BMP file (header too short).\n");
        fclose(file);
        return;
    }
    
    if (header[0] != 'B' || header[1] != 'M') {
        printf("Error: Not a correct BMP file (missing 'BM' signature).\n");
        fclose(file);
        return;
    }
    
    unsigned int dataPos   = *(unsigned int*)&header[0x0A];
    unsigned int imageSize = *(unsigned int*)&header[0x22];
    *width                 = *(unsigned int*)&header[0x12];
    *height                = *(unsigned int*)&header[0x16];
    *bpp = *(unsigned short*)&header[0x1C];
    
    if (imageSize == 0)
        imageSize = (*width) * (*height) * ((*bpp) / 8);
    if (dataPos == 0)
        dataPos = 54;
    
    *data = new unsigned char[imageSize];
    fseek(file, dataPos, SEEK_SET);
    if (fread(*data, 1, imageSize, file) != imageSize) {
        printf("Error: Could not read BMP data.\n");
        delete[] *data;
        *data = nullptr;
        fclose(file);
        return;
    }
    fclose(file);
    
    // Set external and internal formats based on bits per pixel.
    if (*bpp == 24) {
        *format         = 0x80E0;  // GL_BGR
        *internalFormat = 0x1907;  // GL_RGB
    } else if (*bpp == 32) {
        *format         = 0x80E1;  // GL_BGRA
        *internalFormat = 0x1908;  // GL_RGBA
    } else {
        printf("Warning: BMP with %u bits per pixel is not directly supported. Defaulting to 24-bit.\n", *bpp);
        *format         = 0x80E0;
        *internalFormat = 0x1907;
    }
}
