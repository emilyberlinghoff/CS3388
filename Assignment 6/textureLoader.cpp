#include <GL/glew.h>
#include <cstdio>
#include <cstdlib>

GLuint loadBMP_custom(const char * imagepath){
    printf("Loading BMP image %s\n", imagepath);

    // Open the file
    FILE * file = fopen(imagepath,"rb");
    if (!file) {
        printf("Image could not be opened\n");
        return 0;
    }

    // Read header
    unsigned char header[54];
    if (fread(header, 1, 54, file) != 54){
        printf("Not a correct BMP file\n");
        fclose(file);
        return 0;
    }

    if (header[0] != 'B' || header[1] != 'M'){
        printf("Not a correct BMP file\n");
        fclose(file);
        return 0;
    }

    // Read metadata
    unsigned int dataPos     = *(int*)&(header[0x0A]);
    unsigned int imageSize   = *(int*)&(header[0x22]);
    unsigned int width       = *(int*)&(header[0x12]);
    unsigned int height      = *(int*)&(header[0x16]);

    // If missing size, calculate
    if (imageSize == 0) imageSize = width * height * 3;
    if (dataPos == 0) dataPos = 54;

    unsigned char * data = new unsigned char[imageSize];
    fread(data, 1, imageSize, file);
    fclose(file);

    // Create OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // Bind it
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Upload texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    // Texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    delete[] data;

    return textureID;
}
