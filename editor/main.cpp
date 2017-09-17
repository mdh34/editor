
#include <stdio.h>

// #include <ft2build.h>
// #include <freetype/freetype.h>

#include "Window.h"
#include "ShaderProgram.h"

#include "Buffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Renderable2D.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/string_cast.hpp"

#include <math.h>

glm::mat4 projection;
int main(int argc, char** args) {

	printf("Current working directory: %s\n", getCWD().c_str());

		int width = 1000;
		int height = width / 16 * 9;
    Window window(width, height, "Game Engine | Editor");

    ShaderProgram program("/res/shaders/texture");
    program.createUniform("mvpMatrix");
    program.createUniform("texSampler");

    projection = glm::ortho(0.0f, (float) (window.width), (float) (window.height), 0.0f);

    Renderable2D sprite(glm::vec3(10.0f, 10.0f, 1.0f), glm::vec2(500, 500));
    sprite.texture = Texture(std::string("/res/textures/banana.png"));
    Renderer renderer;

    renderer.projectionMatrix = projection;
    renderer.translationMatrix = glm::mat4();
    renderer.modelMatrix = glm::mat4();

    renderer.mvpMatrix = glm::mat4();

    float time = 0;
    while (window.isOpen) {
        time += 0.01f;

        window.clear();
        window.poll();

        renderer.drawRenderable(sprite, program);

        window.flip();
        SDL_Delay(5);
    }

    return 0;
}
