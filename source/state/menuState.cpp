#include "state/menuState.h"

#include "common/utility.h"

MenuState::MenuState(StateStack& stack, Context context) :
State{stack, context},
_options{},
_optionIndex{0}
{
	auto& texture = context._textureHolder->get(TextureID::TitleScreen);
	auto& font = context._fontHolder->get(FontID::Main);

	_backgroundSprite.setTexture(texture);

	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Play");
	centerOrigin(playOption);

	playOption.setPosition(context._window->getView().getSize() / 2.f);
	_options.emplace_back(playOption);

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Exit");
	centerOrigin(exitOption);
	exitOption.setPosition(playOption.getPosition() + sf::Vector2f{ 0.f,30.f });
	_options.emplace_back(exitOption);

	updateOptionText();
}

void MenuState::draw()
{
	auto& window = *getContext()._window;
	window.setView(window.getDefaultView());
	window.draw(_backgroundSprite);

	for (const auto& option : _options)
	{
		window.draw(option);
	}
		
}

bool MenuState::update(sf::Time dt)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
	{
		return false;
	}

	if(event.key.code == sf::Keyboard::Return)
	{
		if(_optionIndex == std::to_underlying(Option::Play))
		{
			requestStackPop();
			requestStackPush(StateID::Game);
		}
		else if(_optionIndex == std::to_underlying(Option::Exit))
		{
			requestStackPop();
		}
	}
	else if(event.key.code == sf::Keyboard::Up)
	{
		_optionIndex = _optionIndex > 0 ? _optionIndex - 1 : _options.size() - 1;
		updateOptionText();
	}
	else if(event.key.code == sf::Keyboard::Down)
	{
		_optionIndex = _optionIndex < _options.size() - 1 ? _optionIndex + 1 : 0;
		updateOptionText();
	}

	return true;
}

void MenuState::updateOptionText()
{
	if(_options.empty())
	{
		return;
	}

	for(auto& option : _options)
	{
		option.setFillColor(sf::Color::White);
	}

	_options[_optionIndex].setFillColor(sf::Color::Red);
}
