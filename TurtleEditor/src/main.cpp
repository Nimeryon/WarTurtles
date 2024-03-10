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
#include "Components/Collisions/PolygonCollisionComponent.h"
#include "Components/Renderer/ShapeRenderer.h"
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

        auto circle1 = Create("Circle 1");
        circle1->AddComponent<Turtle::Physic>();
        circle1->GetComponent<Turtle::Physic>()->InitPhysicParameters(Turtle::Vector2f{ 100.f,-100.f }, Turtle::Vector2f::zero, 5, 0, 0.5f);
        circle1->AddComponent<Turtle::CircleCollisionComponent>();
        Turtle::Vector2f testvec{ 200,200 };
        circle1->GetComponent<Turtle::CircleCollisionComponent>()->InitCollisionParameters(testvec, 50.f);
        circle1->AddComponent<Turtle::ShapeRenderer<sf::CircleShape>>();
        sf::CircleShape circleRender = sf::CircleShape(50.f);
        circle1->GetComponent<Turtle::ShapeRenderer<sf::CircleShape>>()->SetShape(circleRender);
        circle1->GetComponent<Turtle::ShapeRenderer<sf::CircleShape>>()->SetColor(sf::Color::Blue);
        circle1->GetTransform()->Move({ 200, 200 });

        auto circle2 = Create("Circle 2");
        circle2->AddComponent<Turtle::Physic>();
        circle2->GetComponent<Turtle::Physic>()->InitPhysicParameters(Turtle::Vector2f{ -150.f,-150.f }, Turtle::Vector2f::zero, 2, 0, 0.5f);
        circle2->AddComponent<Turtle::PolygonCollisionComponent>();
        testvec = Turtle::Vector2f{ 600,200 };
        circle2->GetComponent<Turtle::PolygonCollisionComponent>()->InitCollisionParameters(testvec,0.f,100.f,100.f);
        
        circle2->AddComponent<Turtle::ShapeRenderer<sf::RectangleShape>>();
        sf::RectangleShape renctangleRender = sf::RectangleShape({ 100,100 });
        circle2->GetComponent<Turtle::ShapeRenderer<sf::RectangleShape>>()->SetShape(renctangleRender);
        circle2->GetComponent<Turtle::ShapeRenderer<sf::RectangleShape>>()->SetColor(sf::Color::White);
        circle2->GetTransform()->Move({ 600, 200 });

        Scene::OnCreate();
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