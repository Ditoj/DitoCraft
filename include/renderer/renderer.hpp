#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<vertex array/vertexArray.hpp>
#include<index buffer/indexBuffer.hpp>
#include<shader/shaderProgram.hpp>
#include<vendor/stb_image/stb_image.h>

class renderer {
    public:
        void draw(const vertexArray& vArray, const shaderProgram& shader, const int first, const int count, GLenum primitive = GL_TRIANGLES) const;
        void drawIndex(const vertexArray& vArray, const indexBuffer& iBuff, const shaderProgram& shader, GLenum primitive = GL_TRIANGLES) const;
        void clear() const;
};