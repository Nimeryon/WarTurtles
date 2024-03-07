#include "Scene.h"
#include "Components/Collisions/CollisionDispatcher.h"

const Turtle::AudioManager& Turtle::Scene::GetAudioManager() const { return m_audioManager; }
const Turtle::TextureManager& Turtle::Scene::GetTextureManager() const { return m_textureManager; }
const Turtle::FontManager& Turtle::Scene::GetFontManager() const { return m_fontManager; }
const Turtle::PhysicManager& Turtle::Scene::GetPhysicManager() const { return m_physicManager; }

void Turtle::Scene::test()
{
	//CollisionDispatcher<ICollisionComponent> dispatcher;
	//dispatcher.add<CircleCollisionComponent, CircleCollisionComponent, collisionBetweenCircles>();
}

