#pragma once
#include <QEngine/Units.hpp>


namespace QEngine {

namespace Renderer {

class Base;

}


class Texture {
public:
    QEngine::Vector2<int> getSize();
    long getHandle() { return m_Handle; }


    friend class Renderer::Base;


protected:
    long m_Handle;
};

}
