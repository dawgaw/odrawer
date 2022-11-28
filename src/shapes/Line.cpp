#include <cmath>
#include <shapes/Line.hpp>
void Line::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Vertex line[] = {first_pos, second_pos};
    line[0].color = line[1].color = this->col;
    target.draw(line, 2, sf::Lines);
};
Line::Line(const SerializableFloatVector &first_pos, const SerializableFloatVector &second_pos, const SerializableColor &col)
    : col(col), first_pos(first_pos), second_pos(second_pos){};
