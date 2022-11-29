

#include <utils/SerializeUtils.hpp>

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

    s.container(o.lines, 0, [](S& s, Line& item) {
        s.object(item);
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
