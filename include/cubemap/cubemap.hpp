#pragma once
#include<renderer/renderer.hpp>
#include<texture/texture.hpp>

class cubemap {
    private:
        texture m_cubeTexture;
        imageTexture m_face;

        vertexBufferLayout  m_layout;
        vertexArray  m_VAO;
        shaderProgram m_shader;
        renderer m_renderer;
        GLuint texid;

    public:
        cubemap();
        cubemap(const std::string& path, const vertexBuffer& VBO);

        inline void bind()   const { m_cubeTexture.bindTarget(GL_TEXTURE_CUBE_MAP); }
        inline void unbind() const { m_cubeTexture.unbind(GL_TEXTURE_CUBE_MAP); }

        void draw(const glm::mat4& view, const glm::mat4& proj);

        inline unsigned int getTextureID() const { return m_cubeTexture.getID(); }
};