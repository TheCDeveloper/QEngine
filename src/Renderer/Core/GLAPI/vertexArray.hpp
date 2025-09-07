#pragma once
#include <glad/gl.h>


namespace GL {

class VertexArray {
public:
    VertexArray();
    ~VertexArray();


    void bind() const;
    inline static void unbind() { glBindVertexArray(0); }


private:
    mutable GLuint m_Handle;
};

}
