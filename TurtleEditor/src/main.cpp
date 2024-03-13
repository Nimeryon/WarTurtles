#include <format>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "imgui-SFML.h"
#include "imgui.h"
#include "App.h"
#include "Scene.h"
#include "Components/Transform.h"
#include "Components/Physic.h"
#include "Components/Collisions/CircleCollisionComponent.h"
#include "Components/Collisions/BoxCollisionComponent.h"
#include "Components/Renderer/ShapeRenderer.h"
#include "Components/Renderer/PolygonRenderer.h"
#include "Managers/SceneManager.h"
#include "Types/Vector2.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/BoxObject.h"
#include "GameObjects/CircleObject.h"

class DemoScene : public Turtle::Scene
{
public:
    void OnCreate() override
    {
        // Box
        auto box = Create<Turtle::BoxObject>("Box");
        box->InitParameters(100, 100, sf::Color::Blue);
        box->InitPhysicsParameters(Turtle::Vector2f{ -50.f, -50.f }, Turtle::Vector2f::zero, 3.f, 0.f, 0.5f, 0.f);
        box->GetTransform()->Move({ 600, 200 });

        // Ground
        auto ground = Create<Turtle::BoxObject>("Ground");
        ground->InitParameters(500, 50, sf::Color::Blue);
        ground->GetTransform()->Move({ 360, 400 });

        // Circle
        auto circle = Create<Turtle::CircleObject>("Circle");
        circle->InitParameters(50, {}, sf::Color::Blue);
        circle->GetTransform()->Move({ 200, 320 });

        Scene::OnCreate();
    }

	void Gui(Turtle::Window& window, const Turtle::Time& deltaTime) override
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

        const auto& mousePos = sf::Mouse::getPosition(window);

        // Creating overlay
        ImGui::Begin("Debug Overlay", 0, imFlags);
        ImGui::Text(std::format("{} FPS", floorf(1.f / deltaTime.asSeconds())).c_str());
        ImGui::Text(std::format("Mouse X: {}, Mouse Y: {}", mousePos.x, mousePos.y).c_str());
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