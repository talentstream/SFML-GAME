#pragma once

#include "common/world.h"
#include "common/state.h"

class GameState final : public State
{
public:
    GameState(StateStack& stack, Context context);

    void draw() override;

    bool update(sf::Time dt) override;

    bool handleEvent(const sf::Event& event) override;

private:
    World _world;
    Player& _player;
};

