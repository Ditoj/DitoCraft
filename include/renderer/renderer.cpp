#define STB_IMAGE_IMPLEMENTATION
#include"renderer.hpp"

void renderer::draw(const vertexArray& vArray, const shaderProgram& shader, const GLint first, const GLsizei count, GLenum primitive) const {
    vArray.bind();
    shader.bind();

    glDrawArrays(primitive, first, count);
}

void renderer::drawIndex(const vertexArray& vArray, const indexBuffer& iBuff, const shaderProgram& shader, GLenum primitive) const {
    vArray.bind();
    iBuff.bind();
    shader.bind();

    glDrawElements(primitive, iBuff.getCount(), GL_UNSIGNED_INT, nullptr);
}

void renderer::clear() const {
    glClear(GL_COLOR_BUFFER_BIT);
}