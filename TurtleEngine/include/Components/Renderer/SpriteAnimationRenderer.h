﻿// SpriteAnimationRenderer.h
#ifndef SPRITE_ANIMATION_RENDERER_H
#define SPRITE_ANIMATION_RENDERER_H

#include "Managers/TextureManager.h"
#include <SFML/Graphics.hpp>
#include "Components/Component.h"

namespace Turtle
{
    class SpriteAnimationRenderer final : public Component
    {
    public:
        explicit SpriteAnimationRenderer(GameObject* parent, const std::string& name = "SpriteAnimationRenderer");

        void InitAnimation(const TextureManager* textureManager, const TextureTag& textureTag, const AnimationTag& animationTag);
        
        void SetColor(const sf::Color& color);
        
        void Update(const Time& deltaTime) override;
        void Draw(sf::RenderWindow& window) override;

    private:
        void SetTextureRect(const SpriteTag& spriteTag);
        
        sf::Sprite m_sprite;
        const TextureManager* m_textureManager;
        TextureTag m_textureTag;
        AnimationTag m_animationTag;
        std::vector<SpriteTag> m_animationFrames;
        float m_currentFrame;
        float m_frameDuration;
        float m_elapsedTime;
    };
} // namespace Turtle

#endif /* SPRITE_ANIMATION_RENDERER_H */
