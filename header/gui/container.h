#pragma once

#include <vector>

#include "common/component.h"

namespace GUI
{
	class Container final : public Component
	{
	public:
		using ContainerPtr = std::shared_ptr<Container>;

		Container();

		void pack(ComponentPtr component);

		bool isSelectable() const override;

		void handleEvent(const sf::Event& event) override;

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		bool hasSelection() const;

		void select(std::size_t index);

		void selectNext();

		void selectPrevious();

	private:
		std::vector<ComponentPtr> _children;
		int _selectedChild;
	};
}
