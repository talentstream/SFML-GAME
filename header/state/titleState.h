#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "common/state.h"

class TitleState final : public State
{
public:
    TitleState(StateStack& stack,Context context);

    void draw() override;

    bool update(sf::Time dt) override;

    bool handleEvent(const sf::Event& event) override;

private:
    sf::Sprite _backgroundSprite;
    sf::Text _text;

    bool _showText; 
    sf::Time _textEffectTime;
};

