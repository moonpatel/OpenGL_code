#include "buffer.h"

buffer::buffer(int vao, int vbo, int ebo) {
    if(vao)
        glGenVertexArrays(1,&VAOID);
    if(vbo)
        glGenBuffers(1,&VBOID);
    if(ebo)
        glGenBuffers(1,&EBOID);
}

void buffer::bindVAO() {
    glBindVertexArray(VAOID);
}

void buffer::unbindVAO() {
    glBindVertexArray(0);
}

void buffer::bindVBO(GLenum bufferTarget) {
    glBindBuffer(bufferTarget,VBOID);
}

void buffer::unbindVBO(GLenum bufferTarget) {
    glBindBuffer(bufferTarget,0);
}

void buffer::bufferData(GLenum bufferTarget, GLfloat *bufferArray, GLenum mode, int attribLoc, int size, int stride, int offset) {
    glBindVertexArray(VAOID);
        glBindBuffer(bufferTarget,VBOID);
            glBufferData(bufferTarget,sizeof(bufferArray),bufferArray,mode);
            glVertexAttribPointer(attribLoc,size,GL_FLOAT,GL_FALSE,stride*sizeof(float),(void*)(offset*sizeof(float)));
            glEnableVertexAttribArray(attribLoc);
        glBindBuffer(bufferTarget,0);
    glBindVertexArray(0);
}