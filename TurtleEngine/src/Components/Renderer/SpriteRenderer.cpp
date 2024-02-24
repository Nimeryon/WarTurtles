#include "Components/Renderer/SpriteRenderer.h"
#include "Components/Transform.h"
#include "GameObjects/GameObject.h"

using TexturePtr = std::unique_ptr<sf::Texture>;
namespace Turtle
{
    SpriteRenderer::SpriteRenderer(GameObject* parent, const std::string& name) : Component(parent, name),m_textureManager(nullptr){}

    void SpriteRenderer::InitTexture(const TextureManager* textureManager, const TextureTag& textureTag,const SpriteTag& spriteTag)
    {
        m_textureManager = textureManager;
        m_textureTag = textureTag;
        SetTextureRect(spriteTag == ""?textureTag:spriteTag);
    }

    void SpriteRenderer::SetTextureRect(const SpriteTag& spriteTag)
    {
        const SpriteData& spriteData = m_textureManager->GetSpriteData(m_textureTag, spriteTag);

        m_sprite.setTexture(*m_textureManager->GetTextureData(m_textureTag).Texture);
        m_sprite.setTextureRect(sf::IntRect(spriteData.startX, spriteData.startY, spriteData.sizeX, spriteData.sizeY));
        m_sprite.setScale(spriteData.isRevertedX ? -1.f : 1.f, spriteData.isRevertedY ? -1.f : 1.f);
    }

    void SpriteRenderer::SetColor(const sf::Color& color)
    {
        m_sprite.setColor(color);
    }

    void SpriteRenderer::Draw(sf::RenderWindow& window)
    {
        const Transform* transform = m_parent->GetTransform();
        window.draw(m_sprite,transform->GetTransformMatrix());
    }
}
