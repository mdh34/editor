#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#ifdef _WIN32
    #include <GL/glew.h>
#else
    #include <OpenGL/gl3.h>
#endif

typedef struct IndexBuffer {
    IndexBuffer();
    IndexBuffer(GLushort* data, GLsizei count);

    GLuint bufferID;
    GLuint count;

    void bind() const;
    void unbind() const;

} IndexBuffer;

#endif
