
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
constexpr std::chrono::nanoseconds timestep(16ms);

Window window;
Renderer renderer;

Editor editor(window, renderer);

void init() {
    printf("Current working directory: %s\n", getCWD().c_str());
    
    int width = 1000;
    int height = width / 16 * 9;
    
    window = Window(width, height, "Editor");
    renderer = Renderer(window.width, window.height);
    
    renderer.projectionMatrix = glm::ortho(0.0f, (float) (window.width), (float) (window.height), 0.0f, -100.0f, 100.0f);;
    renderer.translationMatrix = glm::mat4();
    renderer.modelMatrix = glm::mat4();
    
    renderer.mvpMatrix = glm::mat4();
    renderer.init();
    
    editor.window = window;
    editor.renderer = renderer;
}

SDL_Event event;
void update() {
//     window.poll();
    editor.update();
    renderer.projectionMatrix = glm::ortho(0.0f, (float) (window.width), (float) (window.height), 0.0f, -100.0f, 100.0f);
}


void render() {
    window.clear();
    editor.render();
    window.flip();
}

glm::mat4 projection;
int main(int argc, char** args) {
    init();

    using clock = std::chrono::high_resolution_clock;
    std::chrono::nanoseconds lag(0ns);
    
    auto startTime = clock::now();
    
    while(window.isOpen) {
        auto deltaTime = clock::now() - startTime;
        startTime = clock::now();
        lag += std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);
        
        while (lag >= timestep) {
            lag -= timestep;
            update();
        }
        
        render();
    }

    window.destroy();

    return 0;
}
