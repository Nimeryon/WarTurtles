#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>

#include "App.h"

#include "Managers/SceneManager.h"

Turtle::App::App(Window& window, const Time& logicTime) :
	m_window(window),
	m_logicTime(logicTime)
{
	m_clock.restart();
	ImGui::SFML::Init(m_window);
}

void Turtle::App::Run()
{
	while (m_window.isOpen())
	{
		Time deltaTime = { m_clock.restart() };

		_ProcessInputs();
		_Update(deltaTime);
		_FixedUpdate(deltaTime);
		_Draw(deltaTime);
	}

	ImGui::SFML::Shutdown();
}

void Turtle::App::_ProcessInputs()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}

		ImGui::SFML::ProcessEvent(m_window, event);
	}

	SceneManager::Instance().ProcessInputs();
}
void Turtle::App::_Update(const Time& deltaTime)
{
	SceneManager::Instance().Update(deltaTime);
}
void Turtle::App::_FixedUpdate(const Time& deltaTime)
{
	m_currentLogicTime += deltaTime;
	while (m_currentLogicTime >= m_logicTime)
	{
		SceneManager::Instance().FixedUpdate(m_logicTime);

		m_currentLogicTime -= m_logicTime;
	}
}
void Turtle::App::_Draw(const Time& deltaTime)
{
	m_window.clear();

	SceneManager::Instance().Draw(m_window);

	ImGui::SFML::Update(m_window, m_logicTime);
	SceneManager::Instance().Gui(deltaTime);
	ImGui::SFML::Render(m_window);

	m_window.display();
}