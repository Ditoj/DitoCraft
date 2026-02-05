#pragma once
#include<renderer/renderer.hpp>

struct imageTexture {
    std::string filePath;
    stbi_uc *buffer;
    int width, height, bpp;
};

class texture {
    private:
        GLuint m_rendererId;
        imageTexture m_texture;

    public:
        texture();
        texture(const std::string& path);
        texture(const std::string& path, GLenum target);
        texture(const std::string& path, GLint filterWrapS, GLint filterWrapT, GLint filterMin, GLint filterMag);
        texture(const std::string& path, GLenum target, GLint filterWrapS, GLint filterWrapT, GLint filterMin, GLint filterMag);
        ~texture();

        void bind() const;
        void bind(GLint slot) const;
        void bindTarget(GLenum target) const;
        void bindTarget(GLenum target, GLint slot) const;
        void unbind(GLenum target = GL_TEXTURE_2D) const;

        void genTextureImage(imageTexture& tex, GLenum target, bool flip = true);
        void genTextureImage(const std::string& path, GLenum target, bool flip = true);
        void addToFrameBuffer(const texture& tex, GLint slot = 0, GLenum target = GL_FRAMEBUFFER) const;

        inline GLint getWidth()        const { return m_texture.width; }
        inline GLint getHeight()       const { return m_texture.height; }
        inline GLint getBytesPerPixel() const { return m_texture.bpp; }
        inline GLubyte* getBytes()     const { return m_texture.buffer; }
        inline const GLuint getID()    const { return m_rendererId; }
        inline const imageTexture getData() const { return m_texture; }
};