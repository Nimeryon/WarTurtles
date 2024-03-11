// ShapeRenderer.h
#ifndef SHAPE_RENDERER_H
#define SHAPE_RENDERER_H

#include <SFML/Graphics.hpp>
#include "Components/Component.h"
#include "Interfaces/IClickable.h"

namespace Turtle
{
    template <typename ShapeType>
    class ShapeRenderer final : public Component,public Clickable
    {
    public:
        explicit ShapeRenderer(GameObject* parent, const std::string& name = "ShapeRenderer");

        void SetShape(const ShapeType& shape);
        void SetColor(const sf::Color& color);
        void SetOrigin(const Vector2f& origin);
        void Draw(sf::RenderWindow& window) override;

    private:
        ShapeType m_shape;
    };
} // namespace Turtle

#include "ShapeRenderer.hxx" // Include the implementation file

#endif /* SHAPE_RENDERER_H */
