#ifndef ELEMENTS_BUTTON_HPP
#define ELEMENTS_BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <chrono>
#include <functional>

class Button : public sf::Drawable {
   public:
    Button(const sf::Vector2f &location, const sf::String &text, const sf::Font &font, const sf::Vector2f &size = {70, 25},
           const sf::Color &defaultColor = sf::Color::White, const sf::Color &pressedColor = sf::Color(150, 150, 150),
           const sf::Color &fontColor = sf::Color::Black);

    bool checkClick(const sf::Vector2f &mousePos);
    std::function<void(void)> onClick;

    sf::String getText() const;
    void setText(const std::string &words);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void update();

   private:
    sf::Text text;
    sf::Vector2f location, size;

    sf::Color *curCol;
    sf::Color pressedColor, defaultColor;
    sf::Color fontColor;

    const sf::Font *font;
    bool pressed;
    std::chrono::high_resolution_clock::time_point pressedTime;

    void handleClick();
};
#endif