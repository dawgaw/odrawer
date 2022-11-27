#include <shapes/Rectangle.hpp>
#include <tools/RectangleTool.hpp>

RectangleTool::RectangleTool(const sf::Color& color) : BaseTool(color), first_pos({}), last_pos({}){};

void RectangleTool::setPosition(const sf::Vector2f& pos) {
    this->last_pos = pos;
}

void RectangleTool::onMousePressed(const sf::Vector2f& pos) {
    this->last_pos = this->first_pos = pos;
}
sf::Drawable* RectangleTool::getDrawable() const {
    if (this->last_pos != this->first_pos)
        return new Rectangle(first_pos, last_pos, this->color);
    else
        return nullptr;
};
void RectangleTool::reset() {
    this->last_pos = this->first_pos = {};
}