#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "BeforeGameWnd.h"
#include <SFML/Graphics.hpp>
struct BeforeGameWndFixture {
    sf::Font font;
    BeforeGameWnd wnd;

    BeforeGameWndFixture()
        : font(), 
        wnd(sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(600,600)), font)
    {
        font.openFromFile("arial.ttf");
    }
};

TEST_CASE_FIXTURE(BeforeGameWndFixture, "После создания состояние NothingState") {
    CHECK(wnd.getResultState() == NothingState);
}

TEST_CASE_FIXTURE(BeforeGameWndFixture, "Попытка вызвать функцию getResultState() при отключённом окне") {
    wnd.setEnabled(false);
    CHECK_THROWS_AS(wnd.getResultState(), std::logic_error);
}

TEST_CASE_FIXTURE(BeforeGameWndFixture, "Ошибка при получении ID до клика") {
    CHECK_THROWS_AS(wnd.getSelectedActionID(), std::logic_error);
}

TEST_CASE_FIXTURE(BeforeGameWndFixture, "Клик по 1 кнопке - ID=0") {
    sf::Vector2i clickPos(
        600 / 2 - 275 + 10,
        600 * 3 / 4 - 200 + 10
    );
    wnd.handleMousePress(clickPos, true);
    CHECK(wnd.getResultState() == Restart);
    CHECK_NOTHROW({
        int id = wnd.getSelectedActionID();
        CHECK(id == 0);
    });
}

TEST_CASE_FIXTURE(BeforeGameWndFixture, "Клик за кнопкой не меняет состояние") {
    wnd.handleMousePress(sf::Vector2i(5,5), true);
    CHECK(wnd.getResultState() == NothingState);
    CHECK_THROWS_AS(wnd.getSelectedActionID(), std::logic_error);
}