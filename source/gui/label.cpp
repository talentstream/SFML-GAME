#include "gui/label.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI
{
	Label::Label(const std::string& text, const FontHolder& fontHolder) :
		_text{text, fontHolder.get(FontID::Main), 16}
	{
	}

	bool Label::isSelectable() const
	{
		return false;
	}

	void Label::handleEvent(const sf::Event& event)
	{
	}

	void Label::setText(const std::string& text)
	{
		_text.setString(text);
	}

	void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(_text, states);
	}
}
