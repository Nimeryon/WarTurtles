#include "../include/EndScene.h"
#include "../include/MenuScene.h"
#include "imgui.h"
#include "Managers/AudioManager.h"
#include "Components/Renderer/ShapeRenderer.h"
#include "Components/Renderer/TextRenderer.h"
#include "GameObjects/GameObject.h"

void EndScene::OnCreate()
{
    m_fontManager.LoadFont("GameFont","game.ttf");
        
    m_textureManager.LoadTexture("background","gameBG.jpg");
    m_audioManager.LoadSound("music",Turtle::SoundType::Music,"FFFinal.mp3");
    m_audioManager.SetVolume("music",0.4f);
    m_audioManager.PlaySound("music",true);
    
    Turtle::GameObject* background = Create("background");
    const auto background_renderer = background->AddComponent<Turtle::SpriteRenderer>();
    background_renderer->InitTexture(&m_textureManager,"background","background");
    background->GetTransform()->SetScale({0.5,0.5});
    Turtle::GameObject* backgroundClickable = Create("backgroundClickable");
    const auto backgroundclick_renderer = background->AddComponent<Turtle::ShapeRenderer<sf::RectangleShape>>();
    backgroundclick_renderer->SetShape(sf::RectangleShape({3000,2000}));
    backgroundclick_renderer->SetColor(sf::Color(0,0,0,100));
    backgroundclick_renderer->OnClick(std::bind(&EndScene::GoToMenu,this));
        
    Turtle::GameObject* title = Create("WinnerIs");
    const auto titleText = title->AddComponent<Turtle::TextRenderer>();
    titleText->SetFont(m_fontManager.GetFont("GameFont").get());
    titleText->SetText("THE WINNER IS");
    titleText->SetCharacterSize(80);
    title->GetTransform()->SetPosition({20,40});
        
    Turtle::GameObject* winner = Create("Winner");
    const auto winnerText = winner->AddComponent<Turtle::TextRenderer>();
    winnerText->SetFont(m_fontManager.GetFont("GameFont").get());
    winnerText->SetText(m_winner);
    winnerText->SetCharacterSize(80);
    winnerText->SetColor(sf::Color::Blue);
    winner->GetTransform()->SetPosition({40,150});
    
        
        
}

void EndScene::GoToMenu()
{
    Turtle::SceneManager::Instance().RemoveScene(1);
    Turtle::SceneManager::Instance().AddScene(std::make_unique<MenuScene>(),true,0);
}

void EndScene::Gui(Turtle::Window& window, const Turtle::Time& deltaTime)
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
