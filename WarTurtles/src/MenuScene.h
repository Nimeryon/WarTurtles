#pragma once
#include "imgui-SFML.h"
#include "imgui.h"
#include "App.h"
#include "Managers/AudioManager.h"
#include "Managers/SceneManager.h"
#include "Scene.h"
#include "Components/Renderer/PolygonRenderer.h"
#include "Components/Renderer/ShapeRenderer.h"
#include "Components/Renderer/SpriteAnimationRenderer.h"
#include "GameObjects/GameObject.h"

void Test()
{
    std::cout<< "Test" << std::endl;
}
class MenuScene final : public Turtle::Scene
{
public:
    void OnCreate() override
    {
        m_audioManager.LoadSound("music",Turtle::SoundType::Music,"music.mp3");
        m_textureManager.LoadTexture("turtle","turtle.png");

        m_audioManager.PlaySound("music",true);
		
        Turtle::GameObject* testSprite = Create("Test");
        const auto sprite_renderer = testSprite->AddComponent<Turtle::SpriteAnimationRenderer>();
        sprite_renderer->InitAnimation("turtle","Idle");
        testSprite->GetTransform()->SetScale({0.3f,0.3f});

        Turtle::GameObject* myObject = Create("Test2");
        Turtle::ShapeRenderer<sf::RectangleShape>* shape = myObject->AddComponent<Turtle::ShapeRenderer<sf::RectangleShape>>();
        shape->SetShape(sf::RectangleShape({100,10}));
        shape->OnClick(Test);
        Turtle::App::GetInputManager()->AddCallback(Test,Turtle::EventType::Jump);
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
