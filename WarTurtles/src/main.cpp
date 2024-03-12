#include <format>
#include <SFML/Graphics.hpp>
#include "App.h"
#include "imgui.h"
#include "../include/GameScene.h"

#include "Managers/SceneManager.h"
#include "../include/MenuScene.h"
int main()
{
    Turtle::Window window(Turtle::VideoMode(1080, 720), "WarTurtles", sf::Style::Titlebar | sf::Style::Close);
    Turtle::App game(window);
    Turtle::SceneManager::Instance().AddScene(std::make_unique<MenuScene>(), true);
    game.Run();

    return EXIT_SUCCESS;
}
