#include "Button.h"
#include <stdexcept>

Button::Button(const sf::IntRect & bounds, const std::string & text, const int actionID, const sf::Font& font)
    : _bounds(bounds), _text(text), _actionID(actionID),
      _background(sf::Vector2f(_bounds.size.x - 2, _bounds.size.y - 2)),
      _textVisual(font, text, 30)
{
    if (bounds.size.x <= 0 || bounds.size.y <= 0) {
        throw std::invalid_argument("Button bounds must have positive dimensions");
    }
    if (text.empty()) {
        throw std::invalid_argument("Button text cannot be empty");
    }
    
    _textVisual.setFillColor(sf::Color::White);
    _textVisual.setStyle(sf::Text::Bold);
    sf::FloatRect textRect = _textVisual.getLocalBounds();
    _textVisual.setOrigin(sf::Vector2f(textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f)); 
    _textVisual.setPosition(sf::Vector2f(_bounds.position.x + _bounds.size.x / 2.0f, _bounds.position.y + _bounds.size.y / 2.0f));

    _background.setPosition(sf::Vector2f(_bounds.position.x + 1, _bounds.position.y + 1));
    _background.setFillColor(sf::Color(5, 5, 5));
    _background.setOutlineThickness(1);
    _background.setOutlineColor(sf::Color::White);

    _colourID = 0;
    _isHovered = false;
}

void Button::draw(sf::RenderWindow & renderWindow) const
{
    renderWindow.draw(_background);
    renderWindow.draw(_textVisual);
}

int Button::getActionID() const
{
    return _actionID;
}

void Button::setHovering(const bool isHovering)
{
    _isHovered = isHovering;
    _background.setOutlineThickness(_isHovered ? 3 : 1);
}

bool Button::isPositionInside(const sf::Vector2i & mousePosition) const
{
    return _bounds.contains(mousePosition);
}

void Button::setBackgroundColour(const sf::Color & colour)
{
    _background.setFillColor(colour);
}

void Button::applyColourID(const int colourID)
{
    if (colourID < 0 || colourID > 3) {
        throw std::out_of_range("colourID must be between 0 and 3");
    }
    
    if (colourID > _colourID) {
        _colourID = colourID;
        switch (_colourID) {
        case 1:
            _background.setFillColor(sf::Color(40, 40, 40));
            break;
        case 2:
            _background.setFillColor(sf::Color(141, 141, 74));
            break;
        case 3:
            _background.setFillColor(sf::Color(93, 141, 74));
            break;
        }
    }
}
