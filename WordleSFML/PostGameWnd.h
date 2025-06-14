#ifndef POSTGAMEWND_H
#define POSTGAMEWND_H

/**
 * \file
 * \brief Заголовочный файл с классом PostGameWnd для отображения экрана после завершения игры.
 *
 * Данный файл содержит объявление класса PostGameWnd, который наследуется от WndInterface
 * и отвечает за отображение информации о результате игры (угадано/не угадано, разрешение)
 * и предоставляет пользователю выбор: начать новую игру или выйти.
 */

#include "WndInterface.h"
#include "Button.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <string>

/**
 * \class PostGameWnd
 * \brief Окно после завершения игры с информацией о результате и кнопками для дальнейших действий.
 *
 * Класс PostGameWnd наследует интерфейс WndInterface и реализует окно,
 * в котором показывается, было ли слово угадано, или нет, выводится решение,
 * а также предлагаются кнопки для начала новой игры или выхода.
 */
class PostGameWnd : public WndInterface
{
public:
    /**
     * \brief Конструктор класса PostGameWnd.
     *
     * Инициализирует фон, тексты и кнопки на основании параметров игры.
     *
     * \param bounds     Область, в которой рисуется окно (sf::IntRect).
     * \param font       Шрифт для отображения текста (sf::Font).
     * \param solution   Строка с разгаданным (или неудачно отгаданным) словом.
     * \param wonGame    Логический флаг: true, если пользователь угадал слово; false в противном случае.
     * \param attempts   Количество попыток, которое потребовалось для угадывания слова.
     * \throw std::invalid_argument Если bounds невалидны или attempts < 0.
     */
    PostGameWnd(const sf::IntRect& bounds,
                const sf::Font& font,
                const std::string& solution,
                const bool wonGame,
                const int attempts);

    /**
     * \brief Деструктор по умолчанию.
     */
    virtual ~PostGameWnd() = default;

    /**
     * \brief Обновление логики окна (не используется в текущей реализации).
     *
     * \param deltaTime Время, прошедшее с предыдущего кадра (в секундах).
     * \return void
     */
    virtual void update(const float deltaTime) override {}

    /**
     * \brief Отрисовывает фоновую затемнённую область, центральный фон, тексты и кнопки.
     *
     * Вызывается каждый кадр для отображения элементов окна.
     *
     * \param renderWindow Ссылка на объект sf::RenderWindow для рендеринга.
     * \return void
     */
    virtual void draw(sf::RenderWindow& renderWindow) const override;

    /**
     * \brief Обрабатывает нажатие кнопки мыши.
     *
     * При клике левой кнопкой мыши проверяет положение курсора, и если оно попадает
     * в область одной из кнопок, сохраняет её идентификатор и меняет состояние окна
     * на Restart для перехода к новому действию.
     *
     * \param mousePosition Координаты курсора мыши во время клика (sf::Vector2i).
     * \param isLeft        Флаг: true, если нажата левая кнопка мыши; false — в противном случае.
     * \return void
     * \throw std::out_of_range Если actionID меньше 0 или больше 2.
     */
    virtual void handleMousePress(const sf::Vector2i& mousePosition, bool isLeft) override;

    /**
     * \brief Обрабатывает перемещение мыши по окну.
     *
     * При движении курсора проверяет, находится ли он над одной из кнопок,
     * и устанавливает эффект наведения (hover) для этой кнопки.
     *
     * \param mousePosition Координаты курсора мыши при перемещении (sf::Vector2i).
     * \return void
     */
    virtual void handleMouseMove(const sf::Vector2i& mousePosition) override;

    /**
     * \brief Возвращает текущее состояние окна.
     *
     * После нажатия на одну из кнопок состояние меняется с NothingState на Restart,
     * что сигнализирует основной логике о необходимости перехода.
     *
     * \return WndResultState Текущее состояние окна (NothingState или Restart).
     */
    WndResultState getResultState() const override;

    /**
     * \brief Возвращает ID выбранной кнопки.
     *
     * Данный метод следует вызывать только после того, как getResultState() вернуло Restart.
     *
     * \return int ID нажатой кнопки (0, 1 или 2) или -1, если ни одна кнопка не была нажата.
     * \throw std::logic_error Если выбор значения ID произошел до выбора кнопки.
     */
    int getSelectedActionID() const;

private:
    WndResultState                             _resultState;           /**< Текущее состояние окна (NothingState или Restart). */
    std::vector<Button>                        _buttons;               /**< Список кнопок для выбора дальнейших действий. */
    std::unique_ptr<sf::RectangleShape>        _fullScreenBackground;  /**< Полупрозрачный фон, затеняющий всё окно. */
    std::unique_ptr<sf::RectangleShape>        _background;            /**< Центральный фон для панели с текстами и кнопками. */
    std::unique_ptr<sf::Text>                  _titleText1;            /**< Первый заголовок (например, «You Won!» или «Game Over»). */
    std::unique_ptr<sf::Text>                  _titleText2;            /**< Второй заголовок с количеством попыток или другим сообщением. */
    std::unique_ptr<sf::Text>                  _solutionText;          /**< Текст, отображающий правильное слово (solution). */
    int                                        _selectedActionID{ -1 }; /**< ID нажатой кнопки (0, 1 или 2), -1 если нет выбора. */
};

#endif // POSTGAMEWND_H
