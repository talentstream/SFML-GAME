#pragma once

#include "common/resourceHolder.h"
#include "common/sceneNode.h"

class TextNode final : public SceneNode
{
public:
	explicit TextNode(const FontHolder& fontHolder, const std::string& text);

	void setString(const std::string& text);

private:
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Text _text;
};
