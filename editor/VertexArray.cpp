
#include "VertexArray.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &arrayID);
}

VertexArray::~VertexArray() {
    for (int i = 0; i < buffers.size(); i++) {
        delete buffers[i];
    }
}

void VertexArray::addBuffer(Buffer* buffer, GLuint index) {
    bind();
    buffer->bind();

    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, buffer->componentCount, GL_FLOAT, GL_FALSE, 0, 0);

    buffer->unbind();
    unbind();

    buffers.push_back(buffer);
}

void VertexArray::bind() {
    glBindVertexArray(arrayID);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}