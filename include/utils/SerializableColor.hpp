#ifndef UTILS_SERIALIZABLECOLOR_HPP
#define UTILS_SERIALIZABLECOLOR_HPP

#include <bitsery/bitsery.h>

#include <SFML/Graphics/Color.hpp>

class SerializableColor : public sf::Color {
   private:
    template <typename S>
    friend void serialize(S &s, SerializableColor &o);
    friend class bitsery::Access;

   public:
    SerializableColor() : Color(){};
    SerializableColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255) : Color(red, green, blue, alpha){};

    explicit SerializableColor(uint32_t color) : Color(color){};

    SerializableColor(const Color &c) : Color(c){};
};
#endif