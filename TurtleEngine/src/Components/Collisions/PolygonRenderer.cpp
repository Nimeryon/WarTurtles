#include "Components/Renderer/PolygonRenderer.h"
#include "Components/Transform.h"
#include "GameObjects/GameObject.h"

namespace Turtle
{
    class Transform;
}

namespace Turtle
{
    PolygonRenderer::PolygonRenderer(GameObject* parent, const std::string& name) : Component(parent, name)
    {
        m_vertexArray.setPrimitiveType(sf::Triangles);
    }

    void PolygonRenderer::SetVertices(const std::vector<sf::Vector2f>& vertices)
    {
        m_vertexArray.clear();
        
        for (const sf::Vector2f& vertex : vertices)
        {
            m_vertexArray.append(sf::Vertex(vertex));
        }
    }

    void PolygonRenderer::SetColor(const sf::Color& color)
    {
        for (std::size_t i = 0; i < m_vertexArray.getVertexCount(); ++i)
        {
            m_vertexArray[i].color = color;
        }
    }

    void PolygonRenderer::Draw(sf::RenderWindow& window)
    {
        const Transform* transform = m_parent->GetTransform();
        window.draw(m_vertexArray, transform->GetTransformMatrix());
    }
} // namespace Turtle