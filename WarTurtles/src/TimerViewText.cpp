#include "../include/TimerViewText.h"
#include "../include/TurnManager.h"
Turtle::TimerViewText::TimerViewText(GameObject* parent, const std::string& name): Component(parent,name)
{
}

void Turtle::TimerViewText::Init(TurnManager* turnManager, TextRenderer* timerRenderer, TextRenderer* turnRenderer)
{
    m_turnManager = turnManager;
    m_timerTextRenderer = timerRenderer;
    m_turnTextRenderer = turnRenderer;
    m_turnManager->AddTurnCallback(std::bind(&Turtle::TimerViewText::TurnChangedHandler,this,std::placeholders::_1));
    isInit = true;
}
void Turtle::TimerViewText::TurnChangedHandler(int turn)
{
    switch(turn)
    {
    case 0:
        m_turnTextRenderer->SetText(Waiting1);
        break;
    case 1:
        m_turnTextRenderer->SetText(Playing1);
        break;
    case 2:
        m_turnTextRenderer->SetText(Waiting2);
        break;
    case 3:
        m_turnTextRenderer->SetText(Playing2);
        break;
    }
}

void Turtle::TimerViewText::Update(const Time& deltaTime)
{
    if(!isInit)return;
    Component::Update(deltaTime);
    m_timerTextRenderer->SetText(std::to_string(m_turnManager->GetTimerTime()));
}
