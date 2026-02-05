#include<renderer/renderer.hpp>
#include"vertexArray.hpp"
#include<iostream>

vertexArray::vertexArray() {
    glGenVertexArrays(1, &m_rendererId);
}

vertexArray::~vertexArray() {
    glDeleteVertexArrays(1, &m_rendererId);
}

void vertexArray::bind() const {
    glBindVertexArray(m_rendererId);
};

void vertexArray::unbind() const {
    glBindVertexArray(0);
}

void vertexArray::addBuffer(const vertexBuffer& vBuff, const vertexBufferLayout& layout) const {
    bind();
    vBuff.bind();

    const auto& elements = layout.getElements();
    GLuint offset = 0;
    for(GLuint i = 0; i < elements.size(); i ++) {
        auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void *) offset);
        offset += element.count * sizeof(element.type);
    }

    unbind();
}

GLuint vertexArray::getRenderer() {
    return m_rendererId;
}