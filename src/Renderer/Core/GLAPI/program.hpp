#pragma once
#include <glad/gl.h>

#include <unordered_map>


namespace GL {

class Shader {
public:
    enum class Type {
        VERTEX,
        FRAGMENT
    };


    Shader(Type type, const char* source);
    ~Shader();


    const Type type;


    bool getCompileStatus() { return compileStatus; }


    friend class Program;


private:
    bool compileStatus;

    mutable GLuint m_Handle;
};


class Program {
public:
    Program(Shader& vertexShader, Shader& fragmentShader);
    ~Program();


    void use();

    bool getLinkStatus() { return linkStatus; }

    GLint getUniformLocation(const char* uniformName) const;

    void setUniformMat4f(GLint location, bool transpose, const float* mat4);
    void setUniformMat4f(const char* uniform, bool transpose, const float* mat4);


private:
    bool linkStatus;
    mutable std::unordered_map<const char*, GLint> m_UniformCache;
    
    mutable GLuint m_Handle;
};

}
