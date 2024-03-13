#include "../include/Player.h"

#include "App.h"
#include "../include/EndScene.h"
#include "Components/Collisions/BoxCollisionComponent.h"
#include "Components/Renderer/SpriteRenderer.h"
#include "GameObjects/BoxObject.h"
#include "GameObjects/CircleObject.h"
#include "Managers/SceneManager.h"


Turtle::Player::Player(GameObject* parent, const std::string& name): Component(parent,name)
{
}

void Turtle::Player::OnCreate()
{
    Component::OnCreate();
    App::GetInputManager()->AddCallback(std::bind(&Player::GoLeft,this),EventType::Left);
    App::GetInputManager()->AddCallback(std::bind(&Player::GoRight,this),EventType::Right);
    App::GetInputManager()->AddCallback(std::bind(&Player::Jump,this),EventType::Jump);
    App::GetInputManager()->AddClickCallback(std::bind(&Player::Throw,this,std::placeholders::_1));
    m_parent->SubscribeToCollision(std::bind(&Player::GroundHitTest,this,std::placeholders::_1));
}

void Turtle::Player::Init(unsigned playerId,Physic* physic, SpriteAnimationRenderer* spriteAnimationRenderer,TurnManager* turnManager)
{
    m_physic = physic;
    m_spriteAnimationRenderer = spriteAnimationRenderer;
    m_turnManager = turnManager;
    m_playerId = playerId;
}

void Turtle::Player::Update(const Time& deltaTime)
{
    if(m_physic->Velocity.y < -10 || m_physic->Velocity.y > 10)
    {
        m_spriteAnimationRenderer->SetAnimation(JumpAnim,1);
    }
    else if(m_physic->Velocity.x > 10)
    {
        m_spriteAnimationRenderer->SetAnimation(WalkAnim,0.1);
    }
    else if(m_physic->Velocity.x < -10)
    {
        m_spriteAnimationRenderer->SetAnimation(WalkAnim,0.1);
    }
    else
    {
        m_spriteAnimationRenderer->SetAnimation(IdleAnim,1);
    }
}

void Turtle::Player::GoLeft()
{
    
    if(!IsPlayerTurn())return;
    m_spriteAnimationRenderer->Flip(true);
    m_physic->Velocity = {-m_speed,m_physic->Velocity.y};
}

void Turtle::Player::GoRight()
{
    
    if(!IsPlayerTurn())return;
    m_spriteAnimationRenderer->Flip(false);
    m_physic->Velocity = {m_speed,m_physic->Velocity.y};
}

void Turtle::Player::Jump()
{
    
    if(!IsPlayerTurn() || !isGrounded)return;
    isGrounded = false;
    m_physic->AddImpulse({0,m_jumpForce});
}

void Turtle::Player::Throw(const Vector2i& mousePos)
{
    if(!IsPlayerTurn())return;
    m_turnManager->SwitchTurn();
    Vector2f playerPos = m_parent->GetTransform()->GetPosition();
    
    Vector2f direction = Vector2f(mousePos.x - playerPos.x, mousePos.y - playerPos.y);
    Vector2f normalizedDirection = direction;
    float length = sqrt(normalizedDirection.x * normalizedDirection.x + normalizedDirection.y * normalizedDirection.y);
    normalizedDirection.x /= length;
    normalizedDirection.y /= length;
    
    auto bullet = SceneManager::Instance().GetCurrentScene()->Create("BULLET");
    auto physic = bullet->AddComponent<Physic>();
    physic->InitPhysicParameters(Vector2f{ 0, 0 }, Vector2f::zero, 3.f, 0.4f, 0.6f, 0.5f, 3.f);
    bullet->AddComponent<BoxCollisionComponent>()->InitCollisionParameters(640.f, 404.f);
    auto* bulletRenderer = bullet->AddComponent<SpriteRenderer>();
    bulletRenderer->InitTexture(&SceneManager::Instance().GetCurrentScene()->GetTextureManager(),"Bullet","bullet");
    bulletRenderer->SetOrigin({320,202});
    bullet->GetTransform()->SetScale({0.08f,0.08f});
    bullet->GetTransform()->SetPosition(playerPos+(normalizedDirection*100));
    bullet->SubscribeToCollision(std::bind(&Player::OnBulletHit,this,std::placeholders::_1));
    physic->AddImpulse(direction);
    currentBullet = bullet;
}

void Turtle::Player::OnBulletHit(const GameObject& gameObject)
{
    if( (gameObject.GetName() == "Player1"  && m_playerId ==1) || (gameObject.GetName() == "Player2" && m_playerId ==0) )
    {
        if(currentBullet == nullptr)return;
        currentBullet->Destroy();
        currentBullet = nullptr;
    }
}

void Turtle::Player::GroundHitTest(const GameObject& gameObject)
{
    if(gameObject.GetName() == "Ground")isGrounded = true;
}

void Turtle::Player::GetHit()
{
    m_life--;
    if(m_life<=0)
    {
        SceneManager::Instance().AddScene(std::make_unique<EndScene>(m_playerId==0?"Player 2":"Player 1"));
    }
}

int Turtle::Player::GetLife()
{
    return m_life;
}

int Turtle::Player::GetMaxLife()
{
    return m_maxLife;
}

bool Turtle::Player::IsPlayerTurn()
{
    return (m_turnManager->GetTurnState() == Player1Turn && m_playerId == 0) || (m_turnManager->GetTurnState() == Player2Turn && m_playerId == 1);
}
