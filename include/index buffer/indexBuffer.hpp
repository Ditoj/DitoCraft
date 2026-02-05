#pragma once
#include<string>

class indexBuffer {
    private:
        unsigned int m_rendererId;
        unsigned int m_itemCount;

    public:
        indexBuffer();
        indexBuffer(const unsigned int* indices, unsigned int count);
        ~indexBuffer();

        void bind() const;
        void unbind() const;

        inline unsigned int getCount() const { return m_itemCount; }

        void sendData(const void* data, unsigned int size) const;
        void clear();
};