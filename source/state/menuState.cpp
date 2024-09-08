#include "state/menuState.h"

#include "common/utility.h"
#include "gui/button.h"

MenuState::MenuState(StateStack& stack, Context context) :
	State{stack, context},
	_container{}
{
	auto& texture = context._textureHolder->get(TextureID::TitleScreen);
	_backgroundSprite.setTexture(texture);


	using namespace GUI;
	auto playButton = std::make_shared<Button>(*context._fontHolder, *context._textureHolder);
	playButton->setPosition(100, 250);
	playButton->setText("Play");
	playButton->setCallback([this]()
	{
		requestStackPop();
		requestStackPush(StateID::Game);
	});

	auto settingButton = std::make_shared<Button>(*context._fontHolder, *context._textureHolder);
	settingButton->setPosition(100, 300);
	settingButton->setText("Settings");
	settingButton->setCallback([this]()
	{
		requestStackPush(StateID::Settings);
	});

	auto exitButton = std::make_shared<Button>(*context._fontHolder, *context._textureHolder);
	exitButton->setPosition(100, 350);
	exitButton->setText("Exit");
	exitButton->setCallback([this]()
	{
		requestStackPop();
	});

	_container.pack(playButton);
	_container.pack(settingButton);
	_container.pack(exitButton);
}

void MenuState::draw()
{
	auto& window = *getContext()._window;
	window.setView(window.getDefaultView());

	window.draw(_backgroundSprite);
	window.draw(_container);
}

bool MenuState::update(sf::Time dt)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	_container.handleEvent(event);

	return false;
}
