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
std::shared_ptr<BaseShape> LinesTool::getDrawable() const {
    if (!lines.empty()) {
        return std::make_shared<LinesPath>(lines);
    }
    return nullptr;
}
void LinesTool::reset() {
    lines.clear();
}
LinesTool::LinesTool(const sf::Color& color) : BaseTool(color){};