#include"vertexBuffer.hpp"
#include<renderer/renderer.hpp>

vertexBuffer::vertexBuffer() {
    glGenBuffers(1, &m_rendererId);
}

vertexBuffer::vertexBuffer(const void* data, GLuint size, GLenum mode) {
    glGenBuffers(1, &m_rendererId);
    this->sendData(data, size, mode);
}

vertexBuffer::~vertexBuffer() {
    glDeleteBuffers(1, &m_rendererId);
}

void vertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
}

void vertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void vertexBuffer::sendData(const void* data, unsigned int size, GLenum mode) const {
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, mode);
    unbind();
}

void vertexBuffer::updateData(const void* data, unsigned int size) {
    bind();

    clear();
    glBufferData(m_rendererId, size, data, GL_DYNAMIC_DRAW);

    unbind();
}

void vertexBuffer::clear() {
    glDeleteBuffers(1, &m_rendererId);
    glGenBuffers(1, &m_rendererId);
}