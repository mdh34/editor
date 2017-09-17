
#ifndef WINDOW_H
#define WINDOW_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifdef _WIN32
    #include <GL/glew.h>
#else
    #include <OpenGL/gl3.h>
#endif

#include "GLError.h"

typedef struct Window {
    Window(int width, int height, std::string title);

    SDL_Window* windowHandle;
    SDL_GLContext glContext;
    SDL_Event event;

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
