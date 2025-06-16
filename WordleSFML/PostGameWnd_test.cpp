#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "PostGameWnd.h"
#include <SFML/Graphics.hpp>

class PostGameWndFixture {
public:
    sf::Font font;
    PostGameWnd postGameWnd;

    PostGameWndFixture() 
        : font(),
          postGameWnd(sf::IntRect(sf::Vector2<int>(0, 0), sf::Vector2<int>(800, 600)), font, "TEST", true)
    {
        font.openFromFile("arial.ttf");
    }
};

//Тесты для конструктора
TEST_CASE_FIXTURE(PostGameWndFixture, "Создание окна с нулевыми размерами - исключение")
{
    CHECK_THROWS_AS(PostGameWnd(sf::IntRect(sf::Vector2<int>(0, 0), sf::Vector2<int>(0, 600)), font, "TEST", true), std::invalid_argument);
    CHECK_THROWS_AS(PostGameWnd(sf::IntRect(sf::Vector2<int>(0, 0), sf::Vector2<int>(800, 0)), font, "TEST", true), std::invalid_argument);
}


//Тесты для PostGameWnd::getResultState
TEST_CASE_FIXTURE(PostGameWndFixture, "Начальное состояние окна")
{
    CHECK(postGameWnd.getResultState() == WndResultState::NothingState);
}


//Тесты для PostGameWnd::getSelectedActionID
TEST_CASE_FIXTURE(PostGameWndFixture, "Взымание значения ID до выбора кнопки - исключение")
{
    CHECK_THROWS_AS(postGameWnd.getSelectedActionID(), std::logic_error);
}