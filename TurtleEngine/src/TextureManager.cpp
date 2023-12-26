#include "TextureManager.h"
#include <fstream>
#include <iostream>

const Turtle::SpriteData Turtle::SpriteData::defaultSpriteData{0, 0, 0, 0, false, false};
const Turtle::TextureData Turtle::TextureData::defaultTextureData{nullptr,std::unordered_map<SpriteTag,SpriteData>{}};

Turtle::TextureManager::TextureManager(const std::string& folderPath):m_folderPath(folderPath)
{
}

bool Turtle::TextureManager::LoadTexture(const TextureTag& textureTag, const std::string& texturePath)
{
    auto it = m_texturesData.find(textureTag);
    if (it != m_texturesData.end())
    {
        //Texture is already loaded
        return true;
    }
    TexturePtr texture = std::make_unique<sf::Texture>();
    if(texture->loadFromFile(m_folderPath+texturePath))
    {
        size_t lastDotPosition = texturePath.find_last_of('.');
        if (lastDotPosition != std::string::npos)
        {
            std::string tspirtePath =  texturePath.substr(0, lastDotPosition);
            tspirtePath += ".tsprite";
            TextureData textureData{std::move(texture),ReadTSpriteFile(tspirtePath)};
            m_texturesData.emplace(textureTag,std::move(textureData));
            return true;
        }
    }
    return false;
}

bool Turtle::TextureManager::UnloadTexture(const TextureTag& textureTag)
{
    auto it = m_texturesData.find(textureTag);
    if (it != m_texturesData.end())
    {
        m_texturesData.erase(textureTag);
        return true;
    }
    return false;
}

const Turtle::TextureData& Turtle::TextureManager::GetTextureData(const TextureTag& textureTag)
{
    auto it = m_texturesData.find(textureTag);
    if (it != m_texturesData.end())
    {
        return it->second;
    }
    return TextureData::defaultTextureData;
}

const Turtle::SpriteData& Turtle::TextureManager::GetSpriteData(const TextureTag& textureTag,
    const SpriteTag& spriteTag)
{
    auto textureIt = m_texturesData.find(textureTag);
    if (textureIt != m_texturesData.end())
    {
        auto spritesData = textureIt->second.SpritesData;
        auto spriteIt = spritesData.find(textureTag);
        if (spriteIt != spritesData.end())
        {
            return spriteIt->second;
        }
    }
    return SpriteData::defaultSpriteData;//SpriteData::defaultSpriteData;
}


std::unordered_map<Turtle::SpriteTag, Turtle::SpriteData> Turtle::TextureManager::ReadTSpriteFile(const std::string& tspritePath)
{
    std::unordered_map<SpriteTag,SpriteData> spritesData{};
    
    std::ifstream jsonFile(m_folderPath+tspritePath);
    if (!jsonFile.is_open())
    {
        return spritesData;
    }
    nlohmann::json jsonData;
    jsonFile >> jsonData;

    try
    {
        for (const auto& sprite : jsonData["Sprites"])
        {
            if(!sprite.contains("Name"))
            {
                continue;
            }
            SpriteData spriteData;
            spriteData.startX = sprite.contains("X")? static_cast<int>(sprite["X"]):0;
            spriteData.startY = sprite.contains("Y")? static_cast<int>(sprite["Y"]):0;
            spriteData.sizeX = sprite.contains("SizeX")? static_cast<int>(sprite["SizeX"]):0;
            spriteData.sizeY = sprite.contains("SizeY")? static_cast<int>(sprite["SizeY"]):0;
            spriteData.isRevertedX = sprite.contains("RevertedX")? static_cast<bool>(sprite["RevertedX"]):false;
            spriteData.isRevertedY = sprite.contains("RevertedY")? static_cast<bool>(sprite["RevertedY"]):false;

            spritesData.emplace(sprite["Name"],spriteData);
        }
    }
    catch(...)
    {
        std::cerr<< "Unable to read tsprite file: "<< m_folderPath+tspritePath <<std::endl;
    }
    
    return spritesData;
}
