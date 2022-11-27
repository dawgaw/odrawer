#include <tools/BaseTool.hpp>
BaseTool::BaseTool(const sf::Color& color) : color(color){};

void BaseTool::setColor(const sf::Color& color) {
    this->color = color;
};