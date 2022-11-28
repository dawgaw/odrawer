
#include <network/Client.hpp>
#include <utils/SerializationConfig.hpp>

void Client::start() {
    ;
    this->socket.connect("127.0.0.1", 8020);
    this->socket.setBlocking(false);
}

void Client::send(std::shared_ptr<BaseShape> data) {
    Buffer buffer{};
    size_t writtenSize{};
    TContext ctx{};
    std::get<1>(ctx).registerBasesList<MySerializer>(MyPolymorphicClassesForRegistering{});

    MySerializer ser{ctx, buffer};

    ser.ext(data, bitsery::ext::StdSmartPtr{});
    ser.adapter().flush();
    writtenSize = ser.adapter().writtenBytesCount();
    assert(std::get<0>(ctx).isValid());

    socket.send(buffer.data(), writtenSize);
}

std::vector<std::shared_ptr<BaseShape>> Client::getData() {
    std::vector<std::shared_ptr<BaseShape>> d;
    size_t writtenSize{};
    TContext ctx{};
    std::get<1>(ctx).registerBasesList<MyDeserializer>(MyPolymorphicClassesForRegistering{});
    std::shared_ptr<BaseShape> data;
    sf::Packet p;
    if (socket.receive(p) == sf::Socket::Status::Done) {
        Buffer buffer((uint8_t*)p.getData(), (uint8_t*)p.getData() + p.getDataSize());
        MyDeserializer des{ctx, buffer.begin(), buffer.size()};

        des.ext(data, bitsery::ext::StdSmartPtr{});

        assert(des.adapter().error() == bitsery::ReaderError::NoError && des.adapter().isCompletedSuccessfully());
        assert(std::get<0>(ctx).isValid());
        std::get<0>(ctx).clearSharedState();
        d.push_back(data);
    }
    return d;
}