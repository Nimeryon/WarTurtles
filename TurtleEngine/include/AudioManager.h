#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include <SFML/Audio.hpp>

#include "Utils/Singleton.h"


namespace Turtle
{
    using SoundBufferPtr  = std::unique_ptr<sf::SoundBuffer>;
    using SoundPtr = std::unique_ptr<sf::Sound>;
    using SoundEffect = std::string;

    enum class SoundType{ Music,Sound};
    

    
    struct TurtleAudioInfo
    {
        SoundBufferPtr buffer;
        SoundPtr sound;
        SoundType soundType = SoundType::Sound;
        float volume = 100.f;
        float pitch = 1.f;
    };

    
    class AudioManager final
    {
    public:
        AudioManager() = default;
        AudioManager(AudioManager&) = delete;
        ~AudioManager() = default;
        
        void LoadSound(const SoundEffect& soundEffetName,const SoundType& type,const std::string& path);
        void UnloadSound(const SoundEffect& soundEffetName);
        void PlaySound(const SoundEffect& sound,bool loop = false);
        void PauseSound(const SoundEffect& sound);
        void StopSound(const SoundEffect& sound);
        void SetPitch(const SoundEffect& sound,float pitch);
        void SetRandomPitch(const SoundEffect& sound,float pitch);
        void SetVolume(const SoundEffect& sound,float volume);
        void SetGlobalVolume(const SoundType& soundType, float volume);
    private:
        std::unordered_map<SoundEffect,TurtleAudioInfo> _sounds;
        float _musicVolume = 100.f;
        float _soundVolume = 100.f;
    };
}

