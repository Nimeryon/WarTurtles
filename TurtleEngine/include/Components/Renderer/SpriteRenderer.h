#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "Managers/TextureManager.h"
#include <SFML/Graphics.hpp>
#include "Components/Component.h"

namespace Turtle
{
    class SpriteRenderer final : public Component
    {
    public:
        explicit SpriteRenderer(GameObject* parent,const std::string& name = "SpriteRenderer");

        void InitTexture(const TextureManager* textureManager, const TextureTag& textureTag,const SpriteTag& spriteTag = "");
        
        void SetColor(const sf::Color& color);
        
        void Draw(sf::RenderWindow& window) override;

    private:
        void SetTextureRect(const SpriteTag& spriteTag);
        
        sf::Sprite m_sprite;
        const TextureManager* m_textureManager;
        TextureTag m_textureTag;
    };
} // namespace Turtle

#endif /* SPRITE_RENDERER_H */