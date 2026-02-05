#include"frameBuffer.hpp"

frameBuffer::frameBuffer() {
    glGenFramebuffers(1, &m_rendererId);
}

frameBuffer::~frameBuffer() {
    glDeleteFramebuffers(1, &m_rendererId);
}

void frameBuffer::bind(GLenum target) const {
    glBindFramebuffer(target, m_rendererId);
}

void frameBuffer::unbind(GLenum target) const {
    glBindFramebuffer(target, 0);
}

void frameBuffer::clear() {
    glDeleteBuffers(1, &m_rendererId);
}

void frameBuffer::attachTexture(GLsizei width, GLsizei height, GLint slot, GLenum textureTarget, GLenum target, bool flip) {
    m_colorImage.width  = width;
    m_colorImage.height = height;
    m_colorAttachment.genTextureImage(m_colorImage, textureTarget, flip);

    bind(target);
    m_colorAttachment.addToFrameBuffer(this->m_colorAttachment, slot, textureTarget);
    unbind(target);

    m_colorCount ++;
}

void frameBuffer::attachDepthStencil(GLsizei width, GLsizei height, GLenum target, bool flip) {
    glGenTextures(1, &m_depthStencilBuffer);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_depthStencilBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
    glFramebufferTexture2D(target, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthStencilBuffer, 0);
}

void frameBuffer::attachRenderBuffer(GLsizei width, GLsizei height, GLenum target, bool flip) {
    m_renderBuffer.bind();
    m_renderBuffer.attachFrame(GL_DEPTH24_STENCIL8, width, height, target);
    glFramebufferRenderbuffer(target, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBuffer.getID());
    m_renderBuffer.unbind();
}

void frameBuffer::bindTexture2D(GLenum texTarget, GLenum target) {
    glFramebufferTexture2D(target, GL_COLOR_ATTACHMENT0, texTarget, m_colorAttachment.getID(), 0);
}

void frameBuffer::checkFrameBufferStatus(GLenum target) {
    if(glCheckFramebufferStatus(target) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        glBindFramebuffer(target, 0);
    } else {
            std::cout << "Framebuffer is ready-to-go!" << std::endl;
        }
}