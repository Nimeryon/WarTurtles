#pragma once
#include "App.h"
#include "Managers/SceneManager.h"
#include "Scene.h"

class GameScene final : public Turtle::Scene
{
public:
    
    void OnCreate() override;
    void Gui(Turtle::Window& window, const Turtle::Time& deltaTime) override;
    void FinishGame();
};
