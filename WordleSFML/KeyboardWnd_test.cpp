#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "KeyboardWnd.h"
#include <SFML/Graphics.hpp>
#include <stdexcept>

struct KeyboardWndFixture {
    sf::Font    font;
    KeyboardWnd wnd;

    KeyboardWndFixture()
        : font(), 
        wnd(sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(1000,1000)), font)
    {
        font.openFromFile("arial.ttf");
    }
};

TEST_CASE_FIXTURE(KeyboardWndFixture, "Не передано ID") {
    CHECK_THROWS_AS(wnd.getActionIDReset(), std::logic_error);
}

TEST_CASE_FIXTURE(KeyboardWndFixture, "Верный ID после клика по кнопке Q") {
    sf::Vector2i clickPos((1000 - (10 * 60 + 9 * 10)) / 2 + 30, 1000 * 3 / 4 + 30);
    wnd.handleMousePress(clickPos, true);

    CHECK_NOTHROW({
        int code = wnd.getActionIDReset();
        CHECK(code == static_cast<int>('Q'));
    });
}

TEST_CASE_FIXTURE(KeyboardWndFixture, "Клик вне кнопок не меняет состояние") {
    wnd.handleMousePress({5,5}, true);
    CHECK_THROWS_AS(wnd.getActionIDReset(), std::logic_error);
}
