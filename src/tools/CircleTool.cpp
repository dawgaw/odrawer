#include <cmath>
#include <shapes/Circle.hpp>
#include <tools/CircleTool.hpp>

CircleTool::CircleTool(const sf::Color& color) : BaseTool(color), first_pos({}), last_pos({}){};

void CircleTool::setPosition(const sf::Vector2f& pos) {
    this->last_pos = pos;
}

void CircleTool::onMousePressed(const sf::Vector2f& pos) {
    this->last_pos = this->first_pos = pos;
}
sf::Drawable* CircleTool::getDrawable() const {
    if (this->last_pos != this->first_pos) {
        const auto d = this->last_pos - this->first_pos;
        return new Circle(first_pos, std::sqrt(d.x * d.x + d.y * d.y), this->color);
    } else
        return nullptr;
};
void CircleTool::reset() {
    this->last_pos = this->first_pos = {};
}
