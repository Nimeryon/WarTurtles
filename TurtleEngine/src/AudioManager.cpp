#include "AudioManager.h"

Turtle::AudioManager::AudioManager() :
	m_musicVolume(100.f),
	m_soundVolume(100.f)
{}

void Turtle::AudioManager::LoadSound(const SoundEffect& soundEffectName,const SoundType& type,const std::string& path)
{
    SoundBufferPtr buffer = std::make_unique<sf::SoundBuffer>();
    
    if (buffer->loadFromFile(path))
    {
        SoundPtr sound = std::make_unique<sf::Sound>();
        sound->setBuffer(*buffer);
        TurtleAudioInfo infos;
        infos.buffer = std::move(buffer);
        infos.sound = std::move(sound);
        infos.soundType = type;
        m_sounds[soundEffectName] = std::move(infos);
    }
}

void Turtle::AudioManager::UnloadSound(const SoundEffect& soundEffectName)
{
    auto it = m_sounds.find(soundEffectName);
    if (it != m_sounds.end())
    {
        m_sounds.erase(soundEffectName);
    }
}

void Turtle::AudioManager::PlaySound(const SoundEffect& sound, bool loop)
{
    auto it = m_sounds.find(sound);
    if (it != m_sounds.end())
    {
        const TurtleAudioInfo& infos = it->second;
        const float globalVolume = infos.soundType == SoundType::MUSIC ? m_musicVolume : m_soundVolume;
        infos.sound->setVolume(infos.volume * globalVolume / 100.f);
        infos.sound->setLoop(loop);
        infos.sound->setPitch(infos.pitch);
        infos.sound->play();
    }
}

void Turtle::AudioManager::PauseSound(const SoundEffect& sound)
{
    auto it = m_sounds.find(sound);
    if (it != m_sounds.end())
    {
        it->second.sound->pause();
    }
}

void Turtle::AudioManager::StopSound(const SoundEffect& sound)
{
    auto it = m_sounds.find(sound);
    if (it != m_sounds.end())
    {
        it->second.sound->stop();
    }
}

void Turtle::AudioManager::SetPitch(const SoundEffect& sound, float pitch)
{
    auto it = m_sounds.find(sound);
    if (it != m_sounds.end())
    {
        it->second.pitch = pitch;
    }
}

void Turtle::AudioManager::SetRandomPitch(const SoundEffect& sound, float pitch)
{
    auto it = m_sounds.find(sound);
    if (it != m_sounds.end())
    {
        it->second.pitch = pitch;
    }
}

void Turtle::AudioManager::SetVolume(const SoundEffect& sound, float volume)
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
    case SoundType::MUSIC:
        m_musicVolume = volume;
        break;
    case SoundType::SOUND:
        m_soundVolume = volume;
        break;
    default: break;
    }
}
