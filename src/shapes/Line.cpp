#include <cmath>
#include <shapes/Line.hpp>
void Line::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::VertexArray line(sf::Lines, 2);
    line[0].position = first_pos;
    line[1].position = second_pos;
    line[0].color = line[1].color = this->col;
    target.draw(line);
};
Line::Line(const SerializableFloatVector &first_pos, const SerializableFloatVector &second_pos, const SerializableColor &col)
    : col(col), first_pos(first_pos), second_pos(second_pos){};
