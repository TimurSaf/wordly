#include "Game.h"
#include <chrono>       // std::chrono::system_clock
#include "PuzzleWnd.h"
#include "PostGameWnd.h"
#include "BeforeGameWnd.h"


Game::Game(const sf::IntRect & gameBounds, const sf::Font & font)
	: _bounds(gameBounds), _font(font)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	_randomEngine = std::default_random_engine(seed);
	_terminateGame = false;
    _activeInterface = std::make_unique<BeforeGameWnd>(_bounds, _font);
    _activeOverlay   = nullptr;
}

Game::~Game() = default;  // unique_ptr всё удалит автоматически

void Game::update(const float deltaTime) {
    if (_activeOverlay) {
        _activeOverlay->update(deltaTime);
        if (_activeOverlay->getResultState() == WndResultState::Restart) {
            int wordLength = 6; // значение по умолчанию
            if (auto* postGame = dynamic_cast<PostGameWnd*>(_activeOverlay.get())) {
                wordLength = 4 + postGame->getSelectedActionID();
            }
            _activeOverlay.reset();
            _activeInterface = std::make_unique<PuzzleWnd>(_bounds, _font, 
                request_to_server(static_cast<std::string>("get_word"), wordLength, static_cast<std::string>("")));
        }
        else if (_activeOverlay->getResultState() == WndResultState::Quit) {
            _terminateGame = true;
        }
    }
    else if (_activeInterface) {
        if (auto* before = dynamic_cast<BeforeGameWnd*>(_activeInterface.get());
            before && before->getResultState() == WndResultState::Restart)
        {
            int btnID = before->getSelectedActionID();
            int wordLength = 4 + btnID;
            // Получаем слово нужной длины
            std::string mode = "get_word";
            std::string word = request_to_server(mode, wordLength, mode);
            _activeInterface = std::make_unique<PuzzleWnd>(_bounds, _font, word);
            return;
        }
        _activeInterface->update(deltaTime);
        if (_activeInterface->getResultState() == WndResultState::Finished && !_activeOverlay) {
            auto guessGrid = dynamic_cast<PuzzleWnd*>(_activeInterface.get())->getGuessGrid();
            auto rules = guessGrid.getAllRules();
            std::string solution = guessGrid.getSolution();
            _activeOverlay = std::make_unique<PostGameWnd>(_bounds, _font, solution, guessGrid.isSolved(), rules.size());
        }
    }
}

void Game::draw(sf::RenderWindow & renderWindow) const
{
	if (_activeInterface) {
		_activeInterface->draw(renderWindow);
	}

	if (_activeOverlay) {
		_activeOverlay->draw(renderWindow);
	}
}

void Game::handleMousePress(const sf::Vector2i & mousePosition, bool isLeft)
{
	if (_activeOverlay) {
		_activeOverlay->handleMousePress(mousePosition, isLeft);
	}
	else if (_activeInterface) {
		_activeInterface->handleMousePress(mousePosition, isLeft);
	}
}

void Game::handleMouseMove(const sf::Vector2i & mousePosition)
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

bool Game::getGameCloseRequested() const
{
	return _terminateGame;
}
