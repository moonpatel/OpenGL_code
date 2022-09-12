#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <GL/glew.h>

class buffer {
public:
    GLuint VAOID;
    GLuint VBOID;
    GLuint EBOID;

    buffer(int vao=0, int vbo=0, int ebo=0);
    void bindVAO();
    void unbindVAO();
    void bindVBO(GLenum bufferTarget);
    void unbindVBO(GLenum bufferTarget);
    void bufferData(GLenum bufferTarget, GLfloat *bufferArray, GLenum mode, int attribLoc, int size, int stride, int offset);
    void attribPointer(int index, int count, int stride, int offset);
};

#endif