#pragma once

#include "common/command.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

class CommandQueue;

class SceneNode
	: public sf::Transformable,
	  public sf::Drawable,
	  sf::NonCopyable
{
public:
	using NodePtr = std::unique_ptr<SceneNode>;

	explicit SceneNode(Category category = Category::None);

	void attachChild(NodePtr child);

	NodePtr detachChild(const SceneNode& node);

	void update(sf::Time dt, CommandQueue& commandQueue);

	sf::Vector2f getWorldPosition() const;

	sf::Transform getWorldTransform() const;

	void onCommand(const Command& command, sf::Time dt);

	virtual Category getCategory() const;

	virtual sf::FloatRect getBoundingRect() const;

	virtual bool isMarkedForRemoval() const;

	virtual bool isDestroyed() const;

	static float distance(const SceneNode& lhs, const SceneNode& rhs);

private:
	virtual void updateCurrent(sf::Time dt, CommandQueue& commandQueue);

	void updateChildren(sf::Time dt, CommandQueue& commandQueue) const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

	void drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<NodePtr> _children;
	SceneNode* _parent;
	Category _defaultCategory;
};
