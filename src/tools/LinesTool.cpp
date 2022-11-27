#include <shapes/LinesPath.hpp>
#include <tools/LinesTool.hpp>

void LinesTool::setPosition(const sf::Vector2f& pos) {
    this->lines.emplace_back(prevPos, pos, this->color);
    prevPos = pos;
}

void LinesTool::onMousePressed(const sf::Vector2f& pos) {
    lines.clear();
    prevPos = pos;
}
sf::Drawable* LinesTool::getDrawable() const {
    if (lines.size())
        return new LinesPath(lines);
    else
        return nullptr;
}
void LinesTool::reset() {
    lines.clear();
}
LinesTool::LinesTool(const sf::Color& color) : BaseTool(color), lines({}), prevPos({}){};