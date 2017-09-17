#include "Texture.h"

int count = 0;

// @Cleanup: Need to exit smoothly
Texture::Texture(std::string path) {
    std::string texPath = getCWD() + path;

    SDL_Surface* surface = IMG_Load(texPath.c_str());
    if (!surface) {
        fprintf(stderr, "[ERROR] Failed to load image: %s\n", texPath.c_str());
    }
    
//    std::string savePath = "/Users/Noah/Desktop/test";
//    savePath.append(std::to_string(count++));
//    savePath.append(".bmp");
//    if (SDL_SaveBMP(surface, savePath.c_str()) != 0) {
//        printf("Could not save file %s\n", SDL_GetError());
//    }
    
    width = surface->w;
    height = surface->h;

    if (((width & (width - 1)) != 0) || (height & (height - 1)) != 0) {
        fprintf(stderr, "[ERROR] Image width and height must be a power of 2. %s\n", texPath.c_str());
    }

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    int mode = GL_RGB;

    if (surface->format->BytesPerPixel == 4) {
        printf("[INFO] Using GL_RGBA image loading for %s.\n", texPath.c_str());
        mode = GL_RGBA;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
}
