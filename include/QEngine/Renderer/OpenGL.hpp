#pragma once
#include "QEngine/Resource.hpp"
#include "Renderer.hpp"


namespace QEngine::Renderer {

/**
 * OpenGLRenderer configuration options
 */
struct OpenGLRendererOptions {
    int versionMinor = 3;
    int versionMajor = 3;
  
    int multisampleSamples = 0;
  
    bool vsync = true;
};


/**
 * A renderer implementation for the OpenGL Graphics API
 */
class OpenGLRenderer : public Base {
public:
    OpenGLRenderer(Window& window, const OpenGLRendererOptions& opts);
    ~OpenGLRenderer();


    Texture* createTexture(const std::string_view filepath) override;
    void destroyTexture(Texture* texture) override;

  
    void draw() override;
    void draw(const Scene2D::Scene& scene2D) override;
  
  
private:
    struct RendererData;
    RendererData* m_Data;
};

}
