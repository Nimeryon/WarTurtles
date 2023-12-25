#include "AudioManager.h"

void Turtle::AudioManager::LoadSound(SoundEffect soundEffetName,SoundType type, std::string path)
{
    SoundBufferPtr buffer = std::make_unique<sf::SoundBuffer>();
    
    if (buffer->loadFromFile(path)) {
        SoundPtr sound = std::make_unique<sf::Sound>();
        sound->setBuffer(*buffer);
        TurtleAudioInfo infos;
        infos.buffer = std::move(buffer);
        infos.sound = std::move(sound);
        infos.soundType = type;
        _sounds[soundEffetName] = std::move(infos);
    }
}

void Turtle::AudioManager::UnloadSound(SoundEffect soundEffetName)
{
    auto it = _sounds.find(soundEffetName);
    if (it != _sounds.end())
    {
        _sounds.erase(soundEffetName);
    }
}

void Turtle::AudioManager::PlaySound(SoundEffect sound, bool loop)
{
    auto it = _sounds.find(sound);
    if (it != _sounds.end()) {
        const TurtleAudioInfo& infos = it->second;
        float gloablVolume = infos.soundType == SoundType::Music?_musicVolume:_soundVolume;
        infos.sound->setVolume(infos.volume*gloablVolume/100.f);
        infos.sound->setLoop(loop);
        infos.sound->setPitch(infos.pitch);
        infos.sound->play();
    }
}

void Turtle::AudioManager::PauseSound(SoundEffect sound)
{
    auto it = _sounds.find(sound);
    if (it != _sounds.end()) {
        it->second.sound->pause();
    }
}

void Turtle::AudioManager::StopSound(SoundEffect sound)
{
    auto it = _sounds.find(sound);
    if (it != _sounds.end()) {
        it->second.sound->stop();
    }
}

void Turtle::AudioManager::SetPitch(SoundEffect sound, float pitch)
{
    auto it = _sounds.find(sound);
    if (it != _sounds.end()) {
        it->second.pitch = pitch;
    }
}

void Turtle::AudioManager::SetRandomPitch(SoundEffect sound, float pitch)
{
    auto it = _sounds.find(sound);
    if (it != _sounds.end()) {
        it->second.pitch = pitch;
    }
}

void Turtle::AudioManager::SetVolume(SoundEffect sound, float volume)
{
    auto it = _sounds.find(sound);
    if (it != _sounds.end()) {
        it->second.volume = volume;
    }
}

void Turtle::AudioManager::SetGlobalVolume(SoundType soundType, float volume)
{
    switch(soundType){
        case SoundType::Music:
            _musicVolume = volume;
            break;
        case SoundType::Sound:
            _soundVolume = volume;
            break;
        default:;
    }
}
