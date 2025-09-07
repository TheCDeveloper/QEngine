#pragma once
#include <QEngine/Instance.hpp>
#include <QEngine/Resource.hpp>
#include <QEngine/Units.hpp>


namespace QEngine::Scene2D {

class Sprite : public Instance {
public:
    Sprite() { m_Name = "Sprite2D"; }
    

    Vector2<float> position;
    Vector2<float> scale;
    float rotation = 0.0f;

    Texture* texture;
};

}