#include "BeforeGameWnd.h"

BeforeGameWnd::BeforeGameWnd(const sf::IntRect& bounds, const sf::Font& font)
	: WndInterface(bounds)
{
	_resultState = WndResultState::NothingState;

	_fullScreenBackground = std::make_unique<sf::RectangleShape>(sf::Vector2f(bounds.size.x, bounds.size.y));
	_fullScreenBackground->setFillColor(sf::Color(20, 20, 20, 150));

	_background = std::make_unique<sf::RectangleShape>(sf::Vector2f(bounds.size.x / 2, bounds.size.y / 2));
	_background->setFillColor(sf::Color(60, 60, 60, 230));
	_background->setOutlineColor(sf::Color::White);
	_background->setOutlineThickness(1);
	_background->setPosition(sf::Vector2f(bounds.position.x + bounds.size.x / 4 + 1, bounds.position.y + bounds.size.y / 4 + 1));

	_titleText = std::make_unique<sf::Text>(font, sf::String("Choose the number of letters in a word"), static_cast<unsigned int>(30));
	_titleText->setPosition(
		sf::Vector2f(
			bounds.position.x + bounds.size.x / 2 - _titleText->getGlobalBounds().size.x / 2, bounds.position.y + bounds.size.y / 4 + 60));
	_titleText->setFillColor(sf::Color(148, 214, 199));

	_buttons.push_back(
		Button(
			sf::IntRect(
				sf::Vector2i(
					bounds.position.x + bounds.size.x / 2 - 275, 
					bounds.position.y + bounds.size.y * 3 / 4 - 200
				), 
				sf::Vector2i(150, 150)
			),
			"4", 0, font
		)
	);
	_buttons.push_back(
		Button(
			sf::IntRect(
				sf::Vector2i(
					bounds.position.x + bounds.size.x / 2 - 75,
					bounds.position.y + bounds.size.y * 3 / 4 - 200
				),
				sf::Vector2i(150, 150)
			),
			"5", 1, font
		)
	);
	_buttons.push_back(
		Button(
			sf::IntRect(
				sf::Vector2i(
					bounds.position.x + bounds.size.x / 2 + 125, 
					bounds.position.y + bounds.size.y * 3 / 4 - 200
				),
				sf::Vector2i(150, 150)
			), 
			"6", 2, font
		)
	);
	for (auto& button : _buttons) {
    	button.setBackgroundColour(sf::Color::Black);
	}
}

void BeforeGameWnd::draw(sf::RenderWindow& renderWindow) const
{
	renderWindow.draw(*_fullScreenBackground);
	renderWindow.draw(*_background);
	renderWindow.draw(*_titleText);
	for (const auto& button : _buttons) {
		button.draw(renderWindow);
	}
}

void BeforeGameWnd::update(const float deltaTime) {}

void BeforeGameWnd::handleMousePress(const sf::Vector2i& mousePosition, bool isLeft) {
    if (!isLeft) return;

    for (const auto &button : _buttons) {
        if (button.isPositionInside(mousePosition)) {
            _selectedActionID = button.getActionID();
            _resultState = WndResultState::Restart;
            break;
        }
    }
}

int BeforeGameWnd::getSelectedActionID() const {
	if (_selectedActionID < 0) {
        throw std::logic_error("No action selected yet");
    }
    return _selectedActionID;
}


void BeforeGameWnd::handleMouseMove(const sf::Vector2i& mousePosition)
{
	for (auto& button : _buttons) {
		button.setHovering(button.isPositionInside(mousePosition));
	}
}

WndResultState BeforeGameWnd::getResultState() const
{
	if (!isEnabled()) {
        throw std::logic_error("Cannot query state: window is disabled");
    }
    return _resultState;
}