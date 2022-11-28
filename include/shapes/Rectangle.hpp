#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <shapes/BaseShape.hpp>

class Rectangle : public BaseShape {
   private:
    SerializableFloatVector first_pos, last_pos;
    SerializableColor col;
    template <typename S>
    friend void serialize(S &s, Rectangle &o);
    friend class bitsery::Access;

   public:
    Rectangle() = default;
    Rectangle(const SerializableFloatVector &first_pos, const SerializableFloatVector &last_pos, const SerializableColor &color);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
#endif