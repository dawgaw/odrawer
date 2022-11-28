#ifndef SERIALIZATION_CONFIG_HPP
#define SERIALIZATION_CONFIG_HPP

#include <bitsery/adapter/buffer.h>
#include <bitsery/bitsery.h>
#include <bitsery/ext/inheritance.h>
#include <bitsery/ext/pointer.h>
#include <bitsery/ext/std_smart_ptr.h>
#include <bitsery/traits/vector.h>

#include <memory>
#include <shapes/Circle.hpp>
#include <shapes/Line.hpp>
#include <shapes/LinesPath.hpp>
#include <shapes/Rectangle.hpp>

template <typename S>
void serialize(S& s, BaseShape& o) {}

template <typename S>
void serialize(S& s, SerializableFloatVector& o) {
    s.value4b(o.x);
    s.value4b(o.y);
}

template <typename S>
void serialize(S& s, SerializableColor& o) {
    s.value1b(o.r);
    s.value1b(o.g);
    s.value1b(o.b);
    s.value1b(o.a);
}

template <typename S>
void serialize(S& s, Circle& o) {
    s.ext(o, bitsery::ext::BaseClass<BaseShape>{});
    s.object(o.pos);
    s.value4b(o.radius);
    s.object(o.col);
}

template <typename S>
void serialize(S& s, Line& o) {
    s.ext(o, bitsery::ext::BaseClass<BaseShape>{});
    s.object(o.first_pos);
    s.object(o.second_pos);
    s.object(o.col);
}

template <typename S>
void serialize(S& s, Rectangle& o) {
    s.ext(o, bitsery::ext::BaseClass<BaseShape>{});
    s.object(o.first_pos);
    s.object(o.last_pos);
    s.object(o.col);
}

template <typename S>
void serialize(S& s, LinesPath& o) {
    s.ext(o, bitsery::ext::BaseClass<BaseShape>{});

    s.container(o.lines, 100, [](S& s, Line& item) {
        s.object(item);
    });
}

namespace bitsery::ext {
template <>
struct PolymorphicBaseClass<BaseShape> : PolymorphicDerivedClasses<Circle, Rectangle, Line, LinesPath> {
};
}  // namespace bitsery::ext

using MyPolymorphicClassesForRegistering = bitsery::ext::PolymorphicClassesList<BaseShape>;

using Buffer = std::vector<uint8_t>;
using Writer = bitsery::OutputBufferAdapter<Buffer>;
using Reader = bitsery::InputBufferAdapter<Buffer>;

// we need to define few things in order to work with polymorphism
// 1) we need pointer linking context to work with pointers
// 2) we need polymorphic context to be able to work with polymorphic types
using TContext = std::tuple<
    bitsery::ext::PointerLinkingContext,
    bitsery::ext::PolymorphicContext<bitsery::ext::StandardRTTI>>;
// NOTE:
//  RTTI can be customizable, if you can't use dynamic_cast and typeid, and have 'custom' solution
using MySerializer = bitsery::Serializer<Writer, TContext>;
using MyDeserializer = bitsery::Deserializer<Reader, TContext>;

#endif