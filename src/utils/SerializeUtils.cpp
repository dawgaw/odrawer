

#include <numeric>
#include <utils/SerializeUtils.hpp>

template <typename S>
void serialize(S& serializer, BaseShape& object) {}

template <typename S>
void serialize(S& serializer, SerializableFloatVector& object) {
    serializer.value4b(object.x);
    serializer.value4b(object.y);
}

template <typename S>
void serialize(S& serializer, SerializableColor& object) {
    serializer.value1b(object.r);
    serializer.value1b(object.g);
    serializer.value1b(object.b);
    serializer.value1b(object.a);
}

template <typename S>
void serialize(S& serializer, Circle& object) {
    serializer.ext(object, bitsery::ext::BaseClass<BaseShape>{});
    serializer.object(object.pos);
    serializer.value4b(object.radius);
    serializer.object(object.col);
}

template <typename S>
void serialize(S& serializer, Line& object) {
    serializer.ext(object, bitsery::ext::BaseClass<BaseShape>{});
    serializer.object(object.first_pos);
    serializer.object(object.second_pos);
    serializer.object(object.col);
}

template <typename S>
void serialize(S& serializer, Rectangle& object) {
    serializer.ext(object, bitsery::ext::BaseClass<BaseShape>{});
    serializer.object(object.first_pos);
    serializer.object(object.last_pos);
    serializer.object(object.col);
}

template <typename S>
void serialize(S& serializer, LinesPath& object) {
    serializer.ext(object, bitsery::ext::BaseClass<BaseShape>{});
    serializer.container(object.lines, std::numeric_limits<u_int32_t>::max(), [](S& serializer, Line& item) {
        serializer.object(item);
    });
}

SerializeUtils::Buffer SerializeUtils::serialize(std::shared_ptr<BaseShape> data) {
    SerializeUtils::Buffer buffer{};
    SerializeUtils::TContext ctx{};
    std::get<1>(ctx).registerBasesList<SerializeUtils::MySerializer>(SerializeUtils::MyPolymorphicClassesForRegistering{});
    SerializeUtils::MySerializer ser{ctx, buffer};
    ser.ext(data, bitsery::ext::StdSmartPtr{});
    ser.adapter().flush();
    return buffer;
}
std::shared_ptr<BaseShape> SerializeUtils::deserialize(const SerializeUtils::Buffer& buf) {
    SerializeUtils::TContext ctx{};
    std::get<1>(ctx).registerBasesList<SerializeUtils::MyDeserializer>(SerializeUtils::MyPolymorphicClassesForRegistering{});
    SerializeUtils::MyDeserializer des{ctx, buf.begin(), buf.size()};
    std::shared_ptr<BaseShape> data;
    des.ext(data, bitsery::ext::StdSmartPtr{});
    std::get<0>(ctx).clearSharedState();
    return data;
}
