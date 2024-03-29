﻿// ShapeRenderer.hxx
#ifndef SHAPE_RENDERER_HXX
#define SHAPE_RENDERER_HXX
#include "ShapeRenderer.h"

namespace Turtle
{
    class Transform;
}

template <typename ShapeType>
Turtle::ShapeRenderer<ShapeType>::ShapeRenderer(GameObject* parent, const std::string& name) : Component(parent, name),Clickable(&m_shape) {}

template<typename ShapeType>
ShapeType& Turtle::ShapeRenderer<ShapeType>::GetShape() { return m_shape; }

template <typename ShapeType>
void Turtle::ShapeRenderer<ShapeType>::SetShape(const ShapeType& shape)
{
    m_shape = shape;
}
template<typename ShapeType>
inline void Turtle::ShapeRenderer<ShapeType>::SetOrigin(const Vector2f& origin)
{
    m_shape.setOrigin({ origin.x, origin.y });
}
template <typename ShapeType>
void Turtle::ShapeRenderer<ShapeType>::SetColor(const sf::Color& color)
{
    m_shape.setFillColor(color);
}

template <typename ShapeType>
void Turtle::ShapeRenderer<ShapeType>::Draw(Window& window)
{
    
    const Transform* transform = this->m_parent->GetTransform();
    
    m_shape.setRotation(transform->GetRotation());
    m_shape.setScale(transform->GetScale().x,transform->GetScale().y);
    m_shape.setPosition(transform->GetPosition().x,transform->GetPosition().y);
    window.draw(m_shape);
}
#endif
