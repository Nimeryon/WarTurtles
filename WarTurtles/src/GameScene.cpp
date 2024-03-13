#include "../include/GameScene.h"
#include "imgui-SFML.h"
#include "imgui.h"
#include "../include/EndScene.h"
#include "../include/TimerViewText.h"
#include "../include/TurnManager.h"
#include "Components/Collisions/BoxCollisionComponent.h"
#include "Components/Renderer/ShapeRenderer.h"
#include "Components/Renderer/SpriteAnimationRenderer.h"
#include "Components/Renderer/SpriteRenderer.h"
#include "Components/Renderer/TextRenderer.h"

void Test(int _round)
{
    std::cout << _round;
}
void GameScene::OnCreate()
{
    Turtle::SceneManager::Instance().RemoveScene(0);
    m_fontManager.LoadFont("GameFont","game.ttf");
    m_textureManager.LoadTexture("background","gameBG.jpg");
    m_textureManager.LoadTexture("Player","turtle.png");
    
    Turtle::GameObject* background = Create("backgroundGame");
    const auto background_renderer = background->AddComponent<Turtle::SpriteRenderer>();
    background_renderer->InitTexture(&m_textureManager,"background","background");
    background->GetTransform()->SetScale({0.5,0.5});
    background->GetTransform()->SetPosition({0,-100});
    
    Turtle::GameObject* backgroundClickable = Create("backgroundClickable");
    const auto backgroundclick_renderer = backgroundClickable->AddComponent<Turtle::ShapeRenderer<sf::RectangleShape>>();
    
    backgroundclick_renderer->SetShape(sf::RectangleShape({2000,2000}));
    backgroundclick_renderer->SetColor(sf::Color(0,0,0,0));
    backgroundclick_renderer->OnClick(std::bind(&GameScene::FinishGame,this));


    auto ground = Create("Ground");
    auto* groundCollisionComp = ground->AddComponent<Turtle::BoxCollisionComponent>();
    groundCollisionComp->InitCollisionParameters(1080, 200);
    groundCollisionComp->SetName("Ground");

    auto* groundRenderer = ground->AddComponent<Turtle::ShapeRenderer<sf::RectangleShape>>();
    sf::RectangleShape groundShape;
    groundShape.setSize({ 1080, 200 });
    groundShape.setOrigin({ 540, 100});
    groundShape.setFillColor(sf::Color(117,41,0));
    groundRenderer->SetShape(groundShape);
    groundRenderer->SetColor(sf::Color(117,41,0));

    ground->GetTransform()->SetPosition({540,700});

    auto player = Create("Player1");
    //player->AddComponent<Turtle::Physic>()->InitPhysicParameters(Turtle::Vector2f{ -150.f, -150.f }, Turtle::Vector2f::zero, 3, 0, 0.5f);
    player->AddComponent<Turtle::BoxCollisionComponent>()->InitCollisionParameters(100.f, 100.f);
    auto* player1Animation = player->AddComponent<Turtle::SpriteAnimationRenderer>();
    player1Animation->InitAnimation("Player","Idle");


    auto turnManagerGO = Create("TurnManager");
    auto* turnManager = turnManagerGO->AddComponent<Turtle::TurnManager>();
    turnManager->SetTurnMaxDuration(WaitingPlayer1,5.f);
    turnManager->SetTurnMaxDuration(WaitingPlayer2,5.f);
    turnManager->SetTurnMaxDuration(Player1Turn,30.f);
    turnManager->SetTurnMaxDuration(Player2Turn,30.f);
    turnManager->AddTurnCallback(Test);
    
    auto turnTextGO = Create("TurnText");
    auto timerTextGO = Create("TimerText");
    turnTextGO->SetParent(turnManagerGO);
    timerTextGO->SetParent(turnManagerGO);
    
    auto* turnText = turnTextGO->AddComponent<Turtle::TextRenderer>();
    turnTextGO->GetTransform()->SetPosition({10,10});
    turnText->SetFont(m_fontManager.GetFont("GameFont").get());
    turnText->SetCharacterSize(60);
    
    auto* timerText = timerTextGO->AddComponent<Turtle::TextRenderer>();
    timerTextGO->GetTransform()->SetPosition({10,100});
    timerText->SetFont(m_fontManager.GetFont("GameFont").get());
    timerText->SetCharacterSize(60);
    auto* timerView = turnManagerGO->AddComponent<Turtle::TimerViewText>();
    timerView->Init(turnManager,timerText,turnText);

    turnManager->StartTurn(WaitingPlayer1);
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

