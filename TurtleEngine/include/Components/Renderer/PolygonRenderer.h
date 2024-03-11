// PolygonRenderer.h
#ifndef POLYGON_RENDERER_H
#define POLYGON_RENDERER_H

#include <SFML/Graphics.hpp>
#include "Components/Component.h"

namespace Turtle
{
    class PolygonRenderer  : public Component
    {
    public:
        explicit PolygonRenderer(GameObject* parent, const std::string& name = "PolygonRenderer");

        void SetVertices(const std::vector<sf::Vector2f>& vertices);
        void SetColor(const sf::Color& color);
        void Draw(sf::RenderWindow& window) override;

    private:
        sf::VertexArray m_vertexArray;
    };
} // namespace Turtle

#endif /* POLYGON_RENDERER_H */
