#include "../include/LifeViewText.h"

#include "../include/Player.h"

Turtle::LifeViewText::LifeViewText(GameObject* parent, const std::string& name): Component(parent,name)
{
}

void Turtle::LifeViewText::Init(Player* player, TextRenderer* lifeRenderer)
{
    m_player = player;
    m_lifeRenderer = lifeRenderer;
    isInit = true;
}

void Turtle::LifeViewText::Update(const Time& deltaTime)
{
    if(!isInit)return;
    m_lifeRenderer->SetText(std::to_string(m_player->GetLife())+"/"+std::to_string(m_player->GetMaxLife()));

    Component::Update(deltaTime);
}
