
#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifdef _WIN32
    #include <GL/glew.h>
#else
    #include <OpenGL/gl3.h>
#endif

#include "Util.h"
#include "Types.h"

#include <ft2build.h>
#include FT_FREETYPE_H

typedef struct Texture {
    Texture(std::string path);
    Texture(FT_GlyphSlot& bitmap);
    Texture(uint width, uint height);

    void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
    
    int width;
    int height;

    GLuint texID = 0;
} Texture;

#endif
