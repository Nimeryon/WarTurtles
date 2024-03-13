#include "../include/MenuScene.h"
#include "../include/GameScene.h"
#include "imgui.h"
#include "Managers/AudioManager.h"
#include "Components/Renderer/ShapeRenderer.h"
#include "Components/Renderer/SpriteRenderer.h"
#include "Components/Renderer/TextRenderer.h"
#include "GameObjects/GameObject.h"

void MenuScene::OnCreate()
{
    Turtle::SceneManager::Instance().RemoveScene(2);  
    m_fontManager.LoadFont("GameFont","game.ttf");
    m_audioManager.LoadSound("music",Turtle::SoundType::Music,"music.mp3");
    m_audioManager.LoadSound("click",Turtle::SoundType::Music,"click.mp3");
    m_audioManager.SetVolume("music",0.5f);
    m_audioManager.SetVolume("click",1.f);
    m_textureManager.LoadTexture("background","gameBG.jpg");
    m_audioManager.PlaySound("music",true);
        
    Turtle::GameObject* background = Create("background");
    const auto background_renderer = background->AddComponent<Turtle::SpriteRenderer>();
    background_renderer->InitTexture(&m_textureManager,"background","background");
    background->GetTransform()->SetScale({0.5,0.5});
        
    Turtle::GameObject* title = Create("Title");
    const auto titleText = title->AddComponent<Turtle::TextRenderer>();
    titleText->SetFont(m_fontManager.GetFont("GameFont").get());
    titleText->SetText("WAR TURTLE");
    titleText->SetCharacterSize(100);
    title->GetTransform()->SetPosition({20,20});

    Turtle::GameObject* buttonStart = Create("ButtonStart");
    const auto buttonBg = buttonStart->AddComponent<Turtle::ShapeRenderer<sf::RectangleShape>>();
    buttonBg->SetShape(sf::RectangleShape({500,100}));
    buttonBg->SetColor(sf::Color::Black);
    buttonStart->GetTransform()->SetPosition({100,250});
    Turtle::GameObject* buttonStartTextGO = Create("StartText");
    buttonStartTextGO->SetParent(buttonStart);
    const auto startText = buttonStartTextGO->AddComponent<Turtle::TextRenderer>();
    startText->SetFont(m_fontManager.GetFont("GameFont").get());
    startText->SetText("START GAME");
    startText->SetCharacterSize(50);
    buttonStartTextGO->GetTransform()->SetPosition({10,20});
    buttonBg->OnClick([this] {StartGame();});
        
    Turtle::GameObject* buttonQuit = Create("ButtonQuit");
    const auto buttonQuitBg = buttonQuit->AddComponent<Turtle::ShapeRenderer<sf::RectangleShape>>();
    buttonQuitBg->SetShape(sf::RectangleShape({500,100}));
    buttonQuitBg->SetColor(sf::Color::Black);
    buttonQuit->GetTransform()->SetPosition({100,400});
    Turtle::GameObject* buttonQuitTextGO = Create("QuitText");
    buttonQuitTextGO->SetParent(buttonQuit);
    const auto quitText = buttonQuitTextGO->AddComponent<Turtle::TextRenderer>();
    quitText->SetFont(m_fontManager.GetFont("GameFont").get());
    quitText->SetText("QUIT GAME");
    quitText->SetCharacterSize(50);
    buttonQuitTextGO->GetTransform()->SetPosition({10,20});
    buttonQuitBg->OnClick([this] { QuitGame(); });
}

void MenuScene::Gui(Turtle::Window& window, const Turtle::Time& deltaTime)
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

void MenuScene::StartGame()
{
    m_audioManager.StopSound("music");
    m_audioManager.PlaySound("click");
    Turtle::SceneManager::Instance().AddScene(std::make_unique<GameScene>(),true);
}

void MenuScene::QuitGame()
{
    m_audioManager.PlaySound("click");
    Turtle::App::Quit();
}
