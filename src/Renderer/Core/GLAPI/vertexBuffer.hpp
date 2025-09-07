#pragma once
#include <glad/gl.h>


namespace GL {

template<typename T>
class VertexBuffer {
public:
    VertexBuffer()
        : m_Handle(0) {

        glGenBuffers(1, &m_Handle);
    }

    ~VertexBuffer() {
        glDeleteBuffers(1, &m_Handle);
        m_Handle = 0;
    }


    void bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
    }

    inline static void unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }


    void setData(size_t size, const T* data) {
        glBufferData(GL_ARRAY_BUFFER, size * sizeof(T), data, GL_DYNAMIC_DRAW);
    }


    void setAttributePointer(size_t index, size_t count, size_t stride, size_t offset) const {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, count, getType<T>(), false, stride * sizeof(T), (const void*) (offset * sizeof(T)));
    }


private:
    template<typename GLType>
    inline static GLenum getType();


    template<>
    GLenum getType<unsigned char>() {
        return GL_UNSIGNED_BYTE;
    }

    template<>
    GLenum getType<int>() {
        return GL_INT;
    }

    template<>
    GLenum getType<unsigned int>() {
        return GL_UNSIGNED_INT;
    }

    template<>
    GLenum getType<float>() {
        return GL_FLOAT;
    }


    mutable GLuint m_Handle;
};
    

}
