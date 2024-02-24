#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "Managers/TextureManager.h"
#include <SFML/Graphics.hpp>

#include "Components/Component.h"
#include "Interfaces/IDrawable.h"

namespace Turtle
{
    class SpriteRenderer final : public Component, public IDrawable
    {
    public:
        // Constructor
        SpriteRenderer(GameObject* parent, const TextureManager& textureManager, const TextureTag& textureTag);

        // Set the sprite's texture rectangle
        void SetTextureRect(const SpriteTag& spriteTag);

        // Set the sprite's color
        void SetColor(const sf::Color& color);

        // Draw function from IDrawable interface
        virtual void Draw(sf::RenderWindow& window) override;

    private:
        sf::Sprite m_sprite;
        const TextureManager& m_textureManager;
        TextureTag m_textureTag;
    };
} // namespace Turtle

#endif /* SPRITE_RENDERER_H */