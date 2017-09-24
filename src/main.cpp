
#include <stdio.h>

// #include <ft2build.h>
// #include <freetype/freetype.h>

#include <chrono>

#include "Window.h"
#include "ShaderProgram.h"

#include "Renderer.h"
#include "Renderable2D.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/string_cast.hpp"

#include "GLError.h"

#include "Font.h"
#include "Editor.h"

using namespace std::literals::chrono_literals;

Editor editor;

SDL_Event event;
void update() {
    editor.update();
}


void render() {
    editor.render();
}

int main(int argc, char** args) {

    double start = 0;
    double end = SDL_GetTicks() / 1000.0;
    double deltaTime = 0.0;
    double miliSecs = (1000.0 / 60.0) / 1000.0;
    
    while (editor.isOpen()) {
        start = SDL_GetTicks() / 1000.0;
        deltaTime += (double) (start - end) / miliSecs;
        end = start;
        while (deltaTime >= 1.0) {
            update();
            
            deltaTime -= 1.0;
        }
        
        render();
        
        SDL_Delay(1);
    }
    
    editor.destroy();

    return 0;
}
