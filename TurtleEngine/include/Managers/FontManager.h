#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <memory>
#include <SFML/Graphics/Font.hpp>
#include <unordered_map>
#include <string>

namespace Turtle
{
    using FontPtr = std::unique_ptr<sf::Font>;
    using FontTag = std::string;

    class FontManager final
    {
    public:
        FontManager(const std::string& folderPath = "../../Ressources/Font/");
        FontManager(FontManager&) = delete;
        ~FontManager() = default;

        static const FontManager& Instance();

        bool LoadFont(const FontTag& fontTag, const std::string& fontPath);
        bool UnloadFont(const FontTag& fontTag);
        const FontPtr& GetFont(const FontTag& fontTag) const;

    private:
        std::string m_folderPath;
        std::unordered_map<FontTag, FontPtr> m_fonts;
    };
} // namespace Turtle

#endif /* FONT_MANAGER_H */
