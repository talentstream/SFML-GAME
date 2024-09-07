#pragma once
#include <SFML/Graphics/Text.hpp>

#include "common/component.h"
#include "common/resourceHolder.h"

namespace GUI
{
    class Label final: public Component
    {
    public:
        using LabelPtr = std::shared_ptr<Label>;

        Label(const std::string& text, const FontHolder& fontHolder);

        bool isSelectable() const override;

        void handleEvent(const sf::Event& event) override;

        void setText(const std::string& text);

    private:

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        sf::Text _text;
    };
}
