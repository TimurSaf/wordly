#include <stdexcept>
#include <cctype>
#include "GuessGrid.h"
#include <algorithm>
#include <sstream>
#include "client_http.hpp"

GuessGrid::GuessGrid(const sf::IntRect & bounds, const sf::Font & font, const std::string& solution, const int maxGuesses)
	: WndInterface(bounds), _solution(solution)
{
	if (bounds.size.x <= 0 || bounds.size.y <= 0) {
        throw std::invalid_argument("Bounds must have positive dimensions");
    }
    if (solution.empty()) {
        throw std::invalid_argument("Solution cannot be empty");
    }
    if (maxGuesses <= 0) {
        throw std::invalid_argument("Max guesses must be positive");
    }

	initialiseAllGuesses(font, solution.length(), maxGuesses);
	_solved = false;
	_currentWordIndex = 0;
	_insertPosition = 0;
	_usedKeyCheck = false;
}

void GuessGrid::draw(sf::RenderWindow & renderWindow) const
{
	for (const auto& row : _guessLetters) {
		for (const auto& letter : row) {
			letter.draw(renderWindow);
		}
	}
}

void GuessGrid::handleKeyInput(const sf::Keyboard::Key key)
{
	int keyCode = static_cast<int>(key);
	if (keyCode >= 0 && keyCode <= 25) {
		tryInsertLetter(static_cast<char>(keyCode + 'A'));
	}
	else if (key == sf::Keyboard::Key::Backspace) {
		backSpace();
	}
	else if (key == sf::Keyboard::Key::Enter) {
		checkSolution();
		_usedKeyCheck = true;
	}
}

void GuessGrid::tryInsertLetter(const char letter)
{
	if (!isalpha(letter)) {
        throw std::invalid_argument("Letter must be alphabetic character");
    }

	if (_currentWordIndex == _guessLetters.size() || _solved || _insertPosition == _guessLetters.at(_currentWordIndex).size()) 
		return;
	_guessLetters.at(_currentWordIndex).at(_insertPosition).setLetter(letter);
	++_insertPosition;
}

void GuessGrid::backSpace()
{
	if (_solved || _insertPosition == 0 || _currentWordIndex == _guessLetters.size()) 
		return;
	--_insertPosition;
	_guessLetters.at(_currentWordIndex).at(_insertPosition).setLetter(' ');
}

void GuessGrid::checkSolution()
{
	if (_solved || _insertPosition != _guessLetters.at(_currentWordIndex).size())
		return;
		
	std::string user_word;
	for (int i = 0; i < _solution.length(); i++) {
		char guess = _guessLetters.at(_currentWordIndex).at(i).getLetter();
		user_word.push_back(guess);
	}

	if (request_to_server("check_word", _guessLetters.at(_currentWordIndex).size(),user_word) == "not exist") {
		return;
	}

	int solveCount = 0;
	for (int i = 0; i < _solution.length(); i++) {
		char guess = _guessLetters.at(_currentWordIndex).at(i).getLetter();
		int requiredLetterCount = std::count(_solution.begin(), _solution.end(), guess);
		if (guess == _solution.at(i)) {
			_guessLetters.at(_currentWordIndex).at(i).setSolutionState(PuzzleLetter::SolutionState::CORRECT);
			++solveCount;
		}
		else if (guess != _solution.at(i) && requiredLetterCount != 0) {
			_guessLetters.at(_currentWordIndex).at(i).setSolutionState(PuzzleLetter::SolutionState::WRONG_POS);
		}
		else {
			_guessLetters.at(_currentWordIndex).at(i).setSolutionState(PuzzleLetter::SolutionState::NO_STATE);
		}
	}

	++_currentWordIndex;
	_insertPosition = 0;
	if (solveCount == _solution.length()) {
		_solved = true;
	}
}

bool GuessGrid::isSolved() const
{
	return _solved;
}

bool GuessGrid::hasMoreGuesses() const
{
	return _currentWordIndex < _guessLetters.size();
}

std::vector<std::string> GuessGrid::getAllRules() const
{
	std::vector<std::string> rules;

	for (int i = 0; i < _currentWordIndex; i++) {
		std::stringstream ruleStream;
		for (int j = 0; j < _solution.length(); j++) {
			if (_guessLetters.at(i).at(j).getSolutionState() == PuzzleLetter::SolutionState::CORRECT) {
				ruleStream << "*";
			}
			else if (_guessLetters.at(i).at(j).getSolutionState() == PuzzleLetter::SolutionState::WRONG_POS) {
				ruleStream << "#";
			}
			ruleStream << _guessLetters.at(i).at(j).getLetter();
		}
		rules.emplace_back(ruleStream.str());
	}

	return rules;
}

bool GuessGrid::getKeyCheckReset()
{
	bool result = _usedKeyCheck;
	_usedKeyCheck = false;
	return result;
}

std::string GuessGrid::getSolution() const
{
	return _solution;
}

void GuessGrid::initialiseAllGuesses(const sf::Font & font, const int wordLength, const int maxGuesses)
{
	int elementHeight = 60;
	int elementWidth = 60;

	int leftSide = _bounds.position.x + _bounds.size.x / 2 - ((elementWidth + 10) * wordLength) / 2;
	int posY = _bounds.position.y + 30;
	int posX = leftSide;

	for (int i = 0; i < maxGuesses; i++, posY += elementHeight + 10, posX = leftSide) {
		std::vector<PuzzleLetter> row;

		for (int j = 0; j < wordLength; j++, posX += elementWidth + 10) {
			row.emplace_back(PuzzleLetter(sf::IntRect(sf::Vector2<int>(posX, posY), sf::Vector2<int>(elementHeight, elementWidth)), font));
		}

		_guessLetters.emplace_back(row);
	}
}
