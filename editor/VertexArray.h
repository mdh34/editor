#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <vector>

#ifdef _WIN32
    #include <GL/glew.h>
#endif

#include "Buffer.h"

typedef struct VertexArray {

    VertexArray();
    ~VertexArray();

    GLuint arrayID;
    std::vector<Buffer*> buffers;

    void addBuffer(Buffer* buffer, GLuint index);

    void bind();
    void unbind();

} VertexArray;

#endif
