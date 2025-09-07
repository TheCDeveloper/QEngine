#pragma once
#include <QEngine/Instance.hpp>


namespace QEngine::Scene2D {

class Mesh : public Instance {
public:
    Mesh() : x(0), y(0), width(100), height(100) { m_Name = "Mesh"; }
  
  
    float x, y;
    float width, height;
  
  
    const char* className() const override { return "Mesh2D"; }
};

}
