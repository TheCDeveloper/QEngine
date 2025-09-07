#include "Internal.hpp"
#include "QEngine/Instance.hpp"
#include "QEngine/Scene2D/Scene.hpp"
#include "QEngine/Scene2D/Sprite.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <typeinfo>


/**
 * Shaders
 */
const char* const vshaderSource = R"(
    #version 330 core


    layout(location = 0) in vec2 aPosition;
    layout(location = 1) in vec2 aTexCoord;

    uniform mat4 uModelMatrix;
    uniform mat4 uWorldMatrix;

    out vec2 vTexCoord;


    void main() {
        gl_Position = uWorldMatrix * uModelMatrix * vec4(aPosition, 0.0f, 1.0f);
        vTexCoord = aTexCoord;
    }
)";

const char* const fshaderSource = R"(
    #version 330 core


    in vec2 vTexCoord;

    uniform sampler2D uTexture;

    out vec4 fragColor;


    void main() {
        fragColor = texture(uTexture, vTexCoord);
        fragColor.a = 1.0f;
    }
)";


void GLRenderer::initialize2D(Data &data) {
    GLuint program = glCreateProgram();

    GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vshader, 1, &vshaderSource, nullptr);
    glCompileShader(vshader);
    glAttachShader(program, vshader);

    GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fshader, 1, &fshaderSource, nullptr);
    glCompileShader(fshader);
    glAttachShader(program, fshader);

    glLinkProgram(program);
    glUseProgram(program);

    glDeleteShader(vshader);
    glDeleteShader(fshader);


    const float vertexData[] = {
        -1.0f,  1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f,

         1.0f,  1.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
         -1.0f, -1.0f, 0.0f, 0.0f
    };

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertexData, GL_STATIC_DRAW);

    GLuint vertexArray;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 4 * sizeof(float), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * sizeof(float), (const void*) (2 * sizeof(float)));

    glBindVertexArray(0);


    data.program2D = program;
    data.vertexBuffer2D = vertexBuffer;
    data.vertexArray2D = vertexArray;

    data.uModelMatrix2D = glGetUniformLocation(program, "uModelMatrix");
    data.uWorldMatrix2D = glGetUniformLocation(program, "uWorldMatrix");
    data.uSampler2D     = glGetUniformLocation(program, "uTexture");


    handleResize(data, data.windowWidth, data.windowHeight);
}


void GLRenderer::deinitialize2D(Data &data) {
    glDeleteVertexArrays(1, &data.vertexArray2D);
    glDeleteBuffers(1, &data.vertexBuffer2D);
    glDeleteProgram(data.program2D);
}


void GLRenderer::handleResize(Data& data, int newWidth, int newHeight) {
    glViewport(0, 0, newWidth, newHeight);
    
    data.worldMatrix2D = glm::ortho<float>(0, newWidth, newHeight, 0);
    glUniformMatrix4fv(data.uWorldMatrix2D, 1, false, &data.worldMatrix2D[0][0]);
    
    data.windowWidth = newWidth;
    data.windowHeight = newHeight;
}


unsigned long GLRenderer::createTexture(Data& data, unsigned int width, unsigned int height, unsigned char* pixels) {
    GLuint texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    return (unsigned long) texture;
}


void GLRenderer::destroyTexture(Data &data, unsigned long texture) {
    glDeleteTextures(1, (GLuint*) &texture);
}


void drawInstance(GLRenderer::Data& data, QEngine::Instance& instance) {
    for (auto& child : instance.children()) {
        if (typeid(*child) == typeid(QEngine::Scene2D::Sprite)) {

            QEngine::Scene2D::Sprite& sprite        = (QEngine::Scene2D::Sprite&) *child;
            const QEngine::Vector2<float>& position = sprite.position;
            const QEngine::Vector2<float>& scale    = sprite.scale;
            const float& rotation                   = sprite.rotation;
            GLuint texture                          = 0;

            if (sprite.texture)
                texture = (GLuint) sprite.texture->getHandle();


            glm::mat4 modelMat = glm::mat4(1.0f);
            
            modelMat = glm::translate(modelMat, {position.x + (scale.x / 2), position.y + (scale.x / 2), 0}) *
                       glm::rotate(modelMat, rotation * (float) (M_PI / 180.0f), {0, 0, 1}) *
                       glm::scale(modelMat, {scale.x/2, scale.y/2, 0});


            glUniformMatrix4fv(data.uModelMatrix2D, 1, false, &modelMat[0][0]);

            glBindTexture(GL_TEXTURE_2D, texture);

            glBindVertexArray(data.vertexArray2D);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
    }
}


void GLRenderer::draw(Data &data, const QEngine::Scene2D::Scene &scene2D) {
    glClear(GL_COLOR_BUFFER_BIT);
    drawInstance(data, (QEngine::Instance&) scene2D);
}
