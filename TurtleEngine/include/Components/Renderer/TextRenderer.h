#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <SFML/Graphics.hpp>
#include "Components/Component.h"

namespace Turtle
{
    class TextRenderer final : public Component
    {
    public:
        explicit TextRenderer(GameObject* parent, const std::string& name = "TextRenderer");

        void SetFont(const sf::Font* font);
        void SetText(const std::string& text);
        void SetCharacterSize(unsigned int size);
        void SetColor(const sf::Color& color);
        
        void Draw(sf::RenderWindow& window) override;

    private:
        sf::Text m_text;
    };
} // namespace Turtle

#endif /* TEXT_RENDERER_H */