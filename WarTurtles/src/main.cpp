#include <format>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "imgui-SFML.h"
#include "imgui.h"
#include "App.h"
#include "Managers/AudioManager.h"
#include "Managers/SceneManager.h"
#include "Scene.h"

class DemoScene : public Turtle::Scene
{
	void OnCreate() override
	{
		m_audioManager.LoadSound("creeper",Turtle::SoundType::Sound,"creeper.mp3");
		m_audioManager.LoadSound("music",Turtle::SoundType::Music,"music.mp3");
		m_audioManager.SetGlobalVolume(Turtle::SoundType::Sound,100.f);
		m_audioManager.SetGlobalVolume(Turtle::SoundType::Music,5.f);
		m_audioManager.PlaySound("music",true);
		m_audioManager.PlaySound("creeper");

		m_textureManager.LoadTexture("debug","debug.png");
		for(const auto& data : m_textureManager.GetTextureData("debug").SpritesData)
		{
			std::cout<<data.first<<std::endl;
		}
		
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