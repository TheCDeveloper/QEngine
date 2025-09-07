#pragma once
#include "QEngine/Resource.hpp"
#include <string_view>


namespace QEngine {

class Window;

namespace Scene2D {

class Scene;

}

namespace Renderer {

class Base {
public:
    Base(Window& window): m_Window(window) {}
    virtual ~Base() = default;


    virtual Texture* createTexture(const std::string_view filepath) = 0;
    virtual void destroyTexture(Texture* texture) = 0;


    /**
    * Draw a thing
    */
    virtual void draw() = 0;

    /**
    * Draw a scene
    * @param scene2D Scene instance
    */
    virtual void draw(const Scene2D::Scene& scene2D) = 0;

  
protected:
    Window& m_Window;
    static void* getWindowInternalSDLWindow(Window& window);

    static long getTextureHandle(const QEngine::Texture& texture);
    static void setTextureHandle(QEngine::Texture& texture, long handle);
};

}

}
