/*

Implementation of window.hpp

*/

#include <QEngine/Window.hpp>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_messagebox.h>
#include <cstdlib>


/**
 * WindowData
 */
struct QEngine::Window::WindowData {
    SDL_Window* sdlWindow;
};


QEngine::Window::Window(const WindowOptions& opts) {
    // SDL Initialization
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            "QEngine",
            "Failed to initialize SDL3 backend",
            nullptr
        );
        std::exit(1);
    }


    SDL_Window* sdlWindow = SDL_CreateWindow(
        opts.title.data(),
        opts.width, opts.height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_HIGH_PIXEL_DENSITY
    );

    if (!sdlWindow) {
        std::exit(1);
    }

    SDL_SetWindowMinimumSize(sdlWindow, opts.minWidth, opts.minHeight);
  
    SDL_SetWindowResizable(sdlWindow, opts.resizable);
    SDL_SetWindowFullscreen(sdlWindow, opts.resizable && opts.fullscreened);


    // Class initialization
    m_Data = new WindowData();
  
    m_Data->sdlWindow = sdlWindow;
}


QEngine::Window::~Window() {
    SDL_DestroyWindow(m_Data->sdlWindow);
    SDL_Quit();
  
    delete m_Data;
}


bool QEngine::Window::update() {
    static SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            return false;
        }
        if (event.type == SDL_EVENT_WINDOW_RESIZED) {
            m_onResizeEvent.fire(event.window.data1, event.window.data2);
        }
    }
  
    return true;
}


void* QEngine::Window::getSDLWindow() {
    return m_Data->sdlWindow;
}
