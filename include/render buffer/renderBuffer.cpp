#include"renderBuffer.hpp"

renderBuffer::renderBuffer() {
    if(!created) glGenRenderbuffers(1, &m_rendererId);
    created = true;
}

renderBuffer::renderBuffer(GLenum format, GLsizei width, GLsizei height, GLenum target) : m_format(format), m_width(width), m_height(height) {
    if(! created) glGenRenderbuffers(1, &m_rendererId);
    attachFrame(m_format, m_width, m_height, target);

    created = true;
}

renderBuffer::~renderBuffer() {
    glDeleteRenderbuffers(1, &m_rendererId);
}

void renderBuffer::attachFrame(GLenum internalFormat, GLsizei width, GLsizei height, GLenum target) {
    glRenderbufferStorage(target, internalFormat, width, height);
}

void renderBuffer::bind() const {
    glBindRenderbuffer(GL_RENDERBUFFER, m_rendererId);
}

void renderBuffer::unbind() const {
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}