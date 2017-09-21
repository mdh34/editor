#include "Texture.h"

int count = 0;

// @Cleanup: Need to exit smoothly
Texture::Texture(std::string path) {
    std::string texPath = getCWD() + path;

    SDL_Surface* surface = IMG_Load(texPath.c_str());
    if (!surface) {
        fprintf(stderr, "[ERROR] Failed to load image: %s\n", texPath.c_str());
    }

    width = surface->w;
    height = surface->h;

    if (((width & (width - 1)) != 0) || (height & (height - 1)) != 0) {
        fprintf(stderr, "[ERROR] Image width and height must be a power of 2. %s\n", texPath.c_str());
    }

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

#ifdef _WIN32
    int mode = GL_RGB;
#else
    int mode = GL_BGR;
#endif

    if (surface->format->BytesPerPixel == 4) {
#ifdef _WIN32
        mode = GL_RGBA;
#else
        mode = GL_BGRA;
#endif
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
    
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(FT_GlyphSlot& glyph) {
    width = glyph->bitmap.width;
    height = glyph->bitmap.rows;

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);

//    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}
