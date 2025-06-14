#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "SFMLGame.h"
#include <filesystem>

// Тесты для конструктора
TEST_CASE("Конструктор с корректными параметрами")
{
    std::filesystem::path tempFont = std::filesystem::temp_directory_path() / "test_font.ttf";
    std::ofstream(tempFont.string()).close();

    #undef FONT_FILE_PATH
    #define FONT_FILE_PATH tempFont.string().c_str()
    
    CHECK_NOTHROW(SFMLGame game);

    std::filesystem::remove(tempFont);
}


// Тесты для SFMLGame::loadFont
TEST_CASE("Загрузка шрифта (успешное чтение существующего файла)")
{
    std::filesystem::path tempFont = std::filesystem::temp_directory_path() / "test_font.ttf";
    std::ofstream(tempFont.string()).close();
    
    #undef FONT_FILE_PATH
    #define FONT_FILE_PATH tempFont.string().c_str()
    
    CHECK_NOTHROW(SFMLGame::loadFont());

    std::filesystem::remove(tempFont);
}


// Тест для SFMLGame::gameLoop
TEST_CASE("Основной игровой цикл без ошибок")
{
    SFMLGame game;
    CHECK_NOTHROW(game.gameLoop());
}