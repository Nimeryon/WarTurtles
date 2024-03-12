#ifndef TURN_MANAGER_H
#define TURN_MANAGER_H

#include "Components/Component.h"
#include <functional>
#include <unordered_map> // Pour stocker les durées de tour par type
#include <vector> // Pour stocker les callbacks

#include "Utils/Clock.h"

enum TurnState { WaitingPlayer1=0, Player1Turn=1, WaitingPlayer2=2, Player2Turn=3 };

namespace Turtle
{
    class TurnManager : public Component
    {
    public:
        TurnManager(GameObject* parent, const std::string& name = "TurnManager");
        
        void StartTurn(const TurnState& turnType);
        void SetTurnMaxDuration(const TurnState& turnType, float duration);
        
        void AddTurnCallback(std::function<void(int)> callback);

        void Update(const Time& deltaTime) override;

    private:
        void TriggerCallbacks() const;
        void SwitchTurn(); 
        TurnState m_turnState; 
        std::unordered_map<TurnState, float> m_turnDurations;
        Clock m_timer;
        std::vector<std::function<void(int)>> m_turnCallbacks;
    };
}

#endif /* TURN_MANAGER_H */
