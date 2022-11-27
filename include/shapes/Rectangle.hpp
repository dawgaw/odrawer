#include <SFML/Graphics.hpp>

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
class Rectangle : public sf::Drawable {
   private:
    sf::Vector2f first_pos, last_pos;
    sf::Color col;

   public:
    Rectangle(const sf::Vector2f &first_pos, const sf::Vector2f &last_pos, const sf::Color &color);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
#endif