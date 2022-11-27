#include <shapes/Circle.hpp>

void Circle::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::CircleShape sh(this->radius);
    sh.setPosition(this->pos - sf::Vector2f(this->radius, this->radius));
    sh.setFillColor(this->col);
    target.draw(sh);
};
Circle::Circle(const sf::Vector2f &pos, float radius, const sf::Color &col) : col(col), pos(pos), radius(radius){};