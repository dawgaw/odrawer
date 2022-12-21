#ifndef SHAPES_LINE_HPP
#define SHAPES_LINE_HPP

#include <shapes/BaseShape.hpp>

class Line : public BaseShape {
   private:
    SerializableFloatVector first_pos, second_pos;
    SerializableColor col;
    friend class bitsery::Access;
    template <typename S>
    friend void serialize(S &s, Line &o);

   public:
    Line() = default;

    Line(const SerializableFloatVector &first_pos, const SerializableFloatVector &second_pos, const SerializableColor &col);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
#endif