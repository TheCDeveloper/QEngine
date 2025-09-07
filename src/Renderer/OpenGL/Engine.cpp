#include "Internal.hpp"
#include "QEngine/Resource.hpp"
#include <QEngine/Renderer/OpenGL.hpp>
#include <QEngine/Window.hpp>

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_messagebox.h>

#include <glm/ext/scalar_constants.hpp>
#include <stb/stb_image.h>
#include <glad/gl.h>


/**
 * Struct for OpenGL variables
 */
struct QEngine::Renderer::OpenGLRenderer::RendererData {
    SDL_Window* sdlWindow;
    SDL_GLContext sdlGLContext;

    GLRenderer::Data renderer;
};


QEngine::Renderer::OpenGLRenderer::OpenGLRenderer(
    Window& window,
    const OpenGLRendererOptions& opts
) : Base(window),
    m_Data(nullptr) {

    SDL_Window* sdlWindow = (SDL_Window*) getWindowInternalSDLWindow(window);

    m_Data = new RendererData();
    m_Data->sdlWindow = sdlWindow;


    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, opts.versionMajor);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, opts.versionMinor);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, opts.multisampleSamples);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_NO_ERROR, 1);

    m_Data->sdlGLContext = SDL_GL_CreateContext(sdlWindow);

    if (!m_Data->sdlGLContext) {
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            "QEngine",
            "Failed to create an OpenGL Context",
            sdlWindow
        );
        std::exit(1);
    }

    gladLoadGL((GLADloadfunc) SDL_GL_GetProcAddress);


    if (opts.vsync) {
        if (!SDL_GL_SetSwapInterval(-1)) {
            SDL_GL_SetSwapInterval(1);
        }
    }


    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    // Renderer setup
    int w, h;
    SDL_GetWindowSize(sdlWindow, &w, &h);

    GLRenderer::initialize2D(m_Data->renderer);
    GLRenderer::handleResize(m_Data->renderer, w, h);

    window.onResize.connect([this](int newWidth, int newHeight) {
        GLRenderer::handleResize(m_Data->renderer, newWidth, newHeight);
    });
}


QEngine::Renderer::OpenGLRenderer::~OpenGLRenderer() {
    GLRenderer::deinitialize2D(m_Data->renderer);
    SDL_GL_DestroyContext(m_Data->sdlGLContext);
    delete m_Data;
}


QEngine::Texture* QEngine::Renderer::OpenGLRenderer::createTexture(const std::string_view filepath) {
    Texture* texture = new Texture();

    stbi_set_flip_vertically_on_load(1);

    int width, height;
    unsigned char* pixels = stbi_load(filepath.data(), &width, &height,nullptr, 4);

    if (!pixels)
        return nullptr;


    unsigned long glTex = GLRenderer::createTexture(m_Data->renderer, width, height, pixels);

    stbi_image_free(pixels);

    setTextureHandle(*texture, glTex);
    return texture;
}


void QEngine::Renderer::OpenGLRenderer::destroyTexture(Texture* texture) {
    if (texture) {
        GLRenderer::destroyTexture(m_Data->renderer, getTextureHandle(*texture));
        delete texture;
    }
}


void QEngine::Renderer::OpenGLRenderer::draw() {
    SDL_GL_SwapWindow(m_Data->sdlWindow);
}


void QEngine::Renderer::OpenGLRenderer::draw(const Scene2D::Scene& scene2D) {
    GLRenderer::draw(m_Data->renderer, scene2D);
    SDL_GL_SwapWindow(m_Data->sdlWindow);
}
