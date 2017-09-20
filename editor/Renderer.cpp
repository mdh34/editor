#include "Renderer.h"

#include "GLError.h"

Renderer::Renderer()
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

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    return 0;
}

void Renderer::fillQuad(Renderable2D& renderable, glm::vec4& colour) {
    COLOUR_SHADER.bind();
    COLOUR_SHADER.setUniform("colour", colour);
    COLOUR_SHADER.setUniform("mvpMatrix", getMVPMatrix(renderable));

    glBindVertexArray(vaoID);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*) 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);

    COLOUR_SHADER.unbind();
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

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*) 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    
    TEXTURE_SHADER.unbind();
}

void Renderer::drawString(NFont& font, std::string string, Renderable2D& position, glm::vec4& colour) {
    float x = position.position.x;
    float y = position.position.y;
    float sx = position.size.x;
    float sy = position.size.y;
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    const char *p;
    
    for (p = string.c_str(); *p; p++) {
        if (FT_Load_Char(font.face, *p, FT_LOAD_RENDER))
            continue;
        
        FT_GlyphSlot g = font.face->glyph;
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
                     g->bitmap.width, g->bitmap.rows,
                     0, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);
        
        float x2 = x + g->bitmap_left * sx;
        float y2 = -y - g->bitmap_top * sy;
        float w = g->bitmap.width * sx;
        float h = g->bitmap.rows * sy;
        
        GLfloat box[4][4] = {
            {x2,     -y2    , 0, 0},
            {x2 + w, -y2    , 1, 0},
            {x2,     -y2 - h, 0, 1},
            {x2 + w, -y2 - h, 1, 1},
        };
        
//        GLfloat box[4][4] = {
//            {-1.0f, 1.0f, 0, 0},
//            {-1.0f, -1.0f, 1, 0},
//            {1.0f, -1.0f, 0, 1},
//            {1.0f, 1.0f, 1, 1}
//        };
        
        glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
        
        FONT_SHADER.bind();
        FONT_SHADER.setUniform("texSampler", 0);
        FONT_SHADER.setUniform("colour", colour);
        FONT_SHADER.setUniform("mvpMatrix", getMVPMatrix(position));
        
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        
        FONT_SHADER.unbind();
        
        x += (g->advance.x/64) * sx;
        y += (g->advance.y/64) * sy;
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
