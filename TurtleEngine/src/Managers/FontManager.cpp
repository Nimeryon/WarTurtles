#include "Managers/FontManager.h"
#include <fstream>

#include "Managers/SceneManager.h"


Turtle::FontManager::FontManager(const std::string& folderPath) : m_folderPath(folderPath) {}

const Turtle::FontManager& Turtle::FontManager::Instance()
{
    return SceneManager::Instance().GetCurrentScene()->GetFontManager();
}

bool Turtle::FontManager::LoadFont(const FontTag& fontTag, const std::string& fontPath)
{
    const auto it = m_fonts.find(fontTag);
    if (it != m_fonts.end())
    {
        // Font is already loaded
        return true;
    }

    FontPtr font = std::make_unique<sf::Font>();
    if (font->loadFromFile(m_folderPath + fontPath))
    {
        m_fonts.emplace(fontTag, std::move(font));
        return true;
    }

    return false;
}

bool Turtle::FontManager::UnloadFont(const FontTag& fontTag)
{
    const auto it = m_fonts.find(fontTag);
    if (it != m_fonts.end())
    {
        m_fonts.erase(fontTag);
        return true;
    }

    return false;
}

const Turtle::FontPtr& Turtle::FontManager::GetFont(const FontTag& fontTag) const
{
    const auto it = m_fonts.find(fontTag);
    if (it != m_fonts.end())
    {
        return it->second;
    }

    return nullptr;
}
