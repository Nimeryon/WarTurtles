#include <format>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "imgui-SFML.h"
#include "imgui.h"
#include "App.h"
#include "Managers/AudioManager.h"
#include "Managers/SceneManager.h"
#include "Scene.h"
#include "Components/Renderer/ShapeRenderer.h"
#include "Components/Renderer/SpriteAnimationRenderer.h"
#include "Components/Renderer/SpriteRenderer.h"
#include "Components/Renderer/TextRenderer.h"
#include "GameObjects/GameObject.h"

class DemoScene final : public Turtle::Scene
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
    Turtle::Window window(Turtle::VideoMode(720, 480), "WarTurtles");
    Turtle::App game(window);
    Turtle::SceneManager::Instance().AddScene(std::make_unique<DemoScene>(), true);

    game.Run();

    return EXIT_SUCCESS;
}