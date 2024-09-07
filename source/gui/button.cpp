#include "gui/button.h"

#include "common/utility.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI
{
	Button::Button(const FontHolder& fontHolder, const TextureHolder& textureHolder) :
	_callback{},
	_normalTexture{textureHolder.get(TextureID::ButtonNormal)},
	_selectedTexture{textureHolder.get(TextureID::ButtonSelected)},
	_pressedTexture{textureHolder.get(TextureID::ButtonPressed)},
	_sprite{},
	_text{"",fontHolder.get(FontID::Main), 16},
	_isToggle{false}
	{
		_sprite.setTexture(_normalTexture);

		auto bounds = _sprite.getLocalBounds();
		_text.setPosition(bounds.width / 2.f, bounds.height / 2.f);
	}

	void Button::setCallback(Callback callback)
	{
		_callback = std::move(callback);
	}

	void Button::setText(const std::string& text)
	{
		_text.setString(text);
		centerOrigin(_text);
	}

	void Button::setToggle(bool flag)
	{
		_isToggle = flag;
	}

	bool Button::isSelectable() const
	{
		return true;
	}

	void Button::select()
	{
		Component::select();

		_sprite.setTexture(_selectedTexture);
	}

	void Button::deselect()
	{
		Component::deselect();

		_sprite.setTexture(_normalTexture);
	}

	void Button::activate()
	{
		Component::activate();

		if(_isToggle)
		{
			_sprite.setTexture(_pressedTexture);
		}

		if(_callback)
		{
			_callback();
		}

		if(!_isToggle)
		{
			deactivate();
		}
	}

	void Button::deactivate()
	{
		Component::deactivate();

		if(_isToggle)
		{
			if(isSelected())
			{
				_sprite.setTexture(_selectedTexture);
			}
			else
			{
				_sprite.setTexture(_normalTexture);
			}
		}
	}

	void Button::handleEvent(const sf::Event& event)
	{
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(_sprite, states);
		target.draw(_text, states);
	}
}
