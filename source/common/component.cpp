#include "common/component.h"

namespace GUI
{
	bool Component::isSelected() const
	{
		return _isSelected;
	}

	void Component::select()
	{
		_isSelected = true;
	}

	void Component::deselect()
	{
		_isSelected = false;
	}

	bool Component::isActive() const
	{
		return _isActive;
	}

	void Component::activate()
	{
		_isActive = true;
	}

	void Component::deactivate()
	{
		_isActive = false;
	}

}
