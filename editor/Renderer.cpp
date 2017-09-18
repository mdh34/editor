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
//    TEXTURE_SHADER = ShaderProgram("/res/shaders/texture");

    glGenVertexArrays(GL_ARRAY_BUFFER, &vaoID);
    glBindVertexArray(vaoID);
    
    glGenBuffers(1, &posVBO);
    glBindBuffer(GL_ARRAY_BUFFER, posVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
}

void Renderer::fillQuad(Renderable2D& renderable, glm::vec4& colour) {
    float x = renderable.position.x + renderable.size.x / 2;
    float y = renderable.position.y + renderable.size.y / 2;
    
    translationMatrix = glm::translate(glm::mat4(), glm::vec3(x, y, renderable.position.z));
    modelMatrix = glm::scale(glm::mat4(), glm::vec3(renderable.size.x / 2, renderable.size.y / 2, 1.0f));
    mvpMatrix = projectionMatrix * (translationMatrix * modelMatrix);
    
    COLOUR_SHADER.bind();
    COLOUR_SHADER.setUniform("colour", colour);
    COLOUR_SHADER.setUniform("mvpMatrix", mvpMatrix);

    glBindVertexArray(vaoID);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / 3);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);

    COLOUR_SHADER.unbind();
}
