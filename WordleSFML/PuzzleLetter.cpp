#include "PuzzleLetter.h"
#include <stdexcept>

PuzzleLetter::PuzzleLetter(const sf::IntRect & bounds, const sf::Font & font)
	: _bounds(bounds), _letter(' '),
	_background(sf::Vector2f(_bounds.size.x - 2, _bounds.size.y - 2)),
	_textVisual(font, 'A', 30)
{
	if (bounds.size.x <= 0 || bounds.size.y <= 0) {
        throw std::invalid_argument("Bounds must have positive dimensions");
    }

	_textVisual.setFillColor(sf::Color::White);
	_textVisual.setStyle(sf::Text::Bold);
	_textVisual.setPosition(sf::Vector2f(_bounds.position.x + _bounds.size.x / 2 - _textVisual.getGlobalBounds().size.x / 2, _bounds.position.y + _bounds.size.y / 2 - 20));
	_textVisual.setString(' ');

	_background.setPosition(sf::Vector2f(_bounds.position.x + 1, _bounds.position.y + 1));
	_background.setFillColor(sf::Color(5, 5, 5));
	_background.setOutlineThickness(1);
	_background.setOutlineColor(sf::Color::White);

	_currentState = SolutionState::NO_STATE;
}

void PuzzleLetter::draw(sf::RenderWindow & renderWindow) const
{
	renderWindow.draw(_background);
	renderWindow.draw(_textVisual);
}

char PuzzleLetter::getLetter() const
{
	return _letter;
}

void PuzzleLetter::setLetter(const char letter)
{
	_letter = letter;
	_textVisual.setString(letter);
}

void PuzzleLetter::setSolutionState(const SolutionState & solutionState)
{
	if (solutionState < NO_STATE || solutionState > WRONG_POS) {
        throw std::out_of_range("Invalid SolutionState value");
    }
	
	_currentState = solutionState;
	switch (_currentState) {
	case SolutionState::NO_STATE:
		_background.setFillColor(sf::Color(40, 40, 40));
		break;
	case SolutionState::CORRECT:
		_background.setFillColor(sf::Color(93, 141, 74));
		break;
	case SolutionState::WRONG_POS:
		_background.setFillColor(sf::Color(141, 141, 74));
		break;
	}
}

PuzzleLetter::SolutionState PuzzleLetter::getSolutionState() const
{
	return _currentState;
}

void PuzzleLetter::setBackgroundColour(const sf::Color & colour)
{
	_background.setFillColor(colour);
}
