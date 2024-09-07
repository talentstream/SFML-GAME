#pragma once

#include <functional>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "common/component.h"
#include "common/resourceHolder.h"

namespace GUI
{
	class Button final : public Component
	{
	public:
		using ButtonPtr = std::shared_ptr<Button>;
		using Callback = std::function<void()>;

		Button(const FontHolder& fontHolder, const TextureHolder& textureHolder);

		void setCallback(Callback callback);

		void setText(const std::string& text);

		void setToggle(bool flag);

		bool isSelectable() const override;

		void select() override;

		void deselect() override;

		void activate() override;

		void deactivate() override;

		void handleEvent(const sf::Event& event) override;

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		Callback _callback;
		const sf::Texture& _normalTexture;
		const sf::Texture& _selectedTexture;
		const sf::Texture& _pressedTexture;

		sf::Sprite _sprite;
		sf::Text _text;
		bool _isToggle;
	};
}
