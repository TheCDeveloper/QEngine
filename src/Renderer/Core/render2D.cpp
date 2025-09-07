#include "abstractRenderer.hpp"

#include <glm/gtc/matrix_transform.hpp>


const char* vshaderSource = R"(
    #version 330 core

    
    layout(location = 0) in vec2 aPosition;
    layout(location = 1) in vec2 aTexCoord;

    uniform mat4 uModelMatrix;
    uniform mat4 uOrthoMatrix;

    out vec2 vTexCoord;


    void main() {
        gl_Position = uOrthoMatrix * uModelMatrix * vec4(aPosition, 0.0f, 1.0f);
        vTexCoord   = aTexCoord;
    }
)";

const char* fshaderSource = R"(
    #version 330 core


    in vec2 vTexCoord;
    
    out vec4 fragColor;


    void main() {
        fragColor = vec4(vTexCoord, 0.0f, 1.0f);
    }
)";


void RendererCore::initialize2D(RendererData& data) {
    data.program = createProgram(&vshaderSource, &fshaderSource);
    data.vertexArray = new GL::VertexArray();
    data.vertexBuffer = new GL::VertexBuffer<float>();


    const float vertexData[] = {
        -1.0f,  1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f,

         1.0f,  1.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
         -1.0f, -1.0f, 0.0f, 0.0f
    };

    data.vertexBuffer->bind();
    data.vertexBuffer->setData(24, vertexData);


    data.vertexArray->bind();
    data.vertexBuffer->bind();

    data.vertexBuffer->setAttributePointer(0, 2, 4, 0);
    data.vertexBuffer->setAttributePointer(1, 2, 4, 2);

    data.vertexArray->unbind();


    data.program->use();
}


void RendererCore::deinitialize2D(RendererData &data) {
    delete data.vertexBuffer;
    delete data.vertexArray;
    delete data.program;
}


void RendererCore::handleResize2D(RendererData &data, int width, int height) {
    data.windowWidth = width;
    data.windowHeight = height;

    data.orthoMatrix = glm::ortho(0, width, height, 0);
}


void RendererCore::draw(RendererData& data) {
    data.vertexArray->bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    data.vertexArray->unbind();
}
