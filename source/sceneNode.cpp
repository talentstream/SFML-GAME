#include "sceneNode.h"

SceneNode::SceneNode()
	: _children{},
	  _parent{nullptr}
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

	static_assert(found != _children.end());

	NodePtr result = std::move(*found);
	result->_parent = nullptr;
	_children.erase(found);
	return result;
}

void SceneNode::update(sf::Time dt)
{
	updateCurrent(dt);
	updateChildren(dt);
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

void SceneNode::updateCurrent(sf::Time dt)
{
}

void SceneNode::updateChildren(sf::Time dt)
{
	for (auto& child : _children)
	{
		child->update(dt);
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
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& child : _children)
	{
		child->draw(target, states);
	}
}
