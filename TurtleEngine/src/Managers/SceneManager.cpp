#include "Managers/SceneManager.h"

#include "Utils/Time.h"
#include "Utils/Window.h"
#include "Scene.h"

Turtle::SceneManager::SceneManager() :
	m_currentScene(nullptr),
	m_currentSceneID(0),
	m_insertedSceneID(0)
{}

Turtle::Scene* Turtle::SceneManager::GetCurrentScene() const { return m_currentScene; }

unsigned int Turtle::SceneManager::AddScene(ScenePtr scene, bool setScene)
{
	const auto& inserted = m_scenes.emplace(m_insertedSceneID, std::move(scene)).first;
	inserted->second->OnCreate();

	if (setScene)
	{
		SetScene(m_insertedSceneID);
	}

	m_insertedSceneID++;
	return m_insertedSceneID - 1;
}
void Turtle::SceneManager::RemoveScene(unsigned int sceneID)
{
	const auto it = m_scenes.find(sceneID);
	if (it != m_scenes.end())
	{
		// If scene to remove is the current scene we set current scene to null
		if (m_currentScene == it->second.get())
		{
			m_currentScene = nullptr;
			m_currentSceneID = 0;
		}

		it->second->OnDestroyed();
		m_scenes.erase(it);
	}
}
void Turtle::SceneManager::SetScene(unsigned int sceneID)
{
	const auto it = m_scenes.find(sceneID);
	if (it != m_scenes.end())
	{
		// Utilisation de std::move de manière plus explicite
		m_currentScene = it->second.get();
		m_currentSceneID = sceneID;
	}
}
void Turtle::SceneManager::NextScene()
{
	SetScene(m_currentSceneID + 1);
}
void Turtle::SceneManager::PreviousScene()
{
	if (m_currentSceneID != 0)
	{
		SetScene(m_currentSceneID - 1);
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
void Turtle::SceneManager::Draw(Window& window) const
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
