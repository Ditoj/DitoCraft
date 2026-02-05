#pragma once

#include<vertex buffer/vertexBuffer.hpp>
#include<vertex buffer layout/vertexBufferLayout.hpp>

class vertexArray {
    private:
        unsigned int m_rendererId;

    public:
        vertexArray();
        ~vertexArray();

        void bind() const;
        void unbind() const;
        void addBuffer(const vertexBuffer& vBuff, const vertexBufferLayout& layout) const;
        unsigned int getRenderer();
};