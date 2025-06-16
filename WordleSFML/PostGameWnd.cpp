#include "PostGameWnd.h"
#include <stdexcept>

PostGameWnd::PostGameWnd(const sf::IntRect & bounds, const sf::Font & font, const std::string & solution, const bool wonGame)
	: WndInterface(bounds)
{
	if (bounds.size.x <= 0 || bounds.size.y <= 0) {
        throw std::invalid_argument("Window bounds must have positive dimensions");
    }
	
	_resultState = WndResultState::NothingState;

	_fullScreenBackground = std::make_unique<sf::RectangleShape>(sf::Vector2f(bounds.size.x, bounds.size.y));
	_fullScreenBackground->setFillColor(sf::Color(20, 20, 20, 150));

	_background = std::make_unique<sf::RectangleShape>(sf::Vector2f(bounds.size.x / 2, bounds.size.y / 2));
	_background->setFillColor(sf::Color(60, 60, 60, 230));
	_background->setOutlineColor(sf::Color::White);
	_background->setOutlineThickness(1);
	_background->setPosition(sf::Vector2f(bounds.position.x + bounds.size.x / 4 + 1, bounds.position.y + bounds.size.y / 4 + 1));

	_titleText1 = std::make_unique<sf::Text>(font, sf::String("Choose the number of letters in a word"), static_cast<unsigned int>(30));
	_titleText1->setPosition(sf::Vector2f(bounds.position.x + bounds.size.x / 2 - _titleText1->getGlobalBounds().size.x / 2, bounds.position.y + bounds.size.y / 4 + 100));
	_titleText1->setFillColor(sf::Color(148, 214, 199));

	_titleText2 = std::make_unique<sf::Text>(font, wonGame ? sf::String("You solved it!") : sf::String("Better Luck Next Time!"), static_cast<unsigned int>(40));
	_titleText2->setPosition(sf::Vector2f(bounds.position.x + bounds.size.x / 2 - _titleText2->getGlobalBounds().size.x / 2, bounds.position.y + bounds.size.y / 4 + 10));
	_titleText2->setFillColor(wonGame ? sf::Color(93, 141, 74) : sf::Color(230, 93, 74));

	_solutionText = std::make_unique<sf::Text>(font, sf::String("Solution: ") + solution, static_cast<unsigned int>(30));
	_solutionText->setPosition(sf::Vector2f(bounds.position.x + bounds.size.x / 2 - _solutionText->getGlobalBounds().size.x / 2, bounds.position.y + bounds.size.y / 4 + 10 + 50));

	_buttons.emplace_back(Button(sf::IntRect(sf::Vector2<int>(bounds.position.x + bounds.size.x / 2 - 275, bounds.position.y + bounds.size.y * 3 / 4 - 200), sf::Vector2<int>(150, 150)), "4", 0, font));
	_buttons.emplace_back(Button(sf::IntRect(sf::Vector2<int>(bounds.position.x + bounds.size.x / 2 - 75, bounds.position.y + bounds.size.y * 3 / 4 - 200), sf::Vector2<int>(150, 150)), "5", 1, font));
	_buttons.emplace_back(Button(sf::IntRect(sf::Vector2<int>(bounds.position.x + bounds.size.x / 2 + 125, bounds.position.y + bounds.size.y * 3 / 4 - 200), sf::Vector2<int>(150, 150)), "6", 2, font));
	for (auto& button : _buttons) {
    	button.setBackgroundColour(sf::Color::Black);
	}
}

void PostGameWnd::draw(sf::RenderWindow & renderWindow) const
{
	renderWindow.draw(*_fullScreenBackground);
	renderWindow.draw(*_background);
	renderWindow.draw(*_titleText1);
	renderWindow.draw(*_titleText2);
	renderWindow.draw(*_solutionText);
	for (const auto& button : _buttons) {
		button.draw(renderWindow);
	}
}

void PostGameWnd::handleMousePress(const sf::Vector2i& mousePosition, bool isLeft)
{
    if (!isLeft) return;

    for (auto &btn : _buttons) {
        if (btn.isPositionInside(mousePosition)) {
            if (btn.getActionID() < 0 || btn.getActionID() > 2) {
                throw std::out_of_range("Invalid button action ID");
            }
            _selectedActionID = btn.getActionID();
            _resultState = WndResultState::Restart;
            break;
        }
    }
}

void PostGameWnd::handleMouseMove(const sf::Vector2i & mousePosition)
{
	for (auto& button : _buttons) {
		button.setHovering(button.isPositionInside(mousePosition));
	}
}

WndResultState PostGameWnd::getResultState() const
{
	return _resultState;
}	

int PostGameWnd::getSelectedActionID() const
{
    if (_resultState != WndResultState::Restart) {
        throw std::logic_error("Action ID is not available in current state");
    }
    return _selectedActionID;
}