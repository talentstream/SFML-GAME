#include "state/settingsState.h"

#include "common/player.h"

SettingsState::SettingsState(StateStack& stack, Context context) :
	State{stack, context},
	_container{}
{
	_backgroundSprite.setTexture(context._textureHolder->get(TextureID::TitleScreen));

	addButtonLabel(Player::Action::MoveLeft, 150.f, "Move Left", context);
	addButtonLabel(Player::Action::MoveRight, 200.f, "Move Right", context);
	addButtonLabel(Player::Action::MoveUp, 250.f, "Move Up", context);
	addButtonLabel(Player::Action::MoveDown, 300.f, "Move Down", context);

	updateLabels();

	auto backButton = std::make_shared<GUI::Button>(*context._fontHolder, *context._textureHolder);
	backButton->setPosition(80.f, 375.f);
	backButton->setText("Back");
	backButton->setCallback(std::bind(&SettingsState::requestStackPop, this));

	_container.pack(backButton);
}

void SettingsState::draw()
{
	auto& window = *getContext()._window;

	window.draw(_backgroundSprite);
	window.draw(_container);
}

bool SettingsState::update(sf::Time dt)
{
	return true;
}

bool SettingsState::handleEvent(const sf::Event& event)
{
	bool isKeyBinding{false};

	for (auto i = 0; i < std::to_underlying(Player::Action::Count); ++i)
	{
		if (_bindingButtons[i]->isActive())
		{
			isKeyBinding = true;
			if (event.type == sf::Event::KeyReleased)
			{
				auto key = event.key.code;
				getContext()._player->assignKey(static_cast<Player::Action>(i), key);
				_bindingButtons[i]->deactivate();
			}
			break;
		}
	}

	if(isKeyBinding)
	{
		updateLabels();
	}
	else
	{
		_container.handleEvent(event);
	}

	return false;
}

void SettingsState::updateLabels()
{
	auto& player = *getContext()._player;

	for (auto i = 0; i < std::to_underlying(Player::Action::Count); ++i)
	{
		auto key = player.getAssignedKey(static_cast<Player::Action>(i));
		_bindingLabels[i]->setText(std::to_string(key));
	}
}

void SettingsState::addButtonLabel(Player::Action action, float y, const std::string& text, Context context)
{
	auto index = std::to_underlying(action);
	_bindingButtons[index] = std::make_shared<GUI::Button>(*context._fontHolder, *context._textureHolder);
	_bindingButtons[index]->setPosition(80.f, y);
	_bindingButtons[index]->setText(text);
	_bindingButtons[index]->setToggle(true);

	_bindingLabels[index] = std::make_shared<GUI::Label>("", *context._fontHolder);
	_bindingLabels[index]->setPosition(300.f, y + 15.f);

	_container.pack(_bindingButtons[index]);
	_container.pack(_bindingLabels[index]);
}
