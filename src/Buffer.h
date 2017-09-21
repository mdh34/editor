
#ifndef BUFFER_H
#define BUFFER_H

#include "glm/glm.hpp"

#include <string>

typedef struct Buffer {
    Buffer() {};

    std::string contents;
    
    glm::vec2 cursor = glm::vec2(0.0f, 0.0f);
} Buffer;

#endif
