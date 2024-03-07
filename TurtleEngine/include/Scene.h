// Scene.h
#ifndef SCENE_H // include guard
#define SCENE_H
#include "Managers/AudioManager.h"
#include "Managers/TextureManager.h"
#include "Managers/FontManager.h"
#include "Managers/PhysicManager.h"
#include "Interfaces/IObject.h"

namespace Turtle
{
class Scene : public IObject
{
	const AudioManager& GetAudioManager() const;
	const TextureManager& GetTextureManager() const;
	const FontManager& GetFontManager() const;
	const PhysicManager& GetPhysicManager() const;
	void test();

protected:
	AudioManager m_audioManager;
	TextureManager m_textureManager;
	FontManager m_fontManager;
	PhysicManager m_physicManager;
};
}

#endif /* SCENE_H */