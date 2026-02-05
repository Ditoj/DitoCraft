#pragma once
#include<string>

class vertexBuffer {
    private:
        unsigned int m_rendererId;
        unsigned int m_size;

    public:
        vertexBuffer();
        vertexBuffer(const void* data, unsigned int size, unsigned int mode = 0x88E4);
        ~vertexBuffer();

        void bind() const;
        void unbind() const;

        void sendData(const void* data, unsigned int size, unsigned int mode) const;
        void updateData(const void* data, unsigned int size);
        void clear();

};