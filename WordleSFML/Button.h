#ifndef BUTTON_H
#define BUTTON_H

/**
 * \file
 * \brief Заголовочный файл с классом Button для создания и отображения интерактивных кнопок.
 *
 * Данный файл содержит объявление класса Button, который отвечает за отображение
 * прямоугольной кнопки с текстом, обработку её состояния наведения мыши и нажатия.
 */

#include <SFML/Graphics.hpp>

/**
 * \class Button
 * \brief Класс, реализующий интерактивную кнопку с текстом.
 *
 * Класс Button предоставляет функциональность для создания графической кнопки
 * с возможностью отображения, изменения цвета при наведении и клике. Каждая кнопка
 * имеет уникальный actionID, который позволяет различать действия при её нажатии.
 */
class Button
{
public:
    /**
     * \brief Конструктор.
     * 
     * \param bounds   Область (прямоугольник), в которой будет находиться кнопка (sf::IntRect).
     * \param text     Текст, отображаемый на кнопке (std::string).
     * \param actionID Целочисленный идентификатор, используемый для определения действия при клике.
     * \param font     Ссылка на шрифт (sf::Font), используемый для рендеринга текста на кнопке.
     * \throw std::invalid_argument Если bounds имеют неположительные размеры или текст пуст.
     */
    Button(const sf::IntRect& bounds, const std::string& text, const int actionID, const sf::Font& font);

    /**
     * \brief Деструктор по умолчанию.
     */
    virtual ~Button() = default;

    /**
     * \brief Отрисовывает кнопку на указанном окне.
     * \param renderWindow Ссылка на объект sf::RenderWindow, в котором происходит рендеринг.
     * \return void
     */
    void draw(sf::RenderWindow& renderWindow) const;

    /**
     * \brief Возвращает идентификатор действия кнопки.
     * \return int Текущий actionID кнопки.
     */
    int getActionID() const;

    /**
     * \brief Обновляет состояние "hover" (наведение мыши).
     * \param isHovering Логическое значение: true, если курсор находится над кнопкой; false в противном случае.
     * \return void
     */
    void setHovering(const bool isHovering);

    /**
     * \brief Проверяет, находится ли указанная позиция внутри границ кнопки.
     * \param mousePosition Координаты курсора мыши в окне (sf::Vector2i).
     * \return bool Возвращает true, если точка находится внутри границ кнопки, иначе false.
     */
    bool isPositionInside(const sf::Vector2i& mousePosition) const;

    /**
     * \brief Устанавливает цвет фона кнопки.
     * \param colour Цвет (sf::Color), задаваемый для фона кнопки.
     * \return void
     */
    void setBackgroundColour(const sf::Color& colour);

    /**
     * \brief Применяет предустановленный цвет по идентификатору.
     * \param colourID Идентификатор цвета, определяющий новый фон, если он выше текущего.
     * \return void
     * \throw std::out_of_range Если colourID имеет значение меньше 0 или больше 3.
     */
    void applyColourID(const int colourID);

private:
    sf::IntRect           _bounds;     /**< Область (границы) кнопки. */
    int                   _actionID;   /**< Идентификатор действия при клике. */
    bool                  _isHovered;  /**< Флаг состояния "hover": курсор над кнопкой или нет. */
    std::string           _text;       /**< Текст, отображаемый на кнопке. */
    sf::RectangleShape    _background; /**< Прямоугольник, рисующий фон кнопки. */
    sf::Text              _textVisual; /**< Объект для отображения текста кнопки. */
    int                   _colourID;   /**< Текущий идентификатор цвета, используемый для фона. */
};

#endif // BUTTON_H
