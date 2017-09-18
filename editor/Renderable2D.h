#ifndef RENDERABLE_2D_H
#define RENDERABLE_2D_H

#include "glm/glm.hpp"

typedef struct Renderable2D {

    glm::vec3 position;
    glm::vec2 size;

    Renderable2D() {
        this->position = glm::vec3(0, 0, 1);
        this->size = glm::vec2(10, 10);
    }

    Renderable2D(glm::vec3 position, glm::vec2 size) {
        this->position = position;
        this->size = size;
    }

} Renderable2D;

#endif
