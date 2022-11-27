#include <cmath>
#include <shapes/Line.hpp>
void Line::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Vertex line[] = {first_pos, second_pos};
    line[0].color = line[1].color = this->col;
    target.draw(line, 2, sf::Lines);
};
Line::Line(const sf::Vector2f &first_pos, const sf::Vector2f &second_pos, const sf::Color &col)
    : col(col), first_pos(first_pos), second_pos(second_pos){};
