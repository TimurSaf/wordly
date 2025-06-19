#ifndef PUZZLEWND_H
#define PUZZLEWND_H

/**
 * \file
 * \brief Заголовочный файл с классом PuzzleWnd для отображения игрового окна пазла.
 *
 * Данный файл содержит объявление класса PuzzleWnd, который наследуется от WndInterface
 * и обеспечивает логику и отображение основного игрового процесса: сетки догадок,
 * виртуальной клавиатуры и обработку ввода пользователя (мышь и клавиатура).
 */

#include "WndInterface.h"
#include "KeyboardWnd.h"
#include "GuessGrid.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <stdexcept>
/**
 * \class PuzzleWnd
 * \brief Класс игрового окна пазла.
 *
 * PuzzleWnd отвечает за инициализацию нового пазла, отображение заголовка,
 * сетки догадок (GuessGrid), виртуальной клавиатуры (KeyboardWnd) и обработку
 * всех пользовательских событий (нажатия клавиш и мыши).  
 * Окно переходит в состояние Restart, когда игра завершена и нужно вернуться
 * к экрану выбора или началу новой игры.
 */
class PuzzleWnd : public WndInterface
{
public:
    /**
     * \brief Конструктор класса PuzzleWnd.
     *
     * Инициализирует элементы игрового окна: заголовок, сетку догадок и клавиатуру,
     * устанавливает начальное состояние окна.
     *
     * \param bounds   Прямоугольная область, в которой будет отрисовываться окно (sf::IntRect).
     * \param font     Ссылка на шрифт (sf::Font), используемый для всех текстовых элементов.
     * \param solution Строка-слово, которое игрок должен угадать.
     */
    PuzzleWnd(const sf::IntRect& bounds,
              const sf::Font& font,
              const std::string& solution);

    /**
     * \brief Деструктор класса PuzzleWnd.
     */
    ~PuzzleWnd();

    /**
     * \brief Обновляет внутреннюю логику окна каждую итерацию игрового цикла.
     *
     * Вызывается из основного цикла отрисовки; внутри может обновляться анимация,
     * проверяться состояние игрового процесса и т. д.
     *
     * \param deltaTime Время (в секундах), прошедшее с предыдущего кадра.
     * \return void
     */
    void update(const float deltaTime) override;

    /**
     * \brief Отрисовывает все компоненты игрового окна.
     *
     * Рисует заголовок, сетку догадок (GuessGrid) и виртуальную клавиатуру (KeyboardWnd)
     * на заданном объекте sf::RenderWindow.
     *
     * \param renderWindow Ссылка на объект sf::RenderWindow для отрисовки элементов.
     * \return void
     */
    void draw(sf::RenderWindow& renderWindow) const override;

    /**
     * \brief Обрабатывает нажатие мыши внутри окна.
     *
     * Проверяет, попадает ли позиция курсора в область виртуальной клавиатуры и передаёт
     * событие соответствующим кнопкам. При необходимости обновляет состояние игры.
     *
     * \param mousePosition Координаты курсора мыши во время нажатия (sf::Vector2i).
     * \param isLeft        Логический флаг: true, если нажата левая кнопка мыши.
     * \return void
     */
    void handleMousePress(const sf::Vector2i& mousePosition, bool isLeft) override;

    /**
     * \brief Обрабатывает перемещение мыши внутри окна.
     *
     * Передаёт координаты курсора в виртуальную клавиатуру, чтобы подсвечивать кнопки
     * при наведении.
     *
     * \param mousePosition Координаты курсора мыши при движении (sf::Vector2i).
     * \return void
     */
    void handleMouseMove(const sf::Vector2i& mousePosition) override;

    /**
     * \brief Обрабатывает ввод с аппаратной клавиатуры.
     *
     * Если игрок нажал на клавишу (букву или Enter), соответствующее событие будет
     * передано в GuessGrid или использовано для проверки слова.
     *
     * \param keyCode Код нажатой клавиши (sf::Keyboard::Key).
     * \return void
     */
    void handleKeyInput(const sf::Keyboard::Key keyCode) override;

    /**
     * \brief Возвращает ссылку на объект GuessGrid.
     *
     * С помощью этого метода можно получить доступ к сетке догадок для чтения состояний
     * или выполнения дополнительных проверок извне.
     * \throw std::logic_error если игра ещё не завершена (getResultState() != Finished).
     * \return const GuessGrid& Ссылка на текущий объект GuessGrid.
     */
    const GuessGrid& getGuessGrid() const;

    /**
     * \brief Возвращает текущее состояние окна.
     *
     * Если игра завершена (игрок угадал слово или попытки кончились), метод возвращает Restart,
     * иначе — NothingState.
     *
     * \return WndResultState Текущее состояние окна (NothingState или Restart).
     */
    WndResultState getResultState() const override;

private:
    /**
     * \brief Шрифт, используемый для всех текстовых элементов окна.
     */
    const sf::Font& _font;

    /**
     * \brief Текст заголовка игры (например, "Word Puzzle").
     */
    sf::Text _gameTitle;

    /**
     * \brief Объект виртуальной клавиатуры для ввода букв кликом мыши.
     */
    KeyboardWnd _keyboard;

    /**
     * \brief Сетка догадок, в которую отображаются предыдущие попытки пользователя.
     */
    GuessGrid _guessGrid;

    /**
     * \brief Текущее состояние окна (NothingState или Restart).
     */
    WndResultState _currentState;
};

#endif // PUZZLEWND_H
