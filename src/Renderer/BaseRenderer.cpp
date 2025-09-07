#include <QEngine/Renderer/Renderer.hpp>
#include <QEngine/Window.hpp>
#include <QEngine/Resource.hpp>


void* QEngine::Renderer::Base::getWindowInternalSDLWindow(Window& window) {
    return window.getSDLWindow();
}


long QEngine::Renderer::Base::getTextureHandle(const QEngine::Texture& texture) {
    return texture.m_Handle;
}


void QEngine::Renderer::Base::setTextureHandle(QEngine::Texture& texture, long handle) {
    texture.m_Handle = handle;
}
