
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

#include <ft2build.h>
#include FT_FREETYPE_H

glm::mat4 projection;
int main(int argc, char** args) {

	printf("Current working directory: %s\n", getCWD().c_str());

		int width = 1000;
		int height = width / 16 * 9;
    Window window(width, height, "Editor");

    projection = glm::ortho(0.0f, (float) (window.width), (float) (window.height), 0.0f);

    Renderable2D sprite(glm::vec3(10.0f, 10.0f, 1.0f), glm::vec2(100, 100));
    
    Renderer renderer;

    renderer.projectionMatrix = projection;
    renderer.translationMatrix = glm::mat4();
    renderer.modelMatrix = glm::mat4();

    renderer.mvpMatrix = glm::mat4();
    
    glm::vec4 col(1, 0, 1, 1);
    
    Texture texture("/res/textures/banana.png");
    Texture def("/res/textures/default.png");
    
    renderer.init();

    float time = 0;
    while (window.isOpen) {
        time += 0.01f;

        window.clear();
        window.poll();

//        renderer.fillQuad(sprite, col);
        renderer.drawTexturedQuad(sprite, texture);
        sprite.position.x = 900;
        renderer.drawTexturedQuad(sprite, def);
        sprite.position.x = 10;

        window.flip();
        SDL_Delay(5);
    }

    return 0;
}
