#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "GuessGrid.h"
#include <SFML/Graphics.hpp>

class GuessGridFixture {
public:
    sf::Font font;
    GuessGridFixture() {
        font.openFromFile("arial.ttf");
    }
};

// Тесты для конструктора
TEST_CASE_FIXTURE(GuessGridFixture, "Конструктор с корректными параметрами")
{
    CHECK_NOTHROW(GuessGrid(sf::IntRect(sf::Vector2<int>(0, 0), sf::Vector2<int>(800, 600)), font, "TEST", 6));
}

TEST_CASE_FIXTURE(GuessGridFixture, "Конструктор с нулевыми размерами - исключение")
{
    CHECK_THROWS_AS(GuessGrid(sf::IntRect(sf::Vector2<int>(0, 0), sf::Vector2<int>(0, 600)), font, "TEST", 6), std::invalid_argument);
}

TEST_CASE_FIXTURE(GuessGridFixture, "Конструктор с пустым решением - исключение")
{
    CHECK_THROWS_AS(GuessGrid(sf::IntRect(sf::Vector2<int>(0, 0), sf::Vector2<int>(800, 600)), font, "", 6), std::invalid_argument);
}


// Тесты для GuessGrid::tryInsertLetter
TEST_CASE_FIXTURE(GuessGridFixture, "Вставка корректной буквы") {
    GuessGrid grid(sf::IntRect(sf::Vector2<int>(0, 0), sf::Vector2<int>(800, 600)), font, "TEST", 6);
    CHECK_NOTHROW(grid.tryInsertLetter('A'));
}


// Тесты для GuessGrid::getAllRules
TEST_CASE_FIXTURE(GuessGridFixture, "Получение правил для пустой сетки") {
    GuessGrid grid(sf::IntRect(sf::Vector2<int>(0, 0), sf::Vector2<int>(800, 600)), font, "TEST", 6);
    auto rules = grid.getAllRules();
    CHECK(rules.empty());
}
