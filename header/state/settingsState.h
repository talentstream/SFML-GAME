#pragma once
#include <SFML/Graphics/Sprite.hpp>

#include "common/state.h"
#include "gui/button.h"
#include "gui/container.h"
#include "gui/label.h"

class SettingsState final : public State
{
public:
	SettingsState(StateStack& stack, Context context);

	void draw() override;

	bool update(sf::Time dt) override;

	bool handleEvent(const sf::Event& event) override;

private:
	void updateLabels();

	void addButtonLabel(Player::Action action, float y, const std::string& text, Context context);

private:
	sf::Sprite _backgroundSprite;
	GUI::Container _container;

	std::array<GUI::Button::ButtonPtr, std::to_underlying(Player::Action::Count)> _bindingButtons;
	std::array<GUI::Label::LabelPtr, std::to_underlying(Player::Action::Count)> _bindingLabels;
};

