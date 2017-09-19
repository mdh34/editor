
#ifndef RENDERER_H
#define RENDERER_H

#ifdef _WIN32
    #include <GL/glew.h>
#else
    #include <OpenGL/gl3.h>
    #include <OpenGL/gl3ext.h>
    #include <SDL2/SDL_opengl.h>
#endif

#include "ShaderProgram.h"
#include "Renderable2D.h"
#include "Texture.h"

#include "glm/gtc/matrix_transform.hpp"

typedef struct Renderer {
    glm::mat4 projectionMatrix;
    glm::mat4 translationMatrix;
    glm::mat4 modelMatrix;

    glm::mat4 mvpMatrix;

    ShaderProgram COLOUR_SHADER;
    ShaderProgram TEXTURE_SHADER;

    GLfloat vertices[12];
    GLushort indices[6];
    GLfloat texCoords[8];

    GLuint vaoID;
    GLuint posVBO;
    GLuint indexVBO;
    GLuint texVBO;

    Renderer();

    void init();

    void fillQuad(Renderable2D& renderable, glm::vec4& colour);
    void drawTexturedQuad(Renderable2D& renderable, Texture& texture);

    glm::mat4 getMVPMatrix(Renderable2D& renderable);

} Renderer;

#endif
