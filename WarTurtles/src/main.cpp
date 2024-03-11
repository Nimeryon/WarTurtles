#include <format>
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "App.h"
#include "MenuScene.h"

int main()
{
    Turtle::Window window(Turtle::VideoMode(720, 480), "WarTurtles");
    Turtle::App game(window);
    Turtle::SceneManager::Instance().AddScene(std::make_unique<MenuScene>(), true);

    game.Run();

    return EXIT_SUCCESS;
}