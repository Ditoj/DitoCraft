#pragma once
#include<texture/texture.hpp>
#include<renderer/renderer.hpp>
#include<render buffer/renderBuffer.hpp>
#include<vector>
#include<string>

class frameBuffer {
    private:
        GLuint m_rendererId;
        GLuint m_depthStencilBuffer;

        texture m_colorAttachment;
        imageTexture m_colorImage;
        GLuint m_colorCount;

        renderBuffer m_renderBuffer;

    public:
        frameBuffer();
        ~frameBuffer();

        void bind(GLenum target = GL_FRAMEBUFFER) const;
        void unbind(GLenum target = GL_FRAMEBUFFER) const;

        void clear();

        void attachTexture(GLsizei width, GLsizei height, GLint slot, GLenum textureTarget, GLenum target = GL_FRAMEBUFFER, bool flip = true);
        void attachDepthStencil(GLsizei width, GLsizei height, GLenum target = GL_FRAMEBUFFER, bool flip = true);
        void attachRenderBuffer(GLsizei width, GLsizei height, GLenum target = GL_FRAMEBUFFER, bool flip = true);

        void checkFrameBufferStatus(GLenum target = GL_FRAMEBUFFER);

        void bindTexture2D(GLenum texTarget, GLenum target);

        inline texture& getTextureClass()         { return m_colorAttachment; }
        inline GLuint getTexture()          const { return m_colorAttachment.getID(); }
        inline GLuint getDSBuffer()         const { return m_depthStencilBuffer; }
        inline GLuint renderBuffer()        const { return m_renderBuffer.getID(); }
        inline GLuint getID()               const { return m_rendererId; }
};