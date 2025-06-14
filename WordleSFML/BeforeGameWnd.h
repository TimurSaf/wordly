#ifndef BEFOREGAMEWND_H
#define BEFOREGAMEWND_H

/**
 * \file
 * \brief Заголовочный файл с классом BeforeGameWnd для выбора длины слова перед началом игры.
 *
 * Данный файл содержит объявление класса BeforeGameWnd, который отвечает за отображение
 * и обработку логики окна выбора длины слова перед запуском основной игровой сессии.
 */

#include "WndInterface.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <stdexcept>

/**
 * \class BeforeGameWnd
 * \brief Окно выбора длины слова перед началом игры.
 *
 * Класс BeforeGameWnd наследуется от WndInterface и реализует интерфейс
 * для отображения окна, в котором пользователь может выбрать длину слова
 * перед стартом игры. Внутри окна рисуется фон, заголовок, а также кнопки,
 * соответствующие разным вариантам длины слова.
 */
class BeforeGameWnd : public WndInterface {
public:
    /**
     * \brief Конструктор.
     * \param bounds Область, в которой рисуется окно (sf::IntRect).
     * \param font   Шрифт, используемый для отображения текста и кнопок (sf::Font).
     */
    BeforeGameWnd(const sf::IntRect& bounds, const sf::Font& font);

    /**
     * \brief Рисует фон, заголовок и кнопки.
     * \param renderWindow Ссылка на объект sf::RenderWindow для отрисовки элементов окна.
     * \return void
     */
    void draw(sf::RenderWindow& renderWindow) const override;

    /**
     * \brief Обновляет логику окна каждый кадр.
     * \param deltaTime Время, прошедшее с предыдущего кадра (в секундах).
     * \return void
     */
    void update(const float deltaTime) override;

    /**
     * \brief Обрабатывает нажатие мыши по одной из кнопок.
     * \param mousePosition Координаты курсора мыши в окне (sf::Vector2i).
     * \param isLeft        Флаг, указывающий, была ли нажата левая кнопка мыши (true) или нет (false).
     * \return void
     */
    void handleMousePress(const sf::Vector2i& mousePosition, bool isLeft) override;

    /**
     * \brief Подсвечивает кнопку при наведении.
     * \param mousePosition Координаты курсора мыши в окне (sf::Vector2i).
     * \return void
     */
    void handleMouseMove(const sf::Vector2i& mousePosition) override;

    /**
     * \brief Возвращает состояние окна.
     * \return WndResultState Текущее состояние окна (NothingState или Restart после нажатия кнопки).
     * \throw std::logic_error Если окно было закрыто до вызова функции.
     */
    WndResultState getResultState() const;

    /**
     * \brief Возвращает ID нажатой кнопки.
     * \details Данный метод следует вызывать только после того, как getResultState() вернуло Restart.
     * \return int ID нажатой кнопки (0, 1 или 2)
     * \throw std::logic_error Если метод вызывается до клика (_selectedActionID == -1).
     */
    int getSelectedActionID() const;

private:
    WndResultState                            _resultState;          /**< Текущее состояние окна. */
    std::unique_ptr<sf::RectangleShape>       _fullScreenBackground; /**< Фон во весь экран. */
    std::unique_ptr<sf::RectangleShape>       _background;           /**< Основной фон окна. */
    std::unique_ptr<sf::Text>                 _titleText;            /**< Текст заголовка окна. */
    std::vector<Button>                       _buttons;              /**< Список кнопок выбора длины слова. */
    int                                       _selectedActionID{ -1 }; /**< ID выбранной кнопки. */
};

#endif // BEFOREGAMEWND_H
