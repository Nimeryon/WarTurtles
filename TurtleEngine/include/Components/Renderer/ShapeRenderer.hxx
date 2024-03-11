// ShapeRenderer.hxx
#ifndef SHAPE_RENDERER_HXX
#define SHAPE_RENDERER_HXX
#include "ShapeRenderer.h"

namespace Turtle
{
    class Transform;
}

template <typename ShapeType>
Turtle::ShapeRenderer<ShapeType>::ShapeRenderer(GameObject* parent, const std::string& name) : Component(parent, name) {}

template <typename ShapeType>
void Turtle::ShapeRenderer<ShapeType>::SetShape(const ShapeType& shape)
{
    m_shape = shape;
}

template <typename ShapeType>
void Turtle::ShapeRenderer<ShapeType>::SetColor(const sf::Color& color)
{
    // Assuming that the shape type has a setFillColor method
    m_shape.setFillColor(color);
}

template <typename ShapeType>
void Turtle::ShapeRenderer<ShapeType>::Draw(Window& window)
{
    const Transform* transform = this->m_parent->GetTransform();
    window.draw(m_shape, transform->GetTransformMatrix());
}
#endif
