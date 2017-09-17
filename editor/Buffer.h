#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#ifdef _WIN32
    #include <GL/glew.h>
#else
    #include <OpenGL/gl3.h>
#endif

typedef struct Buffer {
    GLuint bufferID;
    GLuint componentCount;
    
    Buffer();
    Buffer(GLfloat* data, GLsizei count, GLuint componentCount);

    void bind() const;
    void unbind() const;

} Buffer;

#endif
