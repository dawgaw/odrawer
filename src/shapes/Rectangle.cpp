#include <shapes/Rectangle.hpp>

void Rectangle::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    const auto size = this->last_pos - this->first_pos;
    sf::RectangleShape rect(size);
    rect.setPosition(this->first_pos);
    rect.setFillColor(this->col);
    target.draw(rect);
};
Rectangle::Rectangle(const sf::Vector2f &first_pos, const sf::Vector2f &last_pos, const sf::Color &color) : col(color), first_pos(first_pos), last_pos(last_pos){};