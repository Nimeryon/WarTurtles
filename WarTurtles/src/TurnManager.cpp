#include "../include/TurnManager.h"

namespace Turtle
{
    TurnManager::TurnManager(GameObject* parent, const std::string& name) : Component(parent, name), m_turnState(WaitingPlayer1)
    {
    }

    void TurnManager::StartTurn(const TurnState& turnType)
    {
        m_turnState = turnType;
        auto it = m_turnDurations.find(turnType);
        if (it == m_turnDurations.end()) {
            m_turnDurations[turnType] = 10.0f;
        }
        m_timer.restart();
        TriggerCallbacks();
    }

    void TurnManager::SetTurnMaxDuration(const TurnState& turnType, float duration)
    {
        m_turnDurations[turnType] = duration;
    }

    void TurnManager::SwitchTurn()
    {
        StartTurn(static_cast<TurnState>((m_turnState + 1)%4));
    }
    void TurnManager::Update(const Time& deltaTime)
    {
        if (m_timer.getElapsedTime().asSeconds() >= m_turnDurations[m_turnState])
        {
            SwitchTurn();
        }
    }

    int TurnManager::GetTimerTime()
    {
        return  m_turnDurations[m_turnState] - m_timer.getElapsedTime().asSeconds();
    }

    TurnState TurnManager::GetTurnState()
    {
        return m_turnState;
    }

    void TurnManager::AddTurnCallback(std::function<void(int)> callback)
    {
        m_turnCallbacks.push_back(callback);
    }
    void TurnManager::TriggerCallbacks() const
    {
        for (auto& callback : m_turnCallbacks) {
            callback(m_turnState);
        }
    }
}
