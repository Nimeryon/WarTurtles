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

class DemoScene : public Turtle::Scene
{
public:
    void OnCreate() override
    {
        // Box 1
        auto box1 = Create("Box 1");
        box1->AddComponent<Turtle::Physic>()->InitPhysicParameters(Turtle::Vector2f{ -150.f, -150.f }, Turtle::Vector2f::zero, 3, 0, 0.5f);
        box1->AddComponent<Turtle::BoxCollisionComponent>()->InitCollisionParameters(100.f, 100.f);
        
        auto* boxRenderer = box1->AddComponent<Turtle::ShapeRenderer<sf::RectangleShape>>();
        sf::RectangleShape rectangleShape;
        rectangleShape.setSize({ 100, 100 });
        rectangleShape.setOrigin({ 50, 50 });
        rectangleShape.setFillColor(sf::Color::Blue);
        boxRenderer->SetShape(rectangleShape);
        boxRenderer->SetColor(sf::Color::Blue);

        box1->GetTransform()->Move({ 600, 200 });

        // Circle 1
        auto circle1 = Create("Circle 1");
        circle1->AddComponent<Turtle::Physic>()->InitPhysicParameters(Turtle::Vector2f{ 100.f, -100.f }, Turtle::Vector2f::zero, 10, 0, 0.5f);
        circle1->AddComponent<Turtle::CircleCollisionComponent>()->InitCollisionParameters({}, 50.f);

        auto* shapeRenderer = circle1->AddComponent<Turtle::ShapeRenderer<sf::CircleShape>>();
        sf::CircleShape circleRender = sf::CircleShape(50.f);
        circleRender.setOrigin({ 50, 50 });
        shapeRenderer->SetShape(circleRender);
        shapeRenderer->SetColor(sf::Color::Blue);

        circle1->GetTransform()->Move({ 200, 200 });

        // Circle 2
        /*auto circle2 = Create("Circle 2");
        circle2->AddComponent<Turtle::Physic>()->InitPhysicParameters(Turtle::Vector2f{ -100.f, -100.f }, Turtle::Vector2f::zero, 5, 0, 0.5f);
        circle2->AddComponent<Turtle::CircleCollisionComponent>()->InitCollisionParameters({}, 50.f);

        shapeRenderer = circle2->AddComponent<Turtle::ShapeRenderer<sf::CircleShape>>();
        shapeRenderer->SetShape(circleRender);
        shapeRenderer->SetColor(sf::Color::Cyan);

        circle2->GetTransform()->Move({ 600, 200 });*/

        // Box 2
        /*auto box2 = Create("Box 2");
        box2->AddComponent<Turtle::Physic>()->InitPhysicParameters(Turtle::Vector2f{ -150.f, -150.f }, Turtle::Vector2f::zero, 2, 0, 0.5f);
        box2->AddComponent<Turtle::BoxCollisionComponent>()->InitCollisionParameters(100.f, 100.f);

        boxRenderer = box2->AddComponent<Turtle::PolygonRenderer>();
        boxRenderer->SetVertice(box2->GetComponent<Turtle::BoxCollisionComponent>()->GetVertice());
        boxRenderer->SetColor(sf::Color::Cyan);

        box2->GetTransform()->Move({ 600, 200 });*/

        // Ground
        auto ground = Create("Ground");
        auto* groundCollisionComp = ground->AddComponent<Turtle::BoxCollisionComponent>();
        groundCollisionComp->InitCollisionParameters(500.f, 50.f);
        groundCollisionComp->SetName("Ground");

        auto* groundRenderer = ground->AddComponent<Turtle::ShapeRenderer<sf::RectangleShape>>();
        sf::RectangleShape groundShape;
        groundShape.setSize({ 500, 50 });
        groundShape.setOrigin({ 250, 25 });
        groundShape.setFillColor(sf::Color::Blue);
        groundRenderer->SetShape(groundShape);
        groundRenderer->SetColor(sf::Color::Blue);

        ground->GetTransform()->Move({ 360, 400 });

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