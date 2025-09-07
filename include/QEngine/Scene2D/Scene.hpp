#pragma once
#include <QEngine/Instance.hpp>


namespace QEngine::Scene2D {

class Scene : public Instance {
public:
    Scene() { m_Name = "Scene2DRoot"; m_ParentLocked = true; }
  
  
    const char* className() const override { return "Scene2D"; }
};

}
