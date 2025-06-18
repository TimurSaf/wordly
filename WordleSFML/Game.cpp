#include "Game.h"
#include "PuzzleWnd.h"
#include "PostGameWnd.h"
#include "BeforeGameWnd.h"


Game::Game(const sf::IntRect& gameBounds, const sf::Font& font)
	: _bounds(gameBounds), _font(font)
{
    _activeInterface = std::make_unique<BeforeGameWnd>(_bounds, _font);
    _activeOverlay   = nullptr;
}

Game::~Game() = default;

void Game::update(const float deltaTime) {
    if (_activeOverlay) {
        _activeOverlay->update(deltaTime);
        if (_activeOverlay->getResultState() == WndResultState::Restart) {
            int wordLength = 6;
            if (PostGameWnd* postGame = dynamic_cast<PostGameWnd*>(_activeOverlay.get())) {
                wordLength = 4 + postGame->getSelectedActionID();
            }
            _activeOverlay.reset();
            _activeInterface = std::make_unique<PuzzleWnd>(_bounds, _font, 
                request_to_server(static_cast<std::string>("get_word"), wordLength, static_cast<std::string>("")));
        }

    }
    else if (_activeInterface) {
        if (BeforeGameWnd* before = dynamic_cast<BeforeGameWnd*>(_activeInterface.get());
            before && before->getResultState() == WndResultState::Restart)
        {
            int btnID = before->getSelectedActionID();
            int wordLength = 4 + btnID;

            std::string mode = "get_word";
            std::string word = request_to_server(mode, wordLength, mode);
            _activeInterface = std::make_unique<PuzzleWnd>(_bounds, _font, word);
            return;
        }
        _activeInterface->update(deltaTime);
        if (_activeInterface->getResultState() == WndResultState::Finished && !_activeOverlay) {
            GuessGrid guessGrid = dynamic_cast<PuzzleWnd*>(_activeInterface.get())->getGuessGrid();
            std::string solution = guessGrid.getSolution();
            _activeOverlay = std::make_unique<PostGameWnd>(_bounds, _font, solution, guessGrid.isSolved());
        }
    }
}

void Game::draw(sf::RenderWindow& renderWindow) const
{
	if (_activeInterface) {
		_activeInterface->draw(renderWindow);
	}

	if (_activeOverlay) {
		_activeOverlay->draw(renderWindow);
	}
}

void Game::handleMousePress(const sf::Vector2i& mousePosition, bool isLeft)
{
	if (_activeOverlay) {
		_activeOverlay->handleMousePress(mousePosition, isLeft);
	}
	else if (_activeInterface) {
		_activeInterface->handleMousePress(mousePosition, isLeft);
	}
}

void Game::handleMouseMove(const sf::Vector2i& mousePosition)
{
	if (_activeOverlay) {
		_activeOverlay->handleMouseMove(mousePosition);
	}
	else if (_activeInterface) {
		_activeInterface->handleMouseMove(mousePosition);
	}
}

void Game::handleKeyInput(const sf::Keyboard::Key key)
{
	if (_activeOverlay) {
		_activeOverlay->handleKeyInput(key);
	}
	else if (_activeInterface) {
		_activeInterface->handleKeyInput(key);
	}
}