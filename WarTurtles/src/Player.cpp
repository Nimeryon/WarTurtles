#include "../include/Player.h"

#include "App.h"

Turtle::Player::Player(GameObject* parent, const std::string& name): Component(parent,name)
{
}

void Turtle::Player::OnCreate()
{
    Component::OnCreate();
    App::GetInputManager()->AddCallback(std::bind(&Player::GoLeft,this),EventType::Left);
    App::GetInputManager()->AddCallback(std::bind(&Player::GoRight,this),EventType::Right);
    App::GetInputManager()->AddCallback(std::bind(&Player::Jump,this),EventType::Jump);
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
    
    m_physic->Velocity = {-m_speed,m_physic->Velocity.y};
}

void Turtle::Player::GoRight()
{
    
    if(!IsPlayerTurn())return;
    m_physic->Velocity = {m_speed,m_physic->Velocity.y};
}

void Turtle::Player::Jump()
{
    
    if(!IsPlayerTurn())return;
    m_physic->AddImpulse({0,m_jumpForce});
}

bool Turtle::Player::IsPlayerTurn()
{
    return (m_turnManager->GetTurnState() == Player1Turn && m_playerId == 0) || (m_turnManager->GetTurnState() == Player2Turn && m_playerId == 1);
}
