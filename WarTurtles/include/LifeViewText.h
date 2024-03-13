#ifndef LIFE_VIEW_TEXT_H
#define LIFE_VIEW_TEXT_H
#include "Components/Component.h"
#include "Components/Renderer/TextRenderer.h"

namespace Turtle
{
    class Player;

    class LifeViewText : public Component
    {
    public:
        explicit LifeViewText(GameObject* parent, const std::string& name = "LifeViewText");
        void Init(Player* player,TextRenderer* lifeRenderer);
        void Update(const Time& deltaTime) override;
    private:
        TextRenderer* m_lifeRenderer;
        Player* m_player;
        bool isInit = false;
    };
}

#endif /* TURN_VIEW_TEXT_H */
