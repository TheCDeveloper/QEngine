#include "vertexArray.hpp"


GL::VertexArray::VertexArray()
    : m_Handle(0) {

    glGenVertexArrays(1, &m_Handle);
}


GL::VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_Handle);
    m_Handle = 0;
}


void GL::VertexArray::bind() const {
    glBindVertexArray(m_Handle);
}
