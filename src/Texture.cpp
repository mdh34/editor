#include "Texture.h"

int count = 0;

Texture::Texture(std::string path) {
    std::string texPath = getCWD() + path;

    SDL_Surface* surface = IMG_Load(texPath.c_str());
    if (!surface) {
        fprintf(stderr, "[ERROR] Failed to load image: %s\n", texPath.c_str());
    }

    width = surface->w;
    height = surface->h;

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

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

    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(uint width, uint height) {
    surface = SDL_CreateRGBSurface(0, width, height, 8 * 4, 0, 0, 0, 0);
    
    width = surface->w;
    height = surface->h;

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint32 *pixels = (Uint32 *)surface->pixels;
    pixels[(y * surface->w) + x] = pixel;
}