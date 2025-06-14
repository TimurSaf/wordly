#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "Button.h"
#include <SFML/Graphics.hpp>

class ButtonFixture {
public:
    sf::Font font;
    Button button;
    
    ButtonFixture() : 
        font(),
        button(sf::IntRect(sf::Vector2<int>(0, 0), sf::Vector2<int>(100, 50)), "Test", 1, font) 
    {
        font.openFromFile("arial.ttf");
    }
};


//Тесты для конструктора
TEST_CASE_FIXTURE(ButtonFixture, "Создание кнопки с нулевыми размерами - исключение")
{
    CHECK_THROWS_AS(Button(sf::IntRect(sf::Vector2<int>(0, 0), sf::Vector2<int>(0, 50)), "Test", 1, font), std::invalid_argument);
    CHECK_THROWS_AS(Button(sf::IntRect(sf::Vector2<int>(0, 0), sf::Vector2<int>(100, 0)), "Test", 1, font), std::invalid_argument);
}

TEST_CASE_FIXTURE(ButtonFixture, "Создание кнопки с пустым текстом - исключение")
{
    CHECK_THROWS_AS(Button(sf::IntRect(sf::Vector2<int>(0, 0), sf::Vector2<int>(100, 50)), "", 1, font), std::invalid_argument);
}

//Тесты для Buttton::getActionID
TEST_CASE_FIXTURE(ButtonFixture, "Возврат корректного actionID")
{
    CHECK(button.getActionID() == 1);
}

TEST_CASE_FIXTURE(ButtonFixture, "Отсутствие ошибочных значений actionID")
{
    CHECK_FALSE(button.getActionID() == 0);
}




//Тесты для Button::isPositionInside
TEST_CASE_FIXTURE(ButtonFixture, "Определение позиции внутри кнопки")
{
    CHECK(button.isPositionInside(sf::Vector2i(15, 15)) == true);
}

TEST_CASE_FIXTURE(ButtonFixture, "Определение позиции вне кнопки")
{
    CHECK(button.isPositionInside(sf::Vector2i(200, 200)) == false);
}


//Тесты для Button::applyColourID
TEST_CASE_FIXTURE(ButtonFixture, "Корректное применение цветов по ID")
{
    CHECK_NOTHROW(button.applyColourID(1));
    CHECK_NOTHROW(button.applyColourID(2)); 
    CHECK_NOTHROW(button.applyColourID(3));
}

TEST_CASE_FIXTURE(ButtonFixture, "Цвет с недопустимым ID - исключение")
{
    CHECK_THROWS_AS(button.applyColourID(-1), std::out_of_range);
    CHECK_THROWS_AS(button.applyColourID(4), std::out_of_range);
}