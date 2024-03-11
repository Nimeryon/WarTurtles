// PolygonRenderer.h
#ifndef POLYGON_RENDERER_H
#define POLYGON_RENDERER_H

#include <SFML/Graphics.hpp>
#include "Components/Component.h"
#include "Types/Vector2.h"

namespace Turtle
{
    class PolygonRenderer  : public Component
    {
    public:
        explicit PolygonRenderer(GameObject* parent, const std::string& name = "PolygonRenderer");

        void SetVertice(const std::vector<Vector2f>& vertice);
        void SetColor(const sf::Color& color);
        void Draw(Window& window) override;

    private:
        sf::VertexArray m_vertexArray;
    };
} // namespace Turtle

#endif /* POLYGON_RENDERER_H */
