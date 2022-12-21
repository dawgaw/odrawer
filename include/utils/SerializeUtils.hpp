#ifndef UTILS_SERIALIZEUTILS_HPP
#define UTILS_SERIALIZEUTILS_HPP

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

namespace bitsery::ext {
template <>
struct PolymorphicBaseClass<BaseShape> : PolymorphicDerivedClasses<Circle, Rectangle, Line, LinesPath> {
};
}  // namespace bitsery::ext

namespace SerializeUtils {

using MyPolymorphicClassesForRegistering = bitsery::ext::PolymorphicClassesList<BaseShape>;

using Buffer = std::vector<uint8_t>;
using Writer = bitsery::OutputBufferAdapter<Buffer>;
using Reader = bitsery::InputBufferAdapter<Buffer>;

using TContext = std::tuple<
    bitsery::ext::PointerLinkingContext,
    bitsery::ext::PolymorphicContext<bitsery::ext::StandardRTTI>>;

using MySerializer = bitsery::Serializer<Writer, TContext>;
using MyDeserializer = bitsery::Deserializer<Reader, TContext>;

Buffer serialize(std::shared_ptr<BaseShape> data);
std::shared_ptr<BaseShape> deserialize(const Buffer& buf);

};  // namespace SerializeUtils

#endif