#include "common/sceneNode.h"

#include <cassert>

SceneNode::SceneNode(Category category) :
	_children{},
	_parent{nullptr},
	_defaultCategory{category}
{
}

void SceneNode::attachChild(NodePtr child)
{
	child->_parent = this;
	_children.emplace_back(std::move(child));
}

SceneNode::NodePtr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::ranges::find_if(_children, [&](NodePtr& p)
	{
		return p.get() == &node;
	});

	assert(found != _children.end());

	NodePtr result = std::move(*found);
	result->_parent = nullptr;
	_children.erase(found);
	return result;
}

void SceneNode::update(sf::Time dt, CommandQueue& commandQueue)
{
	updateCurrent(dt, commandQueue);
	updateChildren(dt, commandQueue);
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f{};
}

sf::Transform SceneNode::getWorldTransform() const
{
	auto transform = sf::Transform::Identity;

	for (auto node = this; node != nullptr; node = node->_parent)
	{
		transform = node->getTransform() * transform;
	}

	return transform;
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
	if (command._category == getCategory())
	{
		command._action(*this, dt);
	}

	for (const auto& child : _children)
	{
		child->onCommand(command, dt);
	}
}

Category SceneNode::getCategory() const
{
	return Category::Scene;
}

sf::FloatRect SceneNode::getBoundingRect() const
{
	return sf::FloatRect{};
}

bool SceneNode::isMarkedForRemoval() const
{
	return isDestroyed();
}

bool SceneNode::isDestroyed() const
{
	return false;
}

void SceneNode::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const
{
	auto rect = getBoundingRect();

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f{rect.left, rect.top});
	shape.setSize(sf::Vector2f{rect.width, rect.height});
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.f);

	target.draw(shape);
}

void SceneNode::updateCurrent(sf::Time dt, CommandQueue& commandQueue)
{
	// do nothing
}

void SceneNode::updateChildren(sf::Time dt, CommandQueue& commandQueue) const
{
	for (const auto& child : _children)
	{
		child->update(dt, commandQueue);
	}
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	// do nothing
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& child : _children)
	{
		child->draw(target, states);
	}
}
