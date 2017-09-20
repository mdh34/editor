
#ifndef FONT_H
#define FONT_H

#include "Util.h"

#include <string>

#ifdef _WIN32
#include <GL/glew.h>
#else
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#include <SDL2/SDL_opengl.h>
#endif

#include <ft2build.h>
#include FT_FREETYPE_H


typedef struct NFont {
    FT_Library lib;
    FT_Face face;
    
    std::string path;
    GLuint tex;
    GLuint vbo;
    
    NFont();
    NFont(std::string& path);
    
    int init();
} NFont;



#endif /* Font_h */
