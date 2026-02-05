#include"indexBuffer.hpp"
#include<renderer/renderer.hpp>

indexBuffer::indexBuffer() : m_itemCount(0), m_rendererId(0) {}

indexBuffer::indexBuffer(const GLuint* indices, GLuint count) : m_itemCount(count) {
    glGenBuffers(1, &m_rendererId);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), indices, GL_STATIC_DRAW);
    unbind();
}

indexBuffer::~indexBuffer() {
    glDeleteBuffers(1, &m_rendererId);
}

void indexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
}

void indexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void indexBuffer::sendData(const void* data, unsigned int size) const {
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    unbind();
}

void indexBuffer::clear() {
    glDeleteBuffers(1, &m_rendererId);
    glGenBuffers(1, &m_rendererId);
}