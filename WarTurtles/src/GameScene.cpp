﻿#include "../include/GameScene.h"
#include "imgui-SFML.h"
#include "imgui.h"
#include "../include/EndScene.h"
#include "../include/LifeViewText.h"
#include "../include/Player.h"
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

    m_audioManager.LoadSound("music",Turtle::SoundType::Music,"music.mp3");
    m_audioManager.SetVolume("music",0.5f);
    m_audioManager.PlaySound("music",true);

    m_audioManager.LoadSound("hurt",Turtle::SoundType::Music,"hurt.mp3");
    m_audioManager.SetVolume("hurt",0.5f);
    m_audioManager.LoadSound("throw",Turtle::SoundType::Music,"throw.mp3");
    m_audioManager.SetVolume("throw",0.5f);
    m_audioManager.LoadSound("explosion",Turtle::SoundType::Music,"explosion.wav");
    
    m_textureManager.LoadTexture("background","gameBG.jpg");
    m_textureManager.LoadTexture("Player","turtle.png");
    m_textureManager.LoadTexture("Crate","crate.png");
    m_textureManager.LoadTexture("Bullet","bullet.png");
    
    Turtle::GameObject* background = Create("backgroundGame");
    const auto background_renderer = background->AddComponent<Turtle::SpriteRenderer>();
    background_renderer->InitTexture(&m_textureManager,"background","background");
    background->GetTransform()->SetScale({0.5,0.5});
    background->GetTransform()->SetPosition({0,-100});

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

    auto leftWall = Create("LeftWall");
    auto* leftWallCollision = leftWall->AddComponent<Turtle::BoxCollisionComponent>();
    leftWallCollision->InitCollisionParameters(50, 2000);
    leftWallCollision->SetName("Wall");
    auto rightWall = Create("RightWall");
    auto* rightWallCollision = rightWall->AddComponent<Turtle::BoxCollisionComponent>();
    rightWallCollision->InitCollisionParameters(50, 2000);
    rightWallCollision->SetName("Wall");
    rightWall->GetTransform()->Move({1080,0});
    

    auto turnManagerGO = Create("TurnManager");
    auto* turnManager = turnManagerGO->AddComponent<Turtle::TurnManager>();
    turnManager->SetTurnMaxDuration(WaitingPlayer1,5.f);
    turnManager->SetTurnMaxDuration(WaitingPlayer2,5.f);
    turnManager->SetTurnMaxDuration(Player1Turn,30.f);
    turnManager->SetTurnMaxDuration(Player2Turn,30.f);
    
    auto player1 = Create("Player1");
    auto* physicsPlayer1 = player1->AddComponent<Turtle::Physic>();
    physicsPlayer1->InitPhysicParameters(Turtle::Vector2f{ 0, 0 }, Turtle::Vector2f::zero, 3.f, 0.4f, 0.6f, 0.5f, 0.f);
    physicsPlayer1->BlockAngularVelocity(true);
    player1->AddComponent<Turtle::BoxCollisionComponent>()->InitCollisionParameters(300.f, 600.f);
    auto* player1Animation = player1->AddComponent<Turtle::SpriteAnimationRenderer>();
    player1->AddComponent<Turtle::Player>()->Init(0,physicsPlayer1,player1Animation,turnManager);
    player1Animation->InitAnimation("Player","Idle");
    player1Animation->SetOrigin({350,350});
    player1Animation->SetScale({0.1f,0.1f});
    player1->GetTransform()->SetPosition({200,500});
    player1->GetTransform()->SetScale({0.2,0.2});

    auto player2 = Create("Player2");
    auto* physicsPlayer2 = player2->AddComponent<Turtle::Physic>();
    physicsPlayer2->InitPhysicParameters(Turtle::Vector2f{ 0, 0 }, Turtle::Vector2f::zero, 3.f, 0.4f, 0.6f, 0.5f, 0.f);
    physicsPlayer2->BlockAngularVelocity(true);
    player2->AddComponent<Turtle::BoxCollisionComponent>()->InitCollisionParameters(300.f, 600.f);
    auto* player2Animation = player2->AddComponent<Turtle::SpriteAnimationRenderer>();
    player2->AddComponent<Turtle::Player>()->Init(1,physicsPlayer2,player2Animation,turnManager);
    player2Animation->InitAnimation("Player","Idle");
    player2Animation->SetOrigin({350,350});
    player2Animation->SetScale({0.1f,0.1f});
    player2->GetTransform()->SetPosition({800,500});
    player2->GetTransform()->SetScale({0.2,0.2});
    player2Animation->Flip(true);
    

    auto crate1 = Create("Crate1");
    crate1->AddComponent<Turtle::Physic>()->InitPhysicParameters(Turtle::Vector2f{ 0, 0 }, Turtle::Vector2f::zero, 3.f, 0.4f, 0.6f, 0.5f, 0.f);
    crate1->AddComponent<Turtle::BoxCollisionComponent>()->InitCollisionParameters(512.f, 512.f);
    auto* crate1Renderer = crate1->AddComponent<Turtle::SpriteRenderer>();
    crate1Renderer->InitTexture(&m_textureManager,"Crate","crate");
    crate1Renderer->SetOrigin({256,256});
    crate1->GetTransform()->SetScale({0.15f,0.15f});
    crate1->GetTransform()->SetPosition({500,550});
    auto crate2 = Create("Crate2");
    crate2->AddComponent<Turtle::Physic>()->InitPhysicParameters(Turtle::Vector2f{ 0, 0 }, Turtle::Vector2f::zero, 3.f, 0.4f, 0.6f, 0.5f, 0.f);
    crate2->AddComponent<Turtle::BoxCollisionComponent>()->InitCollisionParameters(512.f, 512.f);
    auto* crate2Renderer = crate2->AddComponent<Turtle::SpriteRenderer>();
    crate2Renderer->InitTexture(&m_textureManager,"Crate","crate");
    crate2Renderer->SetOrigin({256,256});
    crate2->GetTransform()->SetScale({0.15f,0.15f});
    crate2->GetTransform()->SetPosition({600,550});
    auto crate3 = Create("Crate3");
    crate3->AddComponent<Turtle::Physic>()->InitPhysicParameters(Turtle::Vector2f{ 0, 0 }, Turtle::Vector2f::zero, 3.f, 0.4f, 0.6f, 0.5f, 0.f);
    crate3->AddComponent<Turtle::BoxCollisionComponent>()->InitCollisionParameters(512.f, 512.f);
    auto* crate3Renderer = crate3->AddComponent<Turtle::SpriteRenderer>();
    crate3Renderer->InitTexture(&m_textureManager,"Crate","crate");
    crate3Renderer->SetOrigin({256,256});
    crate3->GetTransform()->SetScale({0.15f,0.15f});
    crate3->GetTransform()->SetPosition({550,450});
    
    
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


    auto lifeP1 = Create("lifeP1");
    auto* lifeP1Text = lifeP1->AddComponent<Turtle::TextRenderer>();
    lifeP1->GetTransform()->SetPosition({120,640});
    lifeP1Text->SetFont(m_fontManager.GetFont("GameFont").get());
    lifeP1Text->SetCharacterSize(50);

    auto lifeP2 = Create("lifeP2");

    auto* lifeP2Text = lifeP2->AddComponent<Turtle::TextRenderer>();
    lifeP2->GetTransform()->SetPosition({750,640});
    lifeP2Text->SetFont(m_fontManager.GetFont("GameFont").get());
    lifeP2Text->SetCharacterSize(50);

    lifeP1->AddComponent<Turtle::LifeViewText>()->Init(player1->GetComponent<Turtle::Player>(),lifeP1Text);
    lifeP2->AddComponent<Turtle::LifeViewText>()->Init(player2->GetComponent<Turtle::Player>(),lifeP2Text);
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

