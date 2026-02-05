#pragma once

#include<GLFW/glfw3.h>
#include<iostream>
#include<vector>

struct vertexBufferElement {
    unsigned int count;
    unsigned int type;
    unsigned char normalized;
};

class vertexBufferLayout {
    private:
        std::vector<vertexBufferElement> m_elements;
        unsigned int m_stride;

    public:
        vertexBufferLayout() : m_stride(0) {};
        //~vertexBufferLayout() {};

        template<GLenum T> void push(unsigned int count) {
            m_elements.push_back({ count, T, GL_FALSE });

            switch(T) {
                case GL_DOUBLE: {
                    m_stride += sizeof(GLdouble) * count;
                } break;

                case GL_FLOAT: {
                    m_stride += sizeof(GLfloat) * count;
                } break;

                case GL_INT: {
                    m_stride += sizeof(GLint) * count;
                } break;

                case GL_UNSIGNED_INT: {
                    m_stride += sizeof(GLuint) * count;
                } break;

                case GL_BYTE: {
                    m_stride += sizeof(GLbyte) * count;
                } break;

                case GL_UNSIGNED_BYTE: {
                    m_stride += sizeof(GLubyte) * count;
                } break;
            }
        }

        inline const std::vector<vertexBufferElement> getElements() const { return m_elements; }
        inline GLuint getStride() const { return m_stride; }
};