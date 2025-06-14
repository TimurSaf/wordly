#ifndef GUESSGRID_H
#define GUESSGRID_H

/**
 * \file
 * \brief Заголовочный файл с классом GuessGrid для отображения и проверки сетки догадок.
 *
 * Данный файл содержит объявление класса GuessGrid, который наследует WndInterface 
 * и реализует логику отображения сетки буквенных догадок, обработки ввода с клавиатуры 
 * и проверки решения.
 */

#include "WndInterface.h"
#include "PuzzleLetter.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

/**
 * \class GuessGrid
 * \brief Класс для управления сеткой догадок в игровой механике.
 *
 * GuessGrid создаёт сетку из PuzzleLetter, отображает её, обрабатывает 
 * ввод с аппаратной клавиатуры (буквы, удаление, Enter), проверяет догаданные слова 
 * и формирует результаты (цветовые правила) для виртуальной клавиатуры.
 */
class GuessGrid : public WndInterface
{
public:
    /**
     * \brief Конструктор.
     *
     * Инициализирует пустую сетку догадок заданных размеров и устанавливает слово-решение.
     *
     * \param bounds     Область, в которой рисуется сетка (sf::IntRect).
     * \param font       Шрифт для отображения букв (sf::Font).
     * \param solution   Строка-слово, которое игрок должен угадать (std::string).
     * \param maxGuesses Максимальное количество попыток (int).
     * 
     * \throw std::invalid_argument Если bounds невалидны, solution пусто или maxGuesses <= 0.
     */
    GuessGrid(const sf::IntRect& bounds, const sf::Font& font, const std::string& solution, const int maxGuesses);

    /**
     * \brief Деструктор.
     *
     * Удаляет динамические ресурсы (если они есть). По умолчанию — пустая реализация.
     */
    virtual ~GuessGrid() = default;

    /**
     * \brief Обновление логики сетки (не используется).
     *
     * В текущей реализации метод не выполняет никаких действий,
     * но требуется переопределить его от базового класса.
     *
     * \param deltaTime Время (в секундах), прошедшее с предыдущего кадра.
     * \return void
     */
    virtual void update(const float deltaTime) override {}

    /**
     * \brief Рисует сетку догадок на экране.
     *
     * Вызывает метод draw для каждого PuzzleLetter в сетке.
     *
     * \param renderWindow Ссылка на объект sf::RenderWindow для отрисовки.
     * \return void
     */
    virtual void draw(sf::RenderWindow& renderWindow) const override;

    /**
     * \brief Обрабатывает ввод с аппаратной клавиатуры.
     *
     * При получении буквы вызывает tryInsertLetter, If Backspace — backSpace, 
     * если Enter — checkSolution.
     *
     * \param key Код нажатой клавиши (sf::Keyboard::Key).
     * \return void
     */
    virtual void handleKeyInput(const sf::Keyboard::Key key) override;

    /**
     * \brief Пытается вставить указанную букву в текущую попытку.
     *
     * Если в текущей строке есть свободное место, буква добавляется.
     *
     * \param letter Символ, который нужно вставить (char).
     * \return void
     * \throw std::invalid_argument Если символ не является буквой.
     */
    void tryInsertLetter(const char letter);

    /**
     * \brief Удаляет последнюю букву в текущей попытке (Backspace).
     *
     * Если текущая попытка не пуста, удаляет один символ.
     *
     * \return void
     */
    void backSpace();

    /**
     * \brief Проверяет текущее слово-слово на совпадение с решением.
     *
     * Сравнивает введённое слово с _solution и обновляет состояние каждого PuzzleLetter.
     * Если слово угадано, _solved устанавливается в true.
     *
     * \return void
     */
    void checkSolution();

    /**
     * \brief Проверяет, было ли решение найдено.
     *
     * \return bool True, если слово угадано (_solved == true); иначе false.
     */
    bool isSolved() const;

    /**
     * \brief Проверяет, остались ли ещё попытки.
     *
     * \return bool True, если число попыток меньше maxGuesses; иначе false.
     */
    bool hasMoreGuesses() const;

    /**
     * \brief Формирует все правила (цвета) на основе предыдущих догадок.
     *
     * Возвращает вектор строк-правил, которые затем применяются к виртуальной клавиатуре.
     *
     * \return std::vector<std::string> Вектор правил (каждая строка соответствует символу).
     */
    std::vector<std::string> getAllRules() const;

    /**
     * \brief Возвращает и сбрасывает флаг изменения проверки клавиши (Enter).
     *
     * Возвращает true, если только что было нажато Enter (сработала проверка).
     * После вызова флаг _usedKeyCheck сбрасывается в false.
     *
     * \return bool True, если проверка была выполнена; иначе false.
     */
    bool getKeyCheckReset();

    /**
     * \brief Возвращает текущее слово-решение.
     *
     * \return std::string Строка с решением (_solution).
     */
    std::string getSolution() const;

    /**
     * \brief Возвращает строку для расшаривания результата (Share String).
     *
     * Формирует строку, представляющую текущее состояние пазла (с цветами).
     *
     * \return std::string Строка, отображающая завершённое состояние игры для публикаций.
     */
    std::string getShareString() const;

private:
    std::vector<std::vector<PuzzleLetter>> _guessLetters; /**< Сетка букв (PuzzleLetter). */
    int                                   _insertPosition; /**< Позиция для вставки следующей буквы. */
    int                                   _currentWordIndex; /**< Индекс текущего слова (номер строки). */
    bool                                  _solved; /**< True, если решение уже найдено. */
    bool                                  _usedKeyCheck; /**< Флаг, указывающий, была ли проверка (Enter). */
    const std::string                     _solution; /**< Строка-решение, с которой сравниваются догадки. */

    /**
     * \brief Инициализирует всю сетку догадок пустыми элементами.
     *
     * Создаёт _guessLetters размером wordLength × maxGuesses,
     * устанавливает каждый элемент PuzzleLetter с указанным шрифтом.
     *
     * \param font       Ссылка на шрифт (sf::Font) для отображения букв.
     * \param wordLength Длина слова (int).
     * \param maxGuesses Максимальное число попыток (int).
     * \return void
     */
    void initialiseAllGuesses(const sf::Font& font, const int wordLength, const int maxGuesses);
};

#endif // GUESSGRID_H
