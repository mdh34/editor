
#ifndef RENDERER_H
#define RENDERER_H

#ifdef _WIN32
    #include <GL/glew.h>
#endif

#include "ShaderProgram.h"
#include "Renderable2D.h"

#include "glm/gtc/matrix_transform.hpp"

typedef struct Renderer {
    glm::mat4 projectionMatrix;
    glm::mat4 translationMatrix;
    glm::mat4 modelMatrix;

    glm::mat4 mvpMatrix;

    Renderer();

    void drawRenderable(Renderable2D& renderable, ShaderProgram& program);

} Renderer;

#endif
