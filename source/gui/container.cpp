#include "gui/container.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI
{
	Container::Container() :
		_children{},
		_selectedChild{-1}
	{
	}

	void Container::pack(ComponentPtr component)
	{
		_children.push_back(component);

		if (!hasSelection() && component->isSelectable())
		{
			select(_children.size() - 1);
		}
	}

	bool Container::isSelectable() const
	{
		return false;
	}

	void Container::handleEvent(const sf::Event& event)
	{
		if (hasSelection() && _children[_selectedChild]->isActive())
		{
			_children[_selectedChild]->handleEvent(event);
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
			{
				selectPrevious();
			}
			else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
			{
				selectNext();
			}
			else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
			{
				if (hasSelection())
				{
					_children[_selectedChild]->activate();
				}
			}
		}
	}

	void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		std::ranges::for_each(_children, [&target, &states](const auto& child)
		{
			target.draw(*child, states);
		});
	}

	bool Container::hasSelection() const
	{
		return _selectedChild >= 0;
	}

	void Container::select(std::size_t index)
	{
		if(_children[index]->isSelectable())
		{
			if (hasSelection())
			{
				_children[_selectedChild]->deselect();
			}

			_children[index]->select();
			_selectedChild = index;
		}
	}

	void Container::selectNext()
	{
		if(!hasSelection())
		{
			return;
		}

		int next = _selectedChild;
		do
		{
			next = (next + 1) % _children.size();
		} while (!_children[next]->isSelectable());

		select(next);
	}

	void Container::selectPrevious()
	{
		if(!hasSelection())
		{
			return;
		}

		int prev = _selectedChild;
		do
		{
			prev = (prev + _children.size() - 1) % _children.size();
		} while (!_children[prev]->isSelectable());

		select(prev);
	}
}
