#include <format>
#include <SFML/Graphics.hpp>

#include "imgui-SFML.h"
#include "imgui.h"
#include "App.h"
#include "Scene.h"
#include "SceneManager.h"

class DemoScene : public Turtle::Scene
{
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
    sf::RenderWindow window(sf::VideoMode(720, 480), "Turtle engine exemple");

    Turtle::App game(window);

    Turtle::SceneManager::Instance().AddScene(std::make_unique<DemoScene>());
    Turtle::SceneManager::Instance().SetScene(0);

    game.Run();

    return EXIT_SUCCESS;
}