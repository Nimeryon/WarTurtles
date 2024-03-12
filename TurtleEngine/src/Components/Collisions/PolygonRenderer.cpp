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
        m_vertexArray.setPrimitiveType(sf::TriangleStrip);
    }

    void PolygonRenderer::SetVertice(const std::vector<Vector2f>& vertice)
    {
        m_vertexArray.clear();
        
        for (const Vector2f& vertex : vertice)
        {
            m_vertexArray.append(sf::Vertex({ vertex.x, vertex.y }));
        }
    }

    void PolygonRenderer::SetColor(const sf::Color& color)
    {
        for (std::size_t i = 0; i < m_vertexArray.getVertexCount(); ++i)
        {
            m_vertexArray[i].color = color;
        }
    }

    void PolygonRenderer::Draw(Window& window)
    {
        const Transform* transform = m_parent->GetTransform();
        window.draw(m_vertexArray, transform->GetTransformMatrix());
    }
} // namespace Turtle