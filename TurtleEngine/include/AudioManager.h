// AudioManager.h
#ifndef AUDIO_MANAGER_H // include guard
#define AUDIO_MANAGER_H
#include <memory>
#include <string>
#include <unordered_map>
#include <SFML/Audio.hpp>

namespace Turtle
{
using SoundBufferPtr  = std::unique_ptr<sf::SoundBuffer>;
using SoundPtr = std::unique_ptr<sf::Sound>;
using SoundEffectTag = std::string;
    
enum class SoundType
{
	Music,
	Sound
};

struct AudioInfo
{
    AudioInfo():soundType(SoundType::Sound),volume(100.f),pitch(1.f){}
    SoundBufferPtr buffer;
    SoundPtr sound;
    SoundType soundType;
    float volume;
    float pitch;
};

class AudioManager final
{
public:
    AudioManager(const std::string& folderPath = "../../Ressources/Audio/");
    AudioManager(AudioManager&) = delete;
    ~AudioManager() = default;
    
    bool LoadSound(const SoundEffectTag& soundEffectName, const SoundType& type, const std::string& path);
    bool UnloadSound(const SoundEffectTag& soundEffectName);

    void PlaySound(const SoundEffectTag& sound, bool loop = false) const;
    void PauseSound(const SoundEffectTag& sound) const;
    void StopSound(const SoundEffectTag& sound) const;

    void SetPitch(const SoundEffectTag& sound, float pitch);
    void SetRandomPitch(const SoundEffectTag& sound, float pitch);
    void SetVolume(const SoundEffectTag& sound, float volume);
    void SetGlobalVolume(const SoundType& soundType, float volume);

private:
    std::unordered_map<SoundEffectTag,AudioInfo> m_sounds;
    float m_musicVolume;
    float m_soundVolume;
    const std::string m_audioFolderPath;
};
}

#endif /* AUDIO_MANAGER_H */
