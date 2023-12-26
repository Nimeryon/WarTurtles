#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <nlohmann/json.hpp>

#include "Utils/Singleton.h"
using json = nlohmann::json;

namespace Turtle
{
    using TexturePtr = std::unique_ptr<sf::Texture>;
    using TextureTag = std::string;
    using SpriteTag = std::string;
    
    struct SpriteData
    {
        int startX;
        int startY;
        int sizeX;
        int sizeY;
        bool isRevertedX;
        bool isRevertedY;
    };
    struct TextureData
    {
        TexturePtr Texture;
        std::unordered_map<SpriteTag,SpriteData> SpritesData;
    };
    
    class TextureManager : public Singleton<TextureManager>
    {
    public:
        TextureManager() = default;
        TextureManager(TextureManager&) = delete;
        ~TextureManager() = default;
        
        bool LoadTexture(const TextureTag& textureTag,const std::string& texturePath);
        bool UnloadTexture(const TextureTag& textureTag);
        const TextureData& GetTextureData(const TextureTag& textureTag);
        const SpriteData& GetSpriteData(const TextureTag& textureTag,const SpriteTag& spriteTag);
        
    private:
        std::unordered_map<TextureTag,TextureData> m_texturesData;
        TextureData& ReadTSpriteFile(const std::string& tspritePath);
    };
}

