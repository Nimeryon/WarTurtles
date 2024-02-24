#include "Components/Renderer/SpriteRenderer.h"

#include "Components/Transform.h"
using TexturePtr = std::unique_ptr<sf::Texture>;
namespace Turtle
{
    SpriteRenderer::SpriteRenderer(GameObject* parent, const TextureManager& textureManager, const TextureTag& textureTag)
        : Component(parent, "SpriteRenderer"), m_textureManager(textureManager), m_textureTag(textureTag)
    {
        SetTextureRect("DefaultSprite");
    }

    void SpriteRenderer::SetTextureRect(const SpriteTag& spriteTag)
    {
        const SpriteData& spriteData = m_textureManager.GetSpriteData(m_textureTag, spriteTag);

        m_sprite.setTexture(*m_textureManager.GetTextureData(m_textureTag).Texture);
        m_sprite.setTextureRect(sf::IntRect(spriteData.startX, spriteData.startY, spriteData.sizeX, spriteData.sizeY));
        m_sprite.setScale(spriteData.isRevertedX ? -1.f : 1.f, spriteData.isRevertedY ? -1.f : 1.f);
    }

    void SpriteRenderer::SetColor(const sf::Color& color)
    {
        m_sprite.setColor(color);
    }

    void SpriteRenderer::Draw(sf::RenderWindow& window)
    {
        const Transform& transform = m_parent->GetTransform(); // Assuming a GetTransform method in GameObject
        m_sprite.setPosition(transform.GetGlobalPosition());
        window.draw(m_sprite);
    }
}
