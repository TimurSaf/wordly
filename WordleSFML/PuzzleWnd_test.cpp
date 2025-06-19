#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "PuzzleWnd.h"
#include <SFML/Graphics.hpp>
#include <stdexcept>

struct PuzzleWndFixture {
    sf::Font font;
    PuzzleWnd wnd;

    PuzzleWndFixture()
    : font(), 
    wnd(sf::IntRect({0,0},{500,500}), font, "HELLO")
    {
        font.openFromFile("arial.ttf");
    }
};

TEST_CASE_FIXTURE(PuzzleWndFixture, "Ошибка при получении GuessGrid до завершения игры") {
    CHECK(wnd.getResultState() != Finished);
    CHECK_THROWS_AS(wnd.getGuessGrid(), std::logic_error);
}

TEST_CASE_FIXTURE(PuzzleWndFixture, "Получение GuessGrid после завершения игры") {
    for (char c : "HELLO") {
        sf::Keyboard::Key key = static_cast<sf::Keyboard::Key>(
            static_cast<int>(sf::Keyboard::Key::A) + (c - 'A')
        );
        wnd.handleKeyInput(key);
    }
    wnd.handleKeyInput(sf::Keyboard::Key::Enter);
    wnd.update(0.0f);
    CHECK(wnd.getResultState() == Finished);
    CHECK_NOTHROW({
        const GuessGrid& grid = wnd.getGuessGrid();
        CHECK(grid.getSolution() == "HELLO");
    });
}