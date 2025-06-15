#ifndef WNDINTERFACE_H
#define WNDINTERFACE_H

/**
 * \file
 * \brief Заголовочный файл с базовым интерфейсом WndInterface для всех оконных интерфейсов.
 *
 * Этот файл содержит объявление класса WndInterface, который определяет общий интерфейс
 * для всех окон (игровых, меню, диалогов) в приложении: методы обновления, отрисовки,
 * обработки ввода и управления состоянием.
 */

#include <SFML/Graphics.hpp>

/**
 * \enum WndResultState
 * \brief Состояния, возвращаемые методом getResultState интерфейсов.
 *
 * Используется для определения результата работы интерфейса:
 * - NothingState — нет изменений,
 * - Finished    — интерфейс завершил свою работу,
 * - Restart     — необходимо перезапустить текущий интерфейс или игру,
 * - Menu        — перейти в меню,
 * - Quit        — выход из приложения.
 */
enum WndResultState {
    NothingState, /**< Нет изменений состояния. */
    Finished,     /**< Интерфейс завершил свою работу. */
    Restart,      /**< Требуется перезапуск интерфейса или игры. */
};

/**
 * \class WndInterface
 * \brief Абстрактный базовый класс для оконных интерфейсов.
 *
 * Определяет общий контракт для всех интерфейсов: обновление логики,
 * отрисовка, обработка ввода мыши и клавиатуры, управление доступностью
 * и получение результата работы интерфейса.
 */
class WndInterface
{
public:
    /**
     * \brief Конструктор.
     *
     * Инициализирует интерфейс заданными границами и делает его включённым.
     *
     * \param bounds Прямоугольная область, в которой будет отображаться интерфейс (sf::IntRect).
     */
    WndInterface(sf::IntRect bounds)
        : _bounds(bounds), _isEnabled(true) {}

    /**
     * \brief Виртуальный деструктор.
     */
    virtual ~WndInterface() = default;

    /**
     * \brief Обновляет состояние интерфейса.
     *
     * Вызывается в каждом кадре игрового цикла для обновления логики.
     *
     * \param deltaTime Время (в секундах), прошедшее с предыдущего кадра.
     * \return void
     */
    virtual void update(const float deltaTime) = 0;

    /**
     * \brief Отрисовывает элементы интерфейса.
     *
     * Вызывается каждый кадр для рендеринга всех графических элементов.
     *
     * \param renderWindow Ссылка на объект sf::RenderWindow для отрисовки.
     * \return void
     */
    virtual void draw(sf::RenderWindow& renderWindow) const = 0;

    /**
     * \brief Обрабатывает нажатие кнопки мыши.
     *
     * По умолчанию не делает ничего, но может быть переопределён.
     *
     * \param mousePosition Координаты курсора мыши во время нажатия (sf::Vector2i).
     * \param isLeft        Флаг: true, если нажата левая кнопка мыши; false — правая.
     * \return void
     */
    virtual void handleMousePress(const sf::Vector2i& mousePosition, bool isLeft) {};

    /**
     * \brief Обрабатывает перемещение мыши.
     *
     * По умолчанию не делает ничего, но может быть переопределён.
     *
     * \param mousePosition Координаты курсора мыши при движении (sf::Vector2i).
     * \return void
     */
    virtual void handleMouseMove(const sf::Vector2i& mousePosition) {};

    /**
     * \brief Обрабатывает нажатие клавиши клавиатуры.
     *
     * По умолчанию не делает ничего, но может быть переопределён.
     *
     * \param key Код нажатой клавиши (sf::Keyboard::Key).
     * \return void
     */
    virtual void handleKeyInput(const sf::Keyboard::Key key) {};

    /**
     * \brief Устанавливает доступность интерфейса.
     *
     * Если интерфейс отключён, его методы update/draw можно пропускать.
     *
     * \param enabled Новое состояние: true — включить интерфейс; false — отключить.
     * \return void
     */
    void setEnabled(bool enabled) { _isEnabled = enabled; };

    /**
     * \brief Проверяет, включён ли интерфейс.
     *
     * \return bool True, если интерфейс включён и доступен; иначе false.
     */
    bool isEnabled() const { return _isEnabled; }

    /**
     * \brief Возвращает результат работы интерфейса.
     *
     * По умолчанию возвращает NothingState. Может быть переопределён
     * для сигнализации о завершении, необходимости перезапуска и т.д.
     *
     * \return WndResultState Текущее состояние интерфейса.
     */
    virtual WndResultState getResultState() const { return WndResultState::NothingState; };

protected:
    sf::IntRect _bounds;   /**< Границы интерфейса для позиционирования и проверки попаданий. */
    bool        _isEnabled;/**< Флаг состояния: true, если интерфейс включён; false — если отключён. */
};

#endif // WNDINTERFACE_H
