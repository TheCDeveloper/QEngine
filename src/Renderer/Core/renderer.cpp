#include <QEngine/Renderer/Core.hpp>
#include <QEngine/Window.hpp>

#include <SDL3/SDL_video.h>

#include "abstractRenderer.hpp"


struct QEngine::Renderer::Core::InternalData {
    SDL_Window* sdlWindow;
    SDL_GLContext sdlGLContext;

    RendererCore::RendererData rendererData;
};


QEngine::Renderer::Core::Core(Window& window)
    : Base(window), m_Internal(nullptr) {

    m_Internal = new InternalData();

    SDL_Window* sdlWindow = (SDL_Window*) getWindowInternalSDLWindow(window);
    m_Internal->sdlWindow = sdlWindow;


    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    m_Internal->sdlGLContext = SDL_GL_CreateContext(sdlWindow);

    if (!m_Internal->sdlGLContext) {
        return;
    }

    SDL_GL_SetSwapInterval(1);

    gladLoadGL((GLADloadfunc) SDL_GL_GetProcAddress);


    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    RendererCore::initialize2D(m_Internal->rendererData);

    int w, h;
    SDL_GetWindowSize(sdlWindow, &w, &h);
    RendererCore::handleResize2D(m_Internal->rendererData, w, h);

    window.onResize.connect([this](int width, int height) {
        RendererCore::handleResize2D(m_Internal->rendererData, width, height);
    });
}


QEngine::Renderer::Core::~Core() {
    RendererCore::deinitialize2D(m_Internal->rendererData);
    SDL_GL_DestroyContext(m_Internal->sdlGLContext);
    delete m_Internal;
}


QEngine::Texture* QEngine::Renderer::Core::createTexture(const std::string_view filepath) {
    return nullptr;
}


void QEngine::Renderer::Core::destroyTexture(Texture* texture) {

}


void QEngine::Renderer::Core::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}


void QEngine::Renderer::Core::draw() {
    RendererCore::draw(m_Internal->rendererData);
}


void QEngine::Renderer::Core::draw(const QEngine::Scene2D::Scene& scene2D) {
    RendererCore::draw(m_Internal->rendererData);
}


void QEngine::Renderer::Core::present() {
    SDL_GL_SwapWindow(m_Internal->sdlWindow);
}
