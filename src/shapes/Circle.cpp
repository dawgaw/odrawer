#include <shapes/Circle.hpp>

void Circle::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::CircleShape circle(this->radius);
    circle.setPosition(this->pos - sf::Vector2f(this->radius, this->radius));
    circle.setFillColor(this->col);
    target.draw(circle);
};
Circle::Circle(const SerializableFloatVector &pos, float radius, const SerializableColor &col) : col(col), pos(pos), radius(radius){};
