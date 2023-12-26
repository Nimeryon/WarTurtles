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
using SoundEffect = std::string;

enum class SoundType
{
	MUSIC,
	SOUND
};

struct TurtleAudioInfo
{
    SoundBufferPtr buffer;
    SoundPtr sound;
    SoundType soundType = SoundType::SOUND;
    float volume = 100.f;
    float pitch = 1.f;
};

class AudioManager final
{
public:
    AudioManager();
    AudioManager(AudioManager&) = delete;
    ~AudioManager() = default;
    
    void LoadSound(const SoundEffect& soundEffectName,const SoundType& type,const std::string& path);
    void UnloadSound(const SoundEffect& soundEffectName);
    void PlaySound(const SoundEffect& sound,bool loop = false);
    void PauseSound(const SoundEffect& sound);
    void StopSound(const SoundEffect& sound);
    void SetPitch(const SoundEffect& sound,float pitch);
    void SetRandomPitch(const SoundEffect& sound,float pitch);
    void SetVolume(const SoundEffect& sound,float volume);
    void SetGlobalVolume(const SoundType& soundType, float volume);

private:
    std::unordered_map<SoundEffect,TurtleAudioInfo> m_sounds;
    float m_musicVolume;
    float m_soundVolume;
};
}

#endif /* AUDIO_MANAGER_H */
