/*

PROJECT CORE

A new renderer replacing old OpenGLRenderer,
with more modularity

*/

#pragma once
#include "Renderer.hpp"


namespace QEngine::Renderer {

class Core : public Base {
public:
    Core(Window& window);
    ~Core();


    Texture* createTexture(const std::string_view filepath) override;
    void destroyTexture(Texture* texture) override;


    void clear();

    void draw() override;
    void draw(const Scene2D::Scene& scene2D) override; 

    void present();


private:
    struct InternalData;
    InternalData* m_Internal;
};

}
