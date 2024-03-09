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
		m_audioManager.LoadSound("creeper",Turtle::SoundType::Sound,"creeper.mp3");
		m_audioManager.LoadSound("music",Turtle::SoundType::Music,"music.mp3");
		m_audioManager.SetGlobalVolume(Turtle::SoundType::Sound,100.f);
		m_audioManager.SetGlobalVolume(Turtle::SoundType::Music,5.f);
		m_audioManager.PlaySound("music",true);
		m_audioManager.PlaySound("creeper");
		m_textureManager.LoadTexture("turtle","turtle.png");
		m_fontManager.LoadFont("font","default.ttf");
		
		testSprite = new Turtle::GameObject("Test");
		const auto sprite_renderer = testSprite->AddComponent<Turtle::SpriteAnimationRenderer>();
		sprite_renderer->InitAnimation(&m_textureManager,"turtle","Idle");
		sprite_renderer->SetAnimationSpeed(50);
		testSprite->GetTransform()->SetPosition({10,10});
		testSprite->GetTransform()->SetScale({0.5f,0.5f});

		testFont = new Turtle::GameObject("Test2");
		const auto text_renderer = testSprite->AddComponent<Turtle::TextRenderer>();
		text_renderer->SetFont(m_fontManager.GetFont("font").get());
		text_renderer->SetText("Hello world");
		text_renderer->SetCharacterSize(1);
		text_renderer->SetColor(sf::Color::White);
		testFont->GetTransform()->SetPosition({10,10});

		
		testShape = new Turtle::GameObject("Test3");
		const auto shape_renderer = testShape->AddComponent<Turtle::ShapeRenderer<sf::CircleShape>>();
		shape_renderer->SetShape(sf::CircleShape(10,10));
		shape_renderer->SetColor(sf::Color::Red);
		testShape->GetTransform()->SetPosition({10,10});
	}
	void Update(const Turtle::Time& deltaTime) override
	{
		testSprite->Update(deltaTime);
	}
	void Draw(Turtle::Window& window) override
	{
		testSprite->Draw(window);
		testFont->Draw(window);
		testShape->Draw(window);
		
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
private:
	Turtle::GameObject* testSprite;
	Turtle::GameObject* testFont;
	Turtle::GameObject* testShape;
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