#include <cmath>
#include <shapes/Circle.hpp>
#include <tools/CircleTool.hpp>

CircleTool::CircleTool(const sf::Color& color) : BaseTool(color){};

void CircleTool::setPosition(const sf::Vector2f& pos) {
    this->last_pos = pos;
}

void CircleTool::onMousePressed(const sf::Vector2f& pos) {
    this->last_pos = this->first_pos = pos;
}
std::shared_ptr<BaseShape> CircleTool::getDrawable() const {
    if (this->last_pos != this->first_pos) {
        const auto distance = this->last_pos - this->first_pos;
        return std::make_shared<Circle>(first_pos, std::sqrt(distance.x * distance.x + distance.y * distance.y), this->color);
    }
    return nullptr;
};
void CircleTool::reset() {
    this->last_pos = this->first_pos = {};
}
