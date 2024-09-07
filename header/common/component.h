#pragma once

#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>

namespace GUI
{
	class Component :
		public sf::Drawable,
		public sf::Transformable,
		sf::NonCopyable
	{
	public:
		using ComponentPtr = std::shared_ptr<Component>;

		Component() = default;

		~Component() override = default;

		virtual bool isSelectable() const = 0;

		bool isSelected() const;

		virtual void select();

		virtual void deselect();

		virtual bool isActive() const;

		virtual void activate();

		virtual void deactivate();

		virtual void handleEvent(const sf::Event& event) = 0;

	private:
		bool _isSelected{false};
		bool _isActive{false};
	};
}
