#include "program.hpp"
#include <cstdio>


GL::Shader::Shader(Type type, const char* source)
    : type(type), compileStatus(false), m_Handle(0) {

    if (!source) {
        return;
    }


    m_Handle = glCreateShader(type == Type::VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
    glShaderSource(m_Handle, 1, &source, nullptr);
    glCompileShader(m_Handle);


    int shaderCompileStatus = 0;
    glGetShaderiv(m_Handle, GL_COMPILE_STATUS, &shaderCompileStatus);

    if (shaderCompileStatus != 1) {
        char log[1024];
        glGetShaderInfoLog(m_Handle, 1024, nullptr, log);
        std::printf("[QEngine] Core Renderer: shader %u not compiled\n%s\n", m_Handle, log);

        glDeleteShader(m_Handle);
        m_Handle = 0;
    }

    compileStatus = shaderCompileStatus != 1 ? false : true;
}


GL::Shader::~Shader() {
    glDeleteShader(m_Handle);
    m_Handle = 0;
}




GL::Program::Program(Shader& vshader, Shader& fshader) 
    : linkStatus(false), m_Handle(0) {

    if (vshader.type != Shader::Type::VERTEX || fshader.type != Shader::Type::FRAGMENT) {
        return;
    }

    if (!vshader.compileStatus || !fshader.compileStatus) {
        return;
    }


    m_Handle = glCreateProgram();
    glAttachShader(m_Handle, vshader.m_Handle);
    glAttachShader(m_Handle, fshader.m_Handle);
    glLinkProgram(m_Handle);
}


GL::Program::~Program() {
    glDeleteProgram(m_Handle);
    m_Handle = 0;
}


void GL::Program::use() {
    glUseProgram(m_Handle);
}


GLint GL::Program::getUniformLocation(const char* uniformName) const {
    if (m_UniformCache.contains(uniformName)) {
        return m_UniformCache[uniformName];
    }

    GLint location = glGetUniformLocation(m_Handle, uniformName);

    if (location == -1) {
        std::printf("[QEngine] Core Renderer: uniform %s not found in program %u\n", uniformName, m_Handle);
    }

    m_UniformCache[uniformName] = location;
    return location;
}


void GL::Program::setUniformMat4f(GLint location, bool transpose, const float* mat4) {
    glUniformMatrix4fv(location, 1, transpose, mat4);
}
