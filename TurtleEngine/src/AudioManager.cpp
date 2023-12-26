#include "AudioManager.h"

Turtle::AudioManager::AudioManager(const std::string& folderPath) :
    m_musicVolume(100.f),
    m_soundVolume(100.f),
    m_audioFolderPath(folderPath)
{}

bool Turtle::AudioManager::LoadSound(const SoundEffectTag& soundEffectName,const SoundType& type,const std::string& path)
{
   auto it = m_sounds.find(soundEffectName);
   if (it != m_sounds.end())
   {
       //Audio is already loaded
       return true;
   } 
    SoundBufferPtr buffer = std::make_unique<sf::SoundBuffer>();
    
    if (buffer->loadFromFile(m_audioFolderPath+path))
    {
        SoundPtr sound = std::make_unique<sf::Sound>();
        sound->setBuffer(*buffer);
        AudioInfo infos;
        infos.buffer = std::move(buffer);
        infos.sound = std::move(sound);
        infos.soundType = type;
        m_sounds[soundEffectName] = std::move(infos);
        return true;
    }
    return false;
}

bool Turtle::AudioManager::UnloadSound(const SoundEffectTag& soundEffectName)
{
    auto it = m_sounds.find(soundEffectName);
    if (it != m_sounds.end())
    {
        m_sounds.erase(soundEffectName);
        return true;
    }
    return false;
}

void Turtle::AudioManager::PlaySound(const SoundEffectTag& sound, bool loop)
{
    auto it = m_sounds.find(sound);
    if (it != m_sounds.end())
    {
        const AudioInfo& infos = it->second;
        const float globalVolume = infos.soundType == SoundType::Music ? m_musicVolume : m_soundVolume;
        infos.sound->setVolume(infos.volume * globalVolume / 100.f);
        infos.sound->setLoop(loop);
        infos.sound->setPitch(infos.pitch);
        infos.sound->play();
    }
}

void Turtle::AudioManager::PauseSound(const SoundEffectTag& sound)
{
    auto it = m_sounds.find(sound);
    if (it != m_sounds.end())
    {
        it->second.sound->pause();
    }
}

void Turtle::AudioManager::StopSound(const SoundEffectTag& sound)
{
    auto it = m_sounds.find(sound);
    if (it != m_sounds.end())
    {
        it->second.sound->stop();
    }
}

void Turtle::AudioManager::SetPitch(const SoundEffectTag& sound, float pitch)
{
    auto it = m_sounds.find(sound);
    if (it != m_sounds.end())
    {
        it->second.pitch = pitch;
    }
}

void Turtle::AudioManager::SetRandomPitch(const SoundEffectTag& sound, float pitch)
{
    auto it = m_sounds.find(sound);
    if (it != m_sounds.end())
    {
        it->second.pitch = pitch;
    }
}

void Turtle::AudioManager::SetVolume(const SoundEffectTag& sound, float volume)
{
    auto it = m_sounds.find(sound);
    if (it != m_sounds.end())
    {
        it->second.volume = volume;
    }
}

void Turtle::AudioManager::SetGlobalVolume(const SoundType& soundType, float volume)
{
    switch(soundType){
    case SoundType::Music:
        m_musicVolume = volume;
        break;
    case SoundType::Sound:
        m_soundVolume = volume;
        break;
    default: break;
    }
}
