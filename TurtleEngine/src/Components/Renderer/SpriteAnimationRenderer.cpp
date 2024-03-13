// SpriteAnimationRenderer.cpp
#include "Components/Renderer/SpriteAnimationRenderer.h"
#include "Components/Transform.h"
#include "GameObjects/GameObject.h"
#include "Managers/SceneManager.h"

namespace Turtle
{
    SpriteAnimationRenderer::SpriteAnimationRenderer(GameObject* parent, const std::string& name) 
        : Component(parent, name), m_textureManager(nullptr), m_currentFrame(0), m_frameDuration(100), m_elapsedTime(0)
    {}

    void SpriteAnimationRenderer::InitAnimation(const TextureTag& textureTag, const AnimationTag& animationTag)
    {
        m_textureManager = &SceneManager::Instance().GetCurrentScene()->GetTextureManager();
        m_textureTag = textureTag;
        m_animationTag = animationTag;
        m_animationFrames = m_textureManager->GetTextureData(textureTag).AnimationsData.find(animationTag)->second.frames;
        m_frameDuration = m_textureManager->GetTextureData(textureTag).AnimationsData.find(animationTag)->second.speed;
        m_currentFrame = 0;
        SetTextureRect(m_animationFrames[0]);
    }

    void SpriteAnimationRenderer::SetAnimation(const AnimationTag& animationTag, float speed)
    {
        if(animationTag == m_animationTag)return;
        m_animationTag = animationTag;
        m_frameDuration = m_textureManager->GetTextureData(m_textureTag).AnimationsData.find(animationTag)->second.speed;
        m_animationFrames = m_textureManager->GetTextureData(m_textureTag).AnimationsData.find(animationTag)->second.frames;
        m_currentFrame = 0;
    }

    void SpriteAnimationRenderer::SetAnimationSpeed(float speed)
    {
        m_frameDuration = speed;
    }

    void SpriteAnimationRenderer::SetTextureRect(const SpriteTag& spriteTag)
    {
        const SpriteData& spriteData = m_textureManager->GetSpriteData(m_textureTag, spriteTag);

        m_sprite.setTexture(*m_textureManager->GetTextureData(m_textureTag).Texture);
        m_sprite.setTextureRect(sf::IntRect(spriteData.startX, spriteData.startY, spriteData.sizeX, spriteData.sizeY));
        m_sprite.setScale(spriteData.isRevertedX ? -1.f : 1.f, spriteData.isRevertedY ? -1.f : 1.f);
    }

    void SpriteAnimationRenderer::SetColor(const sf::Color& color)
    {
        m_sprite.setColor(color);
    }

    void SpriteAnimationRenderer::SetOrigin(const Vector2f& origin)
    {
        m_sprite.setOrigin(origin.x,origin.y);
    }

    void SpriteAnimationRenderer::SetScale(const Vector2f& scale)
    {
        m_sprite.setScale(scale.x,scale.y);
    }

    void SpriteAnimationRenderer::SetPosition(const Vector2f& position)
    {
        m_sprite.setPosition(position.x,position.y);
    }


    void SpriteAnimationRenderer::Update(const Time& deltaTime)
    {
        m_elapsedTime += deltaTime.asMilliseconds();
        if (m_elapsedTime >= m_frameDuration)
        {
            m_currentFrame = (m_currentFrame + 1) % m_animationFrames.size();
            SetTextureRect(m_animationFrames[static_cast<size_t>(m_currentFrame)]);
            m_elapsedTime = 0;
        }
    }

    void SpriteAnimationRenderer::Draw(sf::RenderWindow& window)
    {
        const Transform* transform = m_parent->GetTransform();
        window.draw(m_sprite, transform->GetTransformMatrix());
    }

    void SpriteAnimationRenderer::Flip(bool flip)
    {
        m_flip = flip;
        auto scale = m_parent->GetTransform()->GetScale();
        float scaleX = flip?-std::abs(scale.x):std::abs(scale.x);
        m_parent->GetTransform()->SetScale({scaleX,scale.y});
    }
} // namespace Turtle
