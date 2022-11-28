#ifndef SERIALIZABLE_FLOAT_VECTOR_HPP
#define SERIALIZABLE_FLOAT_VECTOR_HPP

#include <bitsery/bitsery.h>

#include <SFML/System/Vector2.hpp>

class SerializableFloatVector : public sf::Vector2<float> {
   private:
    template <typename S>
    friend void serialize(S &s, SerializableFloatVector &o);
    friend class bitsery::Access;

   public:
    SerializableFloatVector() : Vector2<float>(){};

    SerializableFloatVector(float X, float Y) : Vector2<float>(x, y){};
    template <typename U>
    explicit SerializableFloatVector(const Vector2<U> &vector) : Vector2<float>(vector){};
    SerializableFloatVector(const Vector2<float> &vector) : Vector2<float>(vector){};
};
#endif