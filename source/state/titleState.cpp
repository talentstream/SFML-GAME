#include "state/titleState.h"

#include "common/utility.h"

TitleState::TitleState(StateStack& stack, Context context) :
	State{stack, context},
	_text{},
	_showText{},
	_textEffectTime{sf::Time::Zero}
{
	_backgroundSprite.setTexture(context._textureHolder->get(TextureID::TitleScreen));

	_text.setFont(context._fontHolder->get(FontID::Main));
	_text.setString("Press any key to start");
	centerOrigin(_text);
	_text.setPosition(context._window->getView().getSize() / 2.f);
}

void TitleState::draw()
{
	auto& window = *getContext()._window;
	window.draw(_backgroundSprite);

	if(_showText)
	{
		window.draw(_text);
	}
}

bool TitleState::update(sf::Time dt)
{
	_textEffectTime += dt;

	if(_textEffectTime >= sf::seconds(0.5f))
	{
		_showText = !_showText;
		_textEffectTime = sf::Time::Zero;
	}

	return true;
}

bool TitleState::handleEvent(const sf::Event& event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		requestStackPop();
		requestStackPush(StateID::Menu);
	} 

	return true;
}
