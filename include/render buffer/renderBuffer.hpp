#pragma once
#include<renderer/renderer.hpp>

class renderBuffer {
    private:
        unsigned int m_rendererId;
        GLenum m_format;
        GLsizei m_width, m_height;
        bool created = false;

    public:
        renderBuffer();
        renderBuffer(GLenum format, GLsizei width, GLsizei height, GLenum target = GL_FRAMEBUFFER);
        ~renderBuffer();

        void attachFrame(GLenum internalFormat, GLsizei width, GLsizei height, GLenum target);

        void bind() const;
        void unbind() const;

        inline GLuint  getFormat() const { return m_format; }
        inline GLsizei getWidth()  const { return m_width; }
        inline GLsizei getHeight() const { return m_height; }
        inline GLuint  getID()     const { return m_rendererId; }
};