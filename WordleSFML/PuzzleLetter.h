#ifndef PUZZLELETTER_H
#define PUZZLELETTER_H

/**
 * \file
 * \brief Заголовочный файл с классом PuzzleLetter для отображения одной буквы пазла.
 *
 * Данный файл содержит объявление класса PuzzleLetter, который отвечает за отображение
 * отдельной буквы в игровом поле, хранение её состояния (правильная, неправильная позиция)
 * и обработку визуального представления.
 */

#include <SFML/Graphics.hpp>

/**
 * \class PuzzleLetter
 * \brief Класс, представляющий одну букву в игровом поле пазла.
 *
 * Класс PuzzleLetter позволяет отображать символ в прямоугольной области,
 * задавать его значение, изменять цвет фона в зависимости от состояния решения
 * (CORRECT, WRONG_POS или NO_STATE) и получать текущее состояние буквы.
 */
class PuzzleLetter
{
public:
    /**
     * \brief Перечисление возможных состояний буквы при решении пазла.
     *
     * NO_STATE    - состояние по умолчанию (буква ещё не проверялась),
     * CORRECT     - буква стоит на правильном месте,
     * WRONG_POS   - буква присутствует в слове, но в неправильной позиции.
     */
    enum SolutionState { NO_STATE, CORRECT, WRONG_POS };

    /**
     * \brief Конструктор по умолчанию.
     *
     * Инициализирует букву пустым символом ('\0') в заданных границах и создаёт
     * соответствующие объекты для отображения фона и текста.
     *
     * \param bounds Прямоугольная область, в которой будет отображаться буква (sf::IntRect).
     * \param font   Шрифт для отображения символа (sf::Font).
     * \throw std::invalid_argument Если bounds имеют неположительные размеры.
     */
    PuzzleLetter(const sf::IntRect& bounds, const sf::Font& font);

    /**
     * \brief Деструктор по умолчанию.
     */
    virtual ~PuzzleLetter() = default;

    /**
     * \brief Рисует букву на указанном окне.
     * \param renderWindow Ссылка на объект sf::RenderWindow для отрисовки элементов.
     * \return void
     */
    void draw(sf::RenderWindow& renderWindow) const;

    /**
     * \brief Возвращает текущий символ буквы.
     * \return char Символ, установленный для этой буквы. Если символ не задан, возвращается '\0'.
     */
    char getLetter() const;

    /**
     * \brief Устанавливает символ для отображения.
     * \param letter Символ, который будет отображён (char).
     * \return void
     */
    void setLetter(const char letter);

    /**
     * \brief Устанавливает состояние решения для этой буквы.
     *
     * Изменяет цвет фона в зависимости от переданного состояния:
     * - CORRECT: фон зелёный (буква на своём месте),
     * - WRONG_POS: фон жёлтый (буква есть в слове, но не на этой позиции),
     * - NO_STATE: фон серый (состояние по умолчанию).
     *
     * \param solutionState Состояние решения для буквы (SolutionState).
     * \return void
     * \throw std::out_of_range Если solutionState недопустим.
     */
    void setSolutionState(const SolutionState& solutionState);

    /**
     * \brief Возвращает текущее состояние решения этой буквы.
     * \return SolutionState Текущее состояние (_currentState).
     */
    SolutionState getSolutionState() const;

private:
    sf::IntRect        _bounds;       /**< Область (границы) для проверки попадания курсора и отрисовки. */
    char               _letter;       /**< Текущий символ буквы (если '\0', буква не установлена). */
    sf::RectangleShape _background;   /**< Прямоугольник, рисующий фон буквы. */
    sf::Text           _textVisual;   /**< Объект для отображения символа внутри прямоугольника. */
    SolutionState      _currentState; /**< Текущее состояние решения для этой буквы. */

    /**
     * \brief Устанавливает цвет фона для буквы.
     * \param colour Цвет (sf::Color) для фона прямоугольника.
     * \return void
     */
    void setBackgroundColour(const sf::Color& colour);
};

#endif // PUZZLELETTER_H
