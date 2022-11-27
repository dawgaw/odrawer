#include <shapes/LinesPath.hpp>

void LinesPath::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto &&i : this->lines) {
        target.draw(i);
    }
};
void LinesPath::addLine(const Line &line) {
    this->lines.push_back(line);
}

LinesPath::LinesPath(const std::vector<Line> &lines) : lines(lines){};