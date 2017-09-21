#include "Renderer.h"

#include "GLError.h"

Renderer::Renderer(unsigned int width, unsigned int height)
: vertices{-1.0f, 1.0f, 0,
    -1.0f, -1.0f, 0,
    1.0f, -1.0f, 0,
    1.0f, 1.0f, 0},
    indices{0, 1, 3, 3, 1, 2},
texCoords{0, 1,
    0, 0,
    1, 0,
    1, 1}
{

    this->width = width;
    this->height = height;

    COLOUR_SHADER = ShaderProgram("/res/shaders/colour");
    COLOUR_SHADER.createUniform("colour");
    COLOUR_SHADER.createUniform("mvpMatrix");

    TEXTURE_SHADER = ShaderProgram("/res/shaders/texture");
    TEXTURE_SHADER.createUniform("mvpMatrix");
    TEXTURE_SHADER.createUniform("texSampler");
    
    FONT_SHADER = ShaderProgram("/res/shaders/font");
    FONT_SHADER.createUniform("texSampler");
    FONT_SHADER.createUniform("colour");
    FONT_SHADER.createUniform("mvpMatrix");
}

int Renderer::init() {
    // OpenGL
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    glGenBuffers(1, &posVBO);
    glBindBuffer(GL_ARRAY_BUFFER, posVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glGenBuffers(1, &texVBO);
    glBindBuffer(GL_ARRAY_BUFFER, texVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glGenBuffers(1, &indexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLushort), &indices[0], GL_STATIC_DRAW);

//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
    
    return 0;
}

void Renderer::fillQuad(Renderable2D& renderable, glm::vec4& colour) {
    COLOUR_SHADER.bind();
    COLOUR_SHADER.setUniform("colour", colour);
    COLOUR_SHADER.setUniform("mvpMatrix", getMVPMatrix(renderable));

    glBindVertexArray(vaoID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, posVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*) 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);

    COLOUR_SHADER.unbind();
}

void Renderer::fillQuad(float x, float y, float width, float height, glm::vec4 colour) {
    Renderable2D temp(x, y, width, height);
    fillQuad(temp, colour);
}

void Renderer::drawTexturedQuad(Renderable2D& renderable, Texture& texture) {
    TEXTURE_SHADER.bind();
    TEXTURE_SHADER.setUniform("texSampler", 0);
    TEXTURE_SHADER.setUniform("mvpMatrix", getMVPMatrix(renderable));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.texID);

    glBindVertexArray(vaoID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, posVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*) 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    
    glBindVertexArray(0);
    
    TEXTURE_SHADER.unbind();
}

void Renderer::drawString(NFont& font, std::string string, glm::vec3 position, glm::vec4 colour) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    const char *p;

    float x = position.x;
    float y = position.y;

    FT_GlyphSlot g = nullptr;
    unsigned int i = 0;
    for (p = string.c_str(); *p; p++) {
        if (i > 0) {
            if (*p == ' ') {
                position.x += g->bitmap.width + 2;
                continue;
            }
        }
        
        if (FT_Load_Char(font.face, *p, FT_LOAD_RENDER))
            continue;
        
        g = font.face->glyph;

        position.y = y + (font.height - g->bitmap.rows + (g->bitmap.rows - g->bitmap_top));
        
        Texture texture(g);
        FONT_SHADER.bind();
        FONT_SHADER.setUniform("texSampler", 0);
        FONT_SHADER.setUniform("mvpMatrix", getGlyphMVPMatrix(position, g));
        FONT_SHADER.setUniform("colour", colour);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.texID);

        glBindVertexArray(vaoID);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, posVBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*)0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);

        FONT_SHADER.unbind();

        // position.x += font.face->max_advance_width / font.height;
        position.x += g->bitmap.width + 2;
        
        glDeleteTextures(1, &texture.texID);
        
        glBindTexture(GL_TEXTURE_2D, 0);
        
        i++;
    }
    
    glDisable(GL_BLEND);
}

glm::mat4 Renderer::getMVPMatrix(Renderable2D& renderable) {
    float x = renderable.position.x + renderable.size.x / 2;
    float y = renderable.position.y + renderable.size.y / 2;

    translationMatrix = glm::translate(glm::mat4(), glm::vec3(x, y, renderable.position.z));
    modelMatrix = glm::scale(glm::mat4(), glm::vec3(renderable.size.x / 2, renderable.size.y / 2, 1.0f));
    mvpMatrix = projectionMatrix * (translationMatrix * modelMatrix);

    return mvpMatrix;
}

glm::mat4 Renderer::getGlyphMVPMatrix(glm::vec3& position, FT_GlyphSlot& glyph) {
    float x = position.x + glyph->bitmap.width / 2;
    float y = position.y + glyph->bitmap.rows / 2;

    translationMatrix = glm::translate(glm::mat4(), glm::vec3(x, y, position.z));
    modelMatrix = glm::scale(glm::mat4(), glm::vec3(glyph->bitmap.width / 2, glyph->bitmap.rows / 2, 1.0f));
    mvpMatrix = projectionMatrix * (translationMatrix * modelMatrix);

 
    return mvpMatrix;
}

glm::vec2 Renderer::toNDC(glm::vec2 coords) {
    // return glm::vec2(coords.x / ((float) width / 2) - 1, coords.y / ((float) height / 2));
    glm::vec4 result = projectionMatrix * glm::vec4(coords.x, coords.y, 1, 1);
    return glm::vec2(result.x, result.y);
}
