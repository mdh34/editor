#include "Renderer.h"

#include "GLError.h"

Renderer::Renderer() {

}

void Renderer::drawRenderable(Renderable2D& renderable, ShaderProgram& shader) {
    shader.bind();
    shader.setUniform("color", renderable.color);

    float x = renderable.position.x + renderable.size.x / 2;
    float y = renderable.position.y + renderable.size.y / 2;

    translationMatrix = glm::translate(glm::mat4(), glm::vec3(x, y, renderable.position.z));

    modelMatrix = glm::scale(glm::mat4(), glm::vec3(renderable.size.x / 2, renderable.size.y / 2, 1.0f));

    mvpMatrix = projectionMatrix * (translationMatrix * modelMatrix);
    shader.setUniform("mvpMatrix", mvpMatrix);

    if (renderable.texture.texID != 0) {
        shader.setUniform("texSampler", renderable.texture.texID);
    } else {
        shader.setUniform("color", renderable.color);
    }

    renderable.vertexArray->bind();

    renderable.indexBuffer->bind();
    if (renderable.texture.texID) renderable.texBuffer->bind();

    glDrawElements(GL_TRIANGLES, renderable.indexBuffer->count, GL_UNSIGNED_SHORT, 0);

    renderable.indexBuffer->unbind();
    if (renderable.texture.texID) renderable.texBuffer->unbind();

    renderable.vertexArray->unbind();

    shader.unbind();

    translationMatrix = glm::mat4();
}
