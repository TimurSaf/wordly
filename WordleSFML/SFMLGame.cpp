#include <stdexcept>
#include "SFMLGame.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window.hpp>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define FONT_FILE_PATH "../Fonts/arial.ttf"

SFMLGame::SFMLGame()
	: _window(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), "Wordle", sf::Style::Titlebar | sf::Style::Close),
	_font(loadFont()), _game(sf::IntRect(sf::Vector2<int>(0, 0), sf::Vector2<int>(WINDOW_WIDTH, WINDOW_HEIGHT)), _font)
{
    try {
        _font = loadFont();
    } catch (const std::runtime_error& e) {
        throw std::runtime_error("Failed to initialize SFMLGame: " + std::string(e.what()));
    }

    if (WINDOW_WIDTH <= 0 || WINDOW_HEIGHT <= 0) {
        throw std::invalid_argument("Window dimensions must be positive");
    }

    // _window.create(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), "Wordle", sf::Style::Titlebar | sf::Style::Close);
    
    // if (!_window.isOpen()) {
    //     throw std::runtime_error("Failed to create SFML window");
    // }

    // try {
    //     _game = Game(sf::IntRect(sf::Vector2<int>(0, 0),sf::Vector2<int> (WINDOW_WIDTH, WINDOW_HEIGHT)), _font);
    // } catch (const std::exception& e) {
    //     _window.close();
    //     throw std::runtime_error("Failed to initialize Game: " + std::string(e.what()));
    // }
}

void SFMLGame::gameLoop()
{
    sf::Clock clock;
    while (_window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();

        while (const std::optional<sf::Event> event = _window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                _window.close();
            }
            else if (const auto* mouseButton = event->getIf<sf::Event::MouseButtonPressed>())
            {
                _game.handleMousePress(
                    mouseButton->position,
                    mouseButton->button == sf::Mouse::Button::Left
                );
            }
            else if (const auto* mouseMove = event->getIf<sf::Event::MouseMoved>())
            {
                _game.handleMouseMove(mouseMove->position);
            }
            else if (const auto* key = event->getIf<sf::Event::KeyPressed>())
            {
                _game.handleKeyInput(key->code);
            }
        }

        _game.update(deltaTime);

        _window.clear(sf::Color::Black);
        _game.draw(_window);
        _window.display();

        if (_game.getGameCloseRequested())
        {
            _window.close();
        }
    }
}


sf::Font SFMLGame::loadFont()
{
    
	sf::Font font;
    if (!font.openFromFile(FONT_FILE_PATH))
	{
		throw std::runtime_error("Font file not found");
	}
	return font;
}