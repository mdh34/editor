
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

typedef struct Texture {
    Texture(std::string path);
    
    int width;
    int height;

    GLuint texID = 0;
} Texture;

#endif
