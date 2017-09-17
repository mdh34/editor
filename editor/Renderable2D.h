#ifndef RENDERABLE_2D_H
#define RENDERABLE_2D_H

#include "Buffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"

#include "glm/glm.hpp"

typedef struct Renderable2D {

    Renderable2D() 
        : position(position), size(size), color(1.0f, 0.1f, 1.0f, 1.0f), texture(std::string("/res/textures/default.png")) {
    }

    Renderable2D(glm::vec3 position, glm::vec2 size) 
        : position(position), size(size), color(1.0f, 0.1f, 1.0f, 1.0f), texture(std::string("/res/textures/default.png"))
    {
        vertexArray = new VertexArray();

        GLfloat vertices[] = {
            -1.0f, 1.0f, 0,
            -1.0f, -1.0f, 0,
            1.0f, -1.0f, 0,
            1.0f, 1.0f, 0
        };
        vertexBuffer = new Buffer(vertices, 4 * 3, 3);


        GLushort indices[] = {
            0, 1, 3, 3, 1, 2
        };
        indexBuffer = new IndexBuffer(indices, 6);

        GLfloat texCoords[] = {
            0, 1,
            0, 0,
            1, 0,
            1, 1,
        };
        texBuffer = new Buffer(texCoords, 2 * 4, 2);

        vertexArray->addBuffer(vertexBuffer, 0);
        vertexArray->addBuffer(texBuffer, 1);
    }

    ~Renderable2D() {
        delete vertexArray;
    }

    glm::vec3 position;
    glm::vec2 size;
    glm::vec4 color;

    Texture texture;

    VertexArray* vertexArray;
    Buffer* vertexBuffer;
    IndexBuffer* indexBuffer;
    Buffer* texBuffer;
} Renderable2D;

#endif
