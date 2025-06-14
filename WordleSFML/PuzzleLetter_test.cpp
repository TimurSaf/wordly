#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "PuzzleLetter.h"
#include <SFML/Graphics.hpp>

class PuzzleLetterFixture {
public:
    sf::Font font;
    PuzzleLetter letter;
    
    PuzzleLetterFixture() 
        : font(),
          letter(sf::IntRect(sf::Vector2<int>(0, 0), sf::Vector2<int>(50, 50)), font)
    {
        font.openFromFile("arial.ttf");
    }
};

// Тесты для конструктора
TEST_CASE_FIXTURE(PuzzleLetterFixture, "Конструктор с корректными параметрами") {
    CHECK_NOTHROW(PuzzleLetter(sf::IntRect(sf::Vector2<int>(0, 0), sf::Vector2<int>(50, 50)), font));
}

TEST_CASE_FIXTURE(PuzzleLetterFixture, "Конструктор с нулевыми размерами - исключение") {
    CHECK_THROWS_AS(PuzzleLetter(sf::IntRect(sf::Vector2<int>(0, 0), sf::Vector2<int>(0, 50)), font), std::invalid_argument);
    CHECK_THROWS_AS(PuzzleLetter(sf::IntRect(sf::Vector2<int>(0, 0), sf::Vector2<int>(50, 0)), font), std::invalid_argument);
}


// Тесты к PuzzleLetter::setLetter
TEST_CASE_FIXTURE(PuzzleLetterFixture, "Установка корректной буквы") {
    CHECK_NOTHROW(letter.setLetter('A'));
    CHECK(letter.getLetter() == 'A');
}


// Тесты к PuzzleLetter::setSolutionState
TEST_CASE_FIXTURE(PuzzleLetterFixture, "Установка некорректного состояния - исключение") {
    CHECK_THROWS_AS(letter.setSolutionState(static_cast<PuzzleLetter::SolutionState>(3)), std::out_of_range);
}

// Тест к PuzzleLetter::getLetter
TEST_CASE_FIXTURE(PuzzleLetterFixture, "Получение буквы по умолчанию") {
    CHECK(letter.getLetter() == ' ');
}

// Тест к PuzzleLetter::getSolutionState
TEST_CASE_FIXTURE(PuzzleLetterFixture, "Получение состояния по умолчанию") {
    CHECK(letter.getSolutionState() == PuzzleLetter::NO_STATE);
}

// Тесты к PuzzleLetter::draw
TEST_CASE_FIXTURE(PuzzleLetterFixture, "Отрисовка буквы без ошибок") {
    sf::RenderWindow window;
    CHECK_NOTHROW(letter.draw(window));
}

TEST_CASE_FIXTURE(PuzzleLetterFixture, "Отрисовка с установленной буквой") {
    sf::RenderWindow window;
    letter.setLetter('B');
    CHECK_NOTHROW(letter.draw(window));
}