#include "SceneManager.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Utils/Time.h"
#include "Scene.h"

Turtle::SceneManager::SceneManager() :
	m_insertedSceneID(0)
{}

unsigned int Turtle::SceneManager::AddScene(ScenePtr scene)
{
	const auto& inserted = m_scenes.emplace(m_insertedSceneID, std::move(scene)).first;
	inserted->second->OnCreate();

	m_insertedSceneID++;
	return m_insertedSceneID - 1;
}
void Turtle::SceneManager::RemoveScene(unsigned sceneID)
{
	const auto it = m_scenes.find(sceneID);
	if (it != m_scenes.end())
	{
		// If scene to remove is the current scene we set current scene to null
		if (m_currentScene == it->second.get())
		{
			m_currentScene = nullptr;
		}

		it->second->OnDestroyed();
		m_scenes.erase(it);
	}
}
void Turtle::SceneManager::SetScene(unsigned sceneID)
{
	const auto it = m_scenes.find(sceneID);
	if (it != m_scenes.end())
	{
		if (m_currentScene)
		{
			m_currentScene->OnDisabled();
		}

		// Utilisation de std::move de manière plus explicite
		m_currentScene = it->second.get();
		m_currentScene->OnEnabled();
	}
}

void Turtle::SceneManager::ProcessInputs() const
{
	if (m_currentScene)
	{
		m_currentScene->ProcessInputs();
	}
}
void Turtle::SceneManager::Update(const Time& deltaTime) const
{
	if (m_currentScene)
	{
		m_currentScene->Update(deltaTime);
	}
}
void Turtle::SceneManager::FixedUpdate(const Time& fixedTime) const
{
	if (m_currentScene)
	{
		m_currentScene->FixedUpdate(fixedTime);
	}
}
void Turtle::SceneManager::Draw(sf::RenderWindow& window) const
{
	if (m_currentScene)
	{
		m_currentScene->Draw(window);
	}
}
void Turtle::SceneManager::Gui(const Time& dt) const
{
	if (m_currentScene)
	{
		m_currentScene->Gui(dt);
	}
}
