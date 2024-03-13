#ifndef TURN_VIEW_TEXT_H
#define TURN_VIEW_TEXT_H
#include "Components/Component.h"
#include "Components/Renderer/TextRenderer.h"

namespace Turtle
{
    class TurnManager;

    class TimerViewText : public Component
    {
    public:
        explicit TimerViewText(GameObject* parent, const std::string& name = "TurnViewText");
        void Init(TurnManager* turnManager,TextRenderer* timerRenderer,TextRenderer* turnRenderer);
        void Update(const Time& deltaTime) override;
        void TurnChangedHandler(int turn);
    private:
        TextRenderer* m_timerTextRenderer;
        TextRenderer* m_turnTextRenderer;
        TurnManager* m_turnManager;
        bool isInit = false;

        const std::string& Waiting1 = "Waiting for Player 1";
        const std::string& Playing1 = "Player 1 Turn";
        const std::string& Waiting2 = "Waiting for Player 2";
        const std::string& Playing2 = "Player 2 Turn";
    
    };
}

#endif /* TURN_VIEW_TEXT_H */
