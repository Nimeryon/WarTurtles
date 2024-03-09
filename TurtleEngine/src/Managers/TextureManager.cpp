#include <fstream>

#include "Managers/TextureManager.h"

#include <iostream>

#include "Managers/SceneManager.h"

const Turtle::SpriteData Turtle::SpriteData::defaultSpriteData{0, 0, 0, 0, false, false};
const Turtle::TextureData Turtle::TextureData::defaultTextureData{nullptr,std::unordered_map<SpriteTag,SpriteData>{}};
const Turtle::AnimationData Turtle::AnimationData::defaultAnimationData{std::vector<SpriteTag>{}};
Turtle::TextureManager::TextureManager(const std::string& folderPath) :
    m_folderPath(folderPath)
{}

const Turtle::TextureManager& Turtle::TextureManager::Instance()
{
    return SceneManager::Instance().GetCurrentScene()->GetTextureManager();
}

bool Turtle::TextureManager::LoadTexture(const TextureTag& textureTag, const std::string& texturePath)
{
    const auto it = m_texturesData.find(textureTag);
    if (it != m_texturesData.end())
    {
        //Texture is already loaded
        return true;
    }

    TexturePtr texture = std::make_unique<sf::Texture>();
    if(texture->loadFromFile(m_folderPath+texturePath))
    {
        const size_t lastDotPosition = texturePath.find_last_of('.');
        if (lastDotPosition != std::string::npos)
        {
            std::string tspritePath =  texturePath.substr(0, lastDotPosition);
            tspritePath += ".tsprite";
            TextureData textureData{std::move(texture)};
            ReadTSpriteFile(tspritePath,textureData.SpritesData,textureData.AnimationsData);
            m_texturesData.emplace(textureTag, std::move(textureData));
            return true;
        }
    }

    return false;
}

bool Turtle::TextureManager::UnloadTexture(const TextureTag& textureTag)
{
    const auto it = m_texturesData.find(textureTag);
    if (it != m_texturesData.end())
    {
        m_texturesData.erase(textureTag);
        return true;
    }

    return false;
}

const Turtle::TextureData& Turtle::TextureManager::GetTextureData(const TextureTag& textureTag) const
{
    const auto it = m_texturesData.find(textureTag);
    if (it != m_texturesData.end())
    {
        return it->second;
    }

    return TextureData::defaultTextureData;
}

const Turtle::SpriteData& Turtle::TextureManager::GetSpriteData(const TextureTag& textureTag, const SpriteTag& spriteTag) const
{
    const auto textureIt = m_texturesData.find(textureTag);
    if (textureIt != m_texturesData.end())
    {
        const auto& spritesData = textureIt->second.SpritesData;
        const auto spriteIt = spritesData.find(spriteTag);
        if (spriteIt != spritesData.end())
        {
            return spriteIt->second;
        }
    }

    return SpriteData::defaultSpriteData;
}


std::unordered_map<Turtle::SpriteTag, Turtle::SpriteData> Turtle::TextureManager::ReadTSpriteFile(const std::string& tspritePath,std::unordered_map<SpriteTag,SpriteData>& spritesData,std::unordered_map<AnimationTag,AnimationData>& animationsData) const
{
    std::ifstream jsonFile(m_folderPath+tspritePath);
    if (!jsonFile.is_open())
    {
        return spritesData;
    }
    nlohmann::json jsonData;
    jsonFile >> jsonData;
    
    for (const auto& sprite : jsonData["Sprites"])
    {
        SpriteTag name = sprite.value("Name", "Sprite" + std::to_string(spritesData.size()));
        SpriteData spriteData
        {
	        sprite.value<int>("X", SpriteData::defaultSpriteData.startX),
	        sprite.value<int>("Y", SpriteData::defaultSpriteData.startY),
	        sprite.value<int>("SizeX", SpriteData::defaultSpriteData.sizeX),
	        sprite.value<int>("SizeY", SpriteData::defaultSpriteData.startY),
	        sprite.value<bool>("RevertedX", SpriteData::defaultSpriteData.isRevertedX),
	        sprite.value<bool>("RevertedY", SpriteData::defaultSpriteData.isRevertedY)
        };
        spritesData.emplace(name,spriteData);
    }
    for (const auto& anim : jsonData["Animations"])
    {
        SpriteTag name = anim.value("Name", "Sprite" + std::to_string(spritesData.size()));
        auto sequence = anim.value<std::vector<SpriteTag>>("Sequence",AnimationData::defaultAnimationData.frames);
        if(sequence.size() == 0){
            std::cout << "[Warning] Anim " << name << " is empty" << std::endl;
            continue;
        }
        AnimationData animationData{ sequence,anim.value<float>("Speed",50),};
        animationsData.emplace(name,animationData);
    }
    

    return spritesData;
}
