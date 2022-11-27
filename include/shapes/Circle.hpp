#include <SFML/Graphics.hpp>
#ifndef CIRCLE_HPP
#define CIRCLE_HPP
class Circle : public sf::Drawable {
   private:
    sf::Vector2f pos;
    float radius;
    sf::Color col;

   public:
    Circle(const sf::Vector2f &pos, float radius, const sf::Color &col);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
#endif
