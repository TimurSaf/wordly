#ifndef GAME_H
#define GAME_H

/**
 * \file
 * \brief Заголовочный файл с классом Game для управления состояниями игры.
 *
 * Данный файл содержит объявление класса Game, который отвечает за 
 * инициализацию игрового контекста, переключение между окнами (интерфейсами), 
 * а также обработку основных событий (обновление, отрисовка, ввод).
 */

#include <random>
#include <memory>
#include "WndInterface.h"
#include "client_http.hpp"

/**
 * \class Game
 * \brief Основной класс, управляющий логикой и интерфейсами игры.
 *
 * Класс Game инициализирует игровые окна (интерфейсы), обрабатывает события 
 * от мыши и клавиатуры, обновляет текущее состояние активного интерфейса 
 * и отслеживает запрос на завершение игры.
 */
class Game
{
public:
    /**
     * \brief Конструктор.
     *
     * Инициализирует игру, создаёт начальный интерфейс (Lobby) и настраивает 
     * генератор случайных чисел.
     *
     * \param gameBounds Прямоугольная область, в которой будет происходить игра (sf::IntRect).
     * \param font       Ссылка на шрифт (sf::Font) для всех текстовых элементов.
     */
    Game(const sf::IntRect& gameBounds, const sf::Font& font);

    /**
     * \brief Деструктор.
     *
     * Освобождает ресурсы, связанные с активными интерфейсами.
     */
    virtual ~Game();

    /**
     * \brief Обновляет текущее состояние активного окна.
     *
     * Вызывается каждый кадр игрового цикла для обновления логики активного интерфейса.
     *
     * \param deltaTime Время (в секундах), прошедшее с предыдущего кадра.
     * \return void
     */
    void update(const float deltaTime);

    /**
     * \brief Рисует текущее активное окно.
     *
     * Вызывается каждый кадр для отрисовки элементов активного интерфейса.
     *
     * \param renderWindow Ссылка на объект sf::RenderWindow для отрисовки.
     * \return void
     */
    void draw(sf::RenderWindow& renderWindow) const;

    /**
     * \brief Обрабатывает нажатие кнопки мыши.
     *
     * Перенаправляет событие клика в активный интерфейс (окно или оверлей).
     *
     * \param mousePosition Координаты курсора мыши в окне (sf::Vector2i).
     * \param isLeft        Флаг, указывающий, была ли нажата левая кнопка мыши (true) или нет (false).
     * \return void
     */
    void handleMousePress(const sf::Vector2i& mousePosition, bool isLeft);

    /**
     * \brief Обрабатывает движение мыши.
     *
     * Перенаправляет событие перемещения курсора в активный интерфейс (окно или оверлей).
     *
     * \param mousePosition Координаты курсора мыши в окне (sf::Vector2i).
     * \return void
     */
    void handleMouseMove(const sf::Vector2i& mousePosition);

    /**
     * \brief Обрабатывает нажатие клавиши клавиатуры.
     *
     * Перенаправляет событие нажатия клавиши в активный интерфейс (окно или оверлей).
     *
     * \param key Код нажатой клавиши (sf::Keyboard::Key).
     * \return void
     */
    void handleKeyInput(const sf::Keyboard::Key key);

    /**
     * \brief Проверяет, был ли запрос на завершение игры.
     *
     * Возвращает true, если активный интерфейс или логика игры поставила флаг 
     * на выход из основного цикла.
     *
     * \return bool True, если игра должна завершиться; false в противном случае.
     */
    bool getGameCloseRequested() const;

private:
    const sf::IntRect            _bounds;          /**< Область игрового поля. */
    const sf::Font&              _font;            /**< Ссылка на шрифт для текста. */
    std::default_random_engine   _randomEngine;    /**< Общий генератор случайных чисел. */
    std::unique_ptr<WndInterface> _activeInterface; /**< Текущий активный интерфейс (окно). */
    std::unique_ptr<WndInterface> _activeOverlay;   /**< Текущий активный оверлей (если есть). */
    bool                         _terminateGame;   /**< Флаг запроса на завершение игры. */
};

#endif // GAME_H
