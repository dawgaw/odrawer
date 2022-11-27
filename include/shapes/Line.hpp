#include <SFML/Graphics.hpp>

#ifndef LINE_HPP
#define LINE_HPP
class Line : public sf::Drawable {
   private:
    sf::Vector2f first_pos, second_pos;
    sf::Color col;

   public:
    Line(const sf::Vector2f &first_pos, const sf::Vector2f &second_pos, const sf::Color &col);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
#endif