// TextureManager.h
#ifndef TEXTURE_MANAGER_H// include guard
#define TEXTURE_MANAGER_H
#include <SFML/Graphics/Texture.hpp>
#include <nlohmann/json.hpp>

namespace Turtle
{
    using TexturePtr = std::unique_ptr<sf::Texture>;
    using TextureTag = std::string;
    using SpriteTag = std::string;
    using AnimationTag = std::string;
    
    struct SpriteData
    {
        static const SpriteData defaultSpriteData;
    
        int startX;
        int startY;
        int sizeX;
        int sizeY;
        bool isRevertedX;
        bool isRevertedY;
    };
    struct AnimationData
    {
        static const AnimationData defaultAnimationData;
        
        std::vector<SpriteTag> frames;
    };
    
    struct TextureData
    {
        const static TextureData defaultTextureData;
    
        TexturePtr Texture;
        std::unordered_map<SpriteTag, SpriteData> SpritesData;
        std::unordered_map<AnimationTag, AnimationData> AnimationsData;
    };

    class TextureManager final
    {
    public:
        TextureManager(const std::string& folderPath = "../../Ressources/Texture/");
        TextureManager(TextureManager&) = delete;
        ~TextureManager() = default;
    
        bool LoadTexture(const TextureTag& textureTag, const std::string& texturePath);
        bool UnloadTexture(const TextureTag& textureTag);
        const TextureData& GetTextureData(const TextureTag& textureTag) const;
        const SpriteData& GetSpriteData(const TextureTag& textureTag, const SpriteTag& spriteTag) const;

        std::unordered_map<SpriteTag, SpriteData> ReadTSpriteFile(const std::string& tspritePath,std::unordered_map<SpriteTag,SpriteData>& spritesData,std::unordered_map<AnimationTag,AnimationData>& animationsData) const;

    private:
        std::string m_folderPath;
        std::unordered_map<TextureTag, TextureData> m_texturesData;
    };
}
#endif /* TEXTURE_MANAGER_H */
