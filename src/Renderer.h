
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
#include "Font.h"

#include "glm/gtc/matrix_transform.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <freetype/ftglyph.h>

typedef struct Renderer {
    glm::mat4 projectionMatrix;
    glm::mat4 translationMatrix;
    glm::mat4 modelMatrix;

    glm::mat4 mvpMatrix;

    ShaderProgram COLOUR_SHADER;
    ShaderProgram TEXTURE_SHADER;
    ShaderProgram FONT_SHADER;

    GLfloat vertices[12];
    GLushort indices[6];
    GLfloat texCoords[8];

    GLuint vaoID;
    GLuint posVBO;
    GLuint indexVBO;
    GLuint texVBO;

    unsigned int width;
    unsigned int height;

    Renderer() {};
    Renderer(unsigned int width, unsigned int height);

    int init();

    void fillQuad(Renderable2D& renderable, glm::vec4& colour);
    void fillQuad(float x, float y, float width, float height, glm::vec4 colour);
    void drawTexturedQuad(Renderable2D& renderable, Texture& texture);
    void drawString(NFont& font, std::string string, glm::vec3 position, glm::vec4& colour);

    glm::mat4 getMVPMatrix(Renderable2D& renderable);
    glm::mat4 getGlyphMVPMatrix(glm::vec3& position, FT_GlyphSlot& glyph);

    glm::vec2 toNDC(glm::vec2 coords);

} Renderer;

#endif
