#ifndef SHAPES_BASESHAPE_HPP
#define SHAPES_BASESHAPE_HPP

#include <bitsery/bitsery.h>

#include <SFML/Graphics.hpp>
#include <utils/SerializableColor.hpp>
#include <utils/SerializableFloatVector.hpp>

class BaseShape : public sf::Drawable {
   private:
    template <typename S>
    friend void serialize(S &s, BaseShape &o);
    friend class bitsery::Access;
};
#endif