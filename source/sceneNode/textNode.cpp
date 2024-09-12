#include "sceneNode/textNode.h"

#include "common/utility.h"


TextNode::TextNode(const FontHolder& fontHolder, const std::string& text)
{
	_text.setFont(fontHolder.get(FontID::Main));
	_text.setCharacterSize(20);
	setString(text);
}

void TextNode::setString(const std::string& text)
{
	_text.setString(text);
	centerOrigin(_text);
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_text, states);
}
