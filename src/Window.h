
#ifndef WINDOW_H
#define WINDOW_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifdef _WIN32
    #include <GL/glew.h>
#else
    #include <OpenGL/gl3.h>
    #include <OpenGL/gl3ext.h>
#endif

#include "GLError.h"

typedef struct Window {
    Window() {};
    Window(int width, int height, std::string title);

    SDL_Window* windowHandle;
    SDL_GLContext glContext;
    SDL_Event event;

    SDL_TextEditingEvent textEvent;
    
    bool isOpen;

    int width;
    int height;
    std::string title;

    void clear();
    void poll();
    void flip();
    void destroy();
} Window;

#endif
