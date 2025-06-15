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
TEST_CASE_FIXTURE(GuessGridFixture, "Вставка корректной буквы")
{
    GuessGrid grid(sf::IntRect(sf::Vector2<int>(0, 0), sf::Vector2<int>(800, 600)), font, "TEST", 6);
    CHECK_NOTHROW(grid.tryInsertLetter('A'));
}


// Тесты для GuessGrid::getAllRules
TEST_CASE_FIXTURE(GuessGridFixture, "Получение правил для пустой сетки")
{
    GuessGrid grid(sf::IntRect(sf::Vector2<int>(0, 0), sf::Vector2<int>(800, 600)), font, "TEST", 6);
    auto rules = grid.getAllRules();
    CHECK(rules.empty());
}

TEST_CASE_FIXTURE(GuessGridFixture, "Правильное решение")
{
    GuessGrid grid(sf::IntRect(sf::Vector2<int>(0, 0), sf::Vector2<int>(800, 600)), font, "APPLE", 6);

    grid.tryInsertLetter('A');
    grid.tryInsertLetter('P');
    grid.tryInsertLetter('P');
    grid.tryInsertLetter('L');
    grid.tryInsertLetter('E');

    grid.checkSolution();

    CHECK(grid.isSolved() == true);
            
    auto rules = grid.getAllRules();
    REQUIRE(rules.size() == 1);
    CHECK(rules[0] == "*A*P*P*L*E");
}
    

TEST_CASE_FIXTURE(GuessGridFixture, "Частично правильное решение")
{
    GuessGrid grid(sf::IntRect(sf::Vector2<int>(0, 0), sf::Vector2<int>(800, 600)), font, "APPLE", 6);

    grid.tryInsertLetter('A');
    grid.tryInsertLetter('P');
    grid.tryInsertLetter('R');
    grid.tryInsertLetter('I');
    grid.tryInsertLetter('L');

    grid.checkSolution();

    CHECK(grid.isSolved() == false);
        
    auto rules = grid.getAllRules();
    REQUIRE(rules.size() == 1);
    CHECK(rules[0] == "*A*PRI#L");
}

TEST_CASE_FIXTURE(GuessGridFixture, "Неправильное решение")
{
    GuessGrid grid(sf::IntRect(sf::Vector2<int>(0, 0), sf::Vector2<int>(800, 600)), font, "APPLE", 6);

    grid.tryInsertLetter('B');
    grid.tryInsertLetter('O');
    grid.tryInsertLetter('C');
    grid.tryInsertLetter('C');
    grid.tryInsertLetter('I');

    grid.checkSolution();

    CHECK(grid.isSolved() == false);
    CHECK(grid.hasMoreGuesses() == true);
        
    auto rules = grid.getAllRules();
    REQUIRE(rules.size() == 1); 
    CHECK(rules[0] == "BOCCI");
}