#include "Components/Renderer/TextRenderer.h"
#include "Components/Transform.h"
#include "GameObjects/GameObject.h"

namespace Turtle
{
    TextRenderer::TextRenderer(GameObject* parent, const std::string& name) : Component(parent, name) {}

    void TextRenderer::SetFont(const sf::Font* font)
    {
        m_text.setFont(*font);
    }

    void TextRenderer::SetText(const std::string& text)
    {
        m_text.setString(text);
    }

    void TextRenderer::SetCharacterSize(unsigned int size)
    {
        m_text.setCharacterSize(size);
    }

    void TextRenderer::SetColor(const sf::Color& color)
    {
        m_text.setFillColor(color);
    }

    void TextRenderer::Draw(sf::RenderWindow& window)
    {
        const Transform* transform = m_parent->GetTransform();
        window.draw(m_text, transform->GetTransformMatrix());
    }
}