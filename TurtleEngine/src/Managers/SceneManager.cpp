#include "Managers/SceneManager.h"

#include "Utils/Time.h"
#include "Utils/Window.h"
#include "Scene.h"
#include "App.h"

Turtle::SceneManager::SceneManager() :
	m_currentScene(nullptr),
	m_currentSceneID(0),
	m_insertedSceneID(0)
{}

Turtle::Scene* Turtle::SceneManager::GetCurrentScene() const { return m_currentScene; }

unsigned int Turtle::SceneManager::AddScene(ScenePtr scene, bool setScene,int sceneId)
{
	if(sceneId != -1)
	{
		m_insertedSceneID = sceneId;
	}
	const auto& inserted = m_scenes.emplace(m_insertedSceneID, std::move(scene)).first;

	if (setScene)
	{
		SetScene(m_insertedSceneID);
		//inserted->second->OnCreate(); already done in SetScene
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
		m_currentScene->OnCreate();
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
void Turtle::SceneManager::DebugDraw(Window& window) const
{
	if (m_currentScene)
	{
		m_currentScene->DebugDraw(window);
	}
}
void Turtle::SceneManager::Gui(Window& window, const Time& dt) const
{
	if (m_currentScene)
	{
		m_currentScene->Gui(window, dt);
	}
}

void Turtle::SceneManager::_HandleObjectCreation()
{
	if (m_currentScene)
	{
		m_currentScene->_HandleObjectCreation();
	}
}
void Turtle::SceneManager::_HandleObjectDestroy()
{
	if (m_currentScene)
	{
		m_currentScene->_HandleObjectDestroy();
	}
}