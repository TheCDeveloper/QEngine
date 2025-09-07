#pragma once
#include "GLAPI.hpp"

#include <glm/glm.hpp>


namespace RendererCore {

struct RendererData {
    int windowWidth, windowHeight;

    glm::mat4 orthoMatrix;

    GLint uModelMatrix;
    GLint uOrthoMatrix;

    GL::Program* program;
    GL::VertexArray* vertexArray;
    GL::VertexBuffer<float>* vertexBuffer;
};


GL::Program* createProgram(const char* const* vshaderSource, const char* const* fshaderSource);


void initialize2D(RendererData& data);
void deinitialize2D(RendererData& data);

void handleResize2D(RendererData& data, int width, int height);


void draw(RendererData& data);

}
