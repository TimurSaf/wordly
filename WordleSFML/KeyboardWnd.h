#ifndef KEYBOARDWND_H
#define KEYBOARDWND_H

/**
 * \file
 * \brief Заголовочный файл с классом KeyboardWnd для отображения виртуальной клавиатуры.
 *
 * Данный файл содержит объявление класса KeyboardWnd, который наследуется от WndInterface
 * и отвечает за отображение набора кнопок-клавиш, обработку их нажатий и наведения мыши.
 */

#include "WndInterface.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <stdexcept>

/**
 * \class KeyboardWnd
 * \brief Класс виртуальной клавиатуры для ввода символов.
 *
 * Класс KeyboardWnd наследуется от WndInterface и реализует окно с набором кнопок,
 * расположенных по форме клавиатуры внизу экрана. Позволяет обрабатывать клики и наведение
 * мыши по кнопкам, возвращает идентификатор нажатой клавиши и окрашивает кнопки по правилам.
 */
class KeyboardWnd : public WndInterface
{
public:
    /**
     * \brief Конструктор класса KeyboardWnd.
     *
     * Инициализирует все кнопки виртуальной клавиатуры и располагает их
     * по центру внизу в пределах переданных границ.
     *
     * \param bounds Область, в которой рисуется окно клавиатуры (sf::IntRect).
     * \param font   Шрифт для отображения текста на кнопках (sf::Font).
     */
    KeyboardWnd(const sf::IntRect& bounds, const sf::Font& font);

    /**
     * \brief Деструктор по умолчанию.
     */
    virtual ~KeyboardWnd() = default;

    /**
     * \brief Обновление логики виртуальной клавиатуры.
     *
     * В текущей реализации метод не выполняет никаких действий,
     * но требует переопределения от базового класса.
     *
     * \param deltaTime Время, прошедшее с предыдущего кадра (в секундах).
     * \return void
     */
    virtual void update(const float deltaTime) override {}

    /**
     * \brief Отрисовывает все кнопки виртуальной клавиатуры.
     *
     * Проходит по всем элементам _buttons и вызывает у них метод draw.
     *
     * \param renderWindow Ссылка на объект sf::RenderWindow для рендеринга.
     * \return void
     */
    virtual void draw(sf::RenderWindow& renderWindow) const override;

    /**
     * \brief Обрабатывает нажатие мыши по кнопкам клавиатуры.
     *
     * При клике левой кнопкой мыши проверяет, попадает ли курсор
     * в область одной из кнопок. Если да, сохраняет actionID этой кнопки
     * и сбрасывает остальные.
     *
     * \param mousePosition Координаты курсора мыши во время клика (sf::Vector2i).
     * \param isLeft        Логический флаг: true, если нажата левая кнопка мыши.
     * \return void
     */
    virtual void handleMousePress(const sf::Vector2i& mousePosition, bool isLeft) override;

    /**
     * \brief Обрабатывает перемещение мыши по области клавиатуры.
     *
     * При движении курсора определяет, находится ли он над одной из кнопок,
     * и устанавливает соответствующий эффект наведения (hover).
     *
     * \param mousePosition Координаты курсора мыши при перемещении (sf::Vector2i).
     * \return void
     */
    virtual void handleMouseMove(const sf::Vector2i& mousePosition) override;

    /**
     * \brief Возвращает идентификатор нажатой кнопки и сбрасывает его на -1.
     *
     * Позволяет получить actionID последнего нажатия, после чего оно сбрасывается,
     * чтобы не обрабатывалось повторно.
     *
     * \return int Идентификатор действия (actionID).
     */
    int getActionIDReset();

    /**
     * \brief Применяет правила окрашивания для клавиш.
     *
     * По переданному вектору строк-правил изменяет цвет фона каждой кнопки
     * в соответствии с заданными правилами (например, для игры-головоломки).
     *
     * \param rules Вектор строковых правил, определяющих цветовые состояния клавиш.
     * \return void
     */
    void applyRules(const std::vector<std::string>& rules);

private:
    /**
     * \brief Список кнопок, представляющих клавиши виртуальной клавиатуры.
     */
    std::vector<Button> _buttons;

    /**
     * \brief Текущий идентификатор действия (actionID) последней нажати клавиши.
     */
    int _actionID{ -1 };

    /**
     * \brief Инициализирует все кнопки виртуальной клавиатуры с учётом шрифта.
     *
     * Создаёт объекты Button с правильным текстом («A», «B», «C» и т.д.) и позиционирует их
     * по строкам и столбцам в нижней части окна.
     *
     * \param font Шрифт для отображения текста на кнопках (sf::Font).
     * \return void
     */
    void initialiseButtons(const sf::Font& font);
};

#endif // KEYBOARDWND_H
