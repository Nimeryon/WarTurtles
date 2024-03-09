#include <format>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "imgui-SFML.h"
#include "imgui.h"
#include "App.h"
#include "Scene.h"
#include "Components/Transform.h"
#include "Managers/SceneManager.h"
#include "Types/Vector2.h"
#include "GameObjects/GameObject.h"

class TestComponent : public Turtle::Component
{
public:
    TestComponent(Turtle::GameObject* parent) : Component(parent, "Test Component")
    {
        m_rect.setSize({ 50, 50 });
        m_rect.setFillColor(sf::Color::Cyan);
    }

    void FixedUpdate(const Turtle::Time& fixedTime) override
    {
        m_parent->GetTransform()->Rotate(1);
    }

    void Draw(Turtle::Window& window) override
    {
        window.draw(m_rect, m_parent->GetTransform()->GetTransformMatrix());
    }

private:
    sf::RectangleShape m_rect;
};

class DemoScene : public Turtle::Scene
{
public:
    void OnCreate() override
    {
        auto object = Create("Test 1");
        object->AddComponent<TestComponent>();
        object->GetTransform()->Move({ 200, 200 });
    }

	void Gui(const Turtle::Time& deltaTime) override
	{
		// Stylizing overlay
        ImGuiWindowFlags imFlags = ImGuiWindowFlags_NoDecoration
            | ImGuiWindowFlags_NoTitleBar
            | ImGuiWindowFlags_AlwaysAutoResize
            | ImGuiWindowFlags_NoSavedSettings
            | ImGuiWindowFlags_NoFocusOnAppearing
            | ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoMouseInputs
            | ImGuiWindowFlags_NoNav;
        ImGui::SetNextWindowPos({ 4, 4 });
        ImGui::SetNextWindowBgAlpha(0.5f);

        // Creating overlay
        ImGui::Begin("FPS Overlay", 0, imFlags);
        ImGui::Text(std::format("{} FPS", floorf(1.f / deltaTime.asSeconds())).c_str());
        ImGui::End();
	}
};

int main()
{
    // Create default window
    Turtle::Window window(Turtle::VideoMode(720, 480), "Turtle Editor");
    Turtle::App game(window);
    Turtle::SceneManager::Instance().AddScene(std::make_unique<DemoScene>(), true);

    game.Run();

    return EXIT_SUCCESS;
}