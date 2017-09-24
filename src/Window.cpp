
#include "Window.h"

Window::Window(int width, int height, std::string title) {
    this->width = width;
    this->height = height;
    this->title = title;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "[ERROR] Failed at SDL_Init(...). SDL_Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

    windowHandle = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
    if (windowHandle == NULL) {
        fprintf(stderr, "[ERROR] Failed at SDL_CreateWindow(...). SDL_Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        fprintf(stderr, "[ERROR] Failed at IMG_Init(...). SDL_image Error: %s\n", IMG_GetError());
    }

    glContext = SDL_GL_CreateContext(windowHandle);
    if (glContext == NULL) {
        fprintf(stderr, "[ERROR] Failed at SDL_GL_CreateContext(...). SDL_Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

#ifdef _WIN32
    glewExperimental = GL_TRUE;
    GLint GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult)
	{
        fprintf(stderr, "[ERROR] Failed at glewInit(). glewError: %s\n", glewGetErrorString(GlewInitResult));
		exit(EXIT_FAILURE);
    }
    else {
        printf("GLEW INIT\n");
    }
#endif
    
    printf("%s\n", glGetString(GL_EXTENSIONS));
    isOpen = true;

    SDL_GL_SetSwapInterval(1);

    SDL_StartTextInput();
}

void Window::poll() {

}

void Window::flip() {
    glFlush();
    SDL_GL_SwapWindow(windowHandle);
}

void Window::clear() {
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void Window::destroy() {
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(windowHandle);

    SDL_StartTextInput();

    SDL_Quit();
}
