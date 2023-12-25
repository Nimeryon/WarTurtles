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

    
    class AudioManager : public Singleton<AudioManager>
    {
    public:
        void LoadSound(SoundEffect soundEffetName,SoundType type,std::string path);
        void PlaySound(SoundEffect sound,bool loop = false);
        void PauseSound(SoundEffect sound);
        void StopSound(SoundEffect sound);
        void SetPitch(SoundEffect sound,float pitch);
        void SetRandomPitch(SoundEffect sound,float pitch);
        void SetVolume(SoundEffect sound,float volume);
        void SetGlobalVolume(SoundType soundType, float volume);
    private:
        std::unordered_map<SoundEffect,TurtleAudioInfo> _sounds;
        float _musicVolume = 100.f;
        float _soundVolume = 100.f;
    };
}

