/*

QEngine Window
Defines the Window class and its functions

*/

#pragma once
#include <QEngine/Units.hpp>
#include <QEngine/Event.hpp>
#include <string_view>


namespace QEngine {

namespace Renderer {

class Base;

}


/**
 * Structure containing Window Options
 */
struct WindowOptions {
    int minWidth = 0, minHeight = 0;
    int width = 800, height = 450;
    std::string_view title = "QEngine";
  
    bool resizable = true;
  
    bool fullscreened = false;
};


/**
 * The Window class
 */
class Window {
public:
    Window(const WindowOptions& opts);
    ~Window();
  
    Event<int, int>& onResize = m_onResizeEvent.event;
  
  
    bool update();
  
    void size(Vector2<int> dimension);
  
  
    friend class Renderer::Base;


private:
    struct WindowData;
    WindowData* m_Data;

    BindableEvent<int, int> m_onResizeEvent;


    void* getSDLWindow();
};

}
