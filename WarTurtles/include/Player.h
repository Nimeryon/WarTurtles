#pragma once
#include "TurnManager.h"
#include "Components/Component.h"
#include "Components/Physic.h"
#include "Components/Renderer/SpriteAnimationRenderer.h"
#include "GameObjects/GameObject.h"

namespace Turtle
{
    class Player : public Component
    {
    public:
        explicit Player(GameObject* parent, const std::string& name = "TurnViewText");
        void OnCreate() override;
        void Init(unsigned playerId,Physic* physic,SpriteAnimationRenderer* spriteAnimationRenderer,TurnManager* turnManager);
        void Update(const Time& deltaTime) override;
        void GoLeft();
        void GoRight();
        void Jump();
        void Throw(const Vector2i& mousePos);
        void OnBulletHit(const GameObject& gameObject);
        void GroundHitTest(const GameObject& gameObject);
        void GetHit();
        int GetLife();
        int GetMaxLife();
    private:
        bool IsPlayerTurn();
        Physic* m_physic;
        SpriteAnimationRenderer* m_spriteAnimationRenderer;
        TurnManager* m_turnManager;
        GameObject* currentBullet = nullptr;
        unsigned m_playerId;
        unsigned m_maxLife = 3;
        unsigned m_life = 3;
        float m_jumpForce = -400;
        float m_speed = 50;
        bool isGrounded = true;

        const std::string& IdleAnim = "Idle";
        const std::string& JumpAnim = "Jump";
        const std::string& WalkAnim = "Walk";
        const std::string& HitAnim = "Hit";
        const std::string& ThrowAnim = "Throw";
        
        
    };
}

