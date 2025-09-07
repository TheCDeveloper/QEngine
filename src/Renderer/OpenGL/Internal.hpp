#pragma once
#include <QEngine/Scene2D/Scene.hpp>

#include <glad/gl.h>
#include <glm/glm.hpp>


namespace GLRenderer {

struct Data {
    int windowWidth, windowHeight;

    glm::mat4 worldMatrix2D;

    GLuint vertexArray2D;
    GLuint vertexBuffer2D;

    GLuint program2D;

    GLint uModelMatrix2D;
    GLint uWorldMatrix2D;
    GLint uSampler2D;
};


void initialize2D(Data& data);
void deinitialize2D(Data& data);


unsigned long createTexture(Data& data, unsigned int width, unsigned int height, unsigned char* pixels);
void destroyTexture(Data& data, unsigned long texture);


void handleResize(Data& data, int newWidth, int newHeight);


void draw(Data& data, const QEngine::Scene2D::Scene& scene2D);

}
