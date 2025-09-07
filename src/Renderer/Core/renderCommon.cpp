#include "abstractRenderer.hpp"


GL::Program* RendererCore::createProgram(const char* const* vshaderSource, const char* const* fshaderSource) {
    if (!vshaderSource || !fshaderSource) {
        return nullptr;
    }


    GL::Shader vshader(GL::Shader::Type::VERTEX, *vshaderSource);
    GL::Shader fshader(GL::Shader::Type::FRAGMENT, *fshaderSource);

    GL::Program* program = new GL::Program(vshader, fshader);
    return program;
}
