#include <SDL.h>
#include <iostream>
#include <cstring> // for memcpy

// Function to load a BMP file and return pixel data
void loadARGB_BMP(const char* imagepath, unsigned char** data, unsigned int* width, unsigned int* height) {
    // Load BMP image
    SDL_Surface* image = SDL_LoadBMP(imagepath);
    if (!image) {
        std::cerr << "Error loading BMP file: " << SDL_GetError() << std::endl;
        *data = nullptr;
        *width = 0;
        *height = 0;
        return;
    }

    // Get width, height, and pixel data
    *width = image->w;
    *height = image->h;

    // BMP uses bottom-left origin, but OpenGL expects top-left origin
    // Flip the image vertically to match OpenGL texture coordinates
    unsigned int rowSize = image->pitch;
    unsigned char* flippedData = new unsigned char[rowSize * (*height)];

    for (unsigned int i = 0; i < *height; i++) {
        memcpy(&flippedData[i * rowSize], &((unsigned char*)image->pixels)[(*height - i - 1) * rowSize], rowSize);
    }

    *data = flippedData;

    // Free SDL surface
    SDL_FreeSurface(image);
}
