#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <shapes/BaseShape.hpp>

class Circle : public BaseShape {
   private:
    SerializableFloatVector pos;
    float radius;
    SerializableColor col;
    template <typename S>
    friend void serialize(S &s, Circle &o);
    friend class bitsery::Access;

   public:
    Circle() = default;

    Circle(const SerializableFloatVector &pos, float radius, const SerializableColor &col);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
#endif
