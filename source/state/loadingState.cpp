#include "state/loadingState.h"

#include "common/utility.h"


LoadingState::LoadingState(StateStack& stack, Context context) :
	State{stack, context}
{
	auto& window = context._window;
	auto& font = context._fontHolder->get(FontID::Main);
	auto viewSize = window->getView().getSize();

	_loadingText.setFont(font);
	_loadingText.setString("Loading Resource");
	centerOrigin(_loadingText);
	_loadingText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f + 50.f);

	_progressBarBackground.setFillColor(sf::Color::White);
	_progressBarBackground.setSize(sf::Vector2f(viewSize.x - 20.f, 10.f));
	_progressBarBackground.setPosition(10.f, _loadingText.getPosition().y + 40.f);

	_progressBar.setFillColor(sf::Color{100,100,100});
	_progressBar.setSize(sf::Vector2f{ 200,10 });
	_progressBar.setPosition(10.f, _loadingText.getPosition().y + 40.f);

	setCompletion(0.f);

	_loadingTask.execute();
}

void LoadingState::draw()
{
	auto& window = *getContext()._window;

	window.setView(window.getDefaultView());

	window.draw(_loadingText);
	window.draw(_progressBarBackground);
	window.draw(_progressBar);
}

bool LoadingState::update(sf::Time dt)
{
	if(_loadingTask.isFinished())
	{
		requestStackPop();
		requestStackPush(StateID::Game);
	}
	else
	{
		setCompletion(_loadingTask.getCompletion());
	}
	return true;
}

bool LoadingState::handleEvent(const sf::Event& event)
{
	return true;
}

void LoadingState::setCompletion(float percent)
{
	percent = std::clamp(percent, 0.f, 1.f);

	_progressBar.setSize(sf::Vector2f(_progressBarBackground.getSize().x * percent,
	                                  _progressBarBackground.getSize().y));
}
