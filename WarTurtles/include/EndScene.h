#pragma once
#include "App.h"
#include "Managers/SceneManager.h"
#include "Scene.h"
#include "Components/Renderer/SpriteRenderer.h"

class EndScene final : public Turtle::Scene
{
public:
    EndScene(const std::string& winner):m_winner(winner){}

    void OnCreate() override;
    void GoToMenu();
    void Gui(Turtle::Window& window, const Turtle::Time& deltaTime) override;
private:
    std::string m_winner = "Player NULL";
};
