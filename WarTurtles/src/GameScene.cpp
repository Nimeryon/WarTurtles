#include "../include/GameScene.h"
#include "imgui-SFML.h"
#include "imgui.h"
#include "../include/EndScene.h"
#include "../include/MenuScene.h"
#include "Components/Renderer/ShapeRenderer.h"
#include "Components/Renderer/SpriteAnimationRenderer.h"
#include "Components/Renderer/SpriteRenderer.h"
#include "Components/Renderer/TextRenderer.h"

void GameScene::OnCreate()
{
    Turtle::SceneManager::Instance().RemoveScene(0);
    m_fontManager.LoadFont("GameFont","game.ttf");
        
    m_textureManager.LoadTexture("background","gameBG.jpg");
    
    Turtle::GameObject* background = Create("backgroundGame");
    const auto background_renderer = background->AddComponent<Turtle::SpriteRenderer>();
    background_renderer->InitTexture(&m_textureManager,"background","background");
    background->GetTransform()->SetScale({0.5,0.5});
    
    Turtle::GameObject* backgroundClickable = Create("backgroundClickable");
    const auto backgroundclick_renderer = backgroundClickable->AddComponent<Turtle::ShapeRenderer<sf::RectangleShape>>();
    
    backgroundclick_renderer->SetShape(sf::RectangleShape({2000,2000}));
    backgroundclick_renderer->SetColor(sf::Color(0,0,0,0));
    backgroundclick_renderer->OnClick(std::bind(&GameScene::FinishGame,this));
}

void GameScene::Gui(Turtle::Window& window, const Turtle::Time& deltaTime)
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

void GameScene::FinishGame()
{
    Turtle::SceneManager::Instance().AddScene(std::make_unique<EndScene>("ZIZI"),true);
}

