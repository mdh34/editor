
#include <stdio.h>

// #include <ft2build.h>
// #include <freetype/freetype.h>

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

glm::mat4 projection;
int main(int argc, char** args) {

    printf("Current working directory: %s\n", getCWD().c_str());

    int width = 1000;
    int height = width / 16 * 9;

    Window window(width, height, "Editor");
    projection = glm::ortho(0.0f, (float) (window.width), (float) (window.height), 0.0f, -100.0f, 100.0f);

    Renderable2D sprite(glm::vec3(10.0f, 10.0f, 1.0f), glm::vec2(100, 100));
    Renderable2D sprite1(glm::vec3(100.0f, 100.0f, 5.0f), glm::vec2(200, 200));
    
    Renderer renderer(width, height);

    renderer.projectionMatrix = projection;
    renderer.translationMatrix = glm::mat4();
    renderer.modelMatrix = glm::mat4();

    renderer.mvpMatrix = glm::mat4();
    
    glm::vec4 col(1, 0, 1, 1);
    
    Texture texture("/res/textures/banana.png");
//    Texture def("/res/textures/default.png");
    
    renderer.init();
    
    std::string path = "/res/fonts/consolas.ttf";
    NFont font = NFont(path, 50);
    font.init();

    glm::vec3 o(0, 0, 1);

    Renderable2D quad(glm::vec3(0, 0, 0), glm::vec2(width, font.height));
    Renderable2D quad2(glm::vec3(320, 200, 1), glm::vec2(200, 150));

    float time = 0;
    while (window.isOpen) {
        time += 0.01f;
        window.clear();
        window.poll();

        renderer.drawTexturedQuad(sprite1, texture);
//        renderer.fillQuad(sprite, col);
        
        o.z = 1;
        renderer.drawString(font, "Hello world g klnvsx431134/;'", o, col);

        window.flip();
        SDL_Delay(5);
    }

    return 0;
}
