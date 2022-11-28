#include <network/Server.hpp>
#include <utils/SerializationConfig.hpp>

Server::~Server() {
    this->listener.close();
}

void Server::start() {
    this->listener.listen(8080, sf::IpAddress("127.0.0.1"));
    this->thrd = std::thread([this] {
        do {
            std::unique_ptr<sf::TcpSocket> socket = std::make_unique<sf::TcpSocket>();
            if (this->listener.accept(*socket) == sf::Socket::Status::Done) {
                socket->setBlocking(false);
                this->sockets.push_back(std::move(socket));
            } else {
                assert("this->listener.accept(socket)");
            }
        } while (true);
    });
    this->thrd.detach();
}

void Server::send(std::shared_ptr<BaseShape> data) {
    Buffer buffer{};
    size_t writtenSize{};
    TContext ctx{};
    std::get<1>(ctx).registerBasesList<MySerializer>(MyPolymorphicClassesForRegistering{});
    // create writer and serialize
    MySerializer ser{ctx, buffer};

    ser.ext(data, bitsery::ext::StdSmartPtr{});
    ser.adapter().flush();
    writtenSize = ser.adapter().writtenBytesCount();
    assert(std::get<0>(ctx).isValid());
    sf::Packet p;
    p.append(buffer.data(), writtenSize);
    for (auto&& i : sockets) {
        i->send(p);
    }
}

std::vector<std::shared_ptr<BaseShape>> Server::getData() {
    std::vector<std::shared_ptr<BaseShape>> d;
    size_t writtenSize{};
    TContext ctx{};
    std::get<1>(ctx).registerBasesList<MyDeserializer>(MyPolymorphicClassesForRegistering{});
    // create writer and serialize

    for (auto&& i : sockets) {
        std::unique_ptr<BaseShape> data;
        sf::Packet p;
        if (i->receive(p) == sf::Socket::Status::Done) {
            Buffer buffer((uint8_t*)p.getData(), (uint8_t*)p.getData() + p.getDataSize());

            MyDeserializer des{ctx, buffer.begin(), buffer.size()};
            des.ext(data, bitsery::ext::StdSmartPtr{});

            assert(des.adapter().error() == bitsery::ReaderError::NoError && des.adapter().isCompletedSuccessfully());
            assert(std::get<0>(ctx).isValid());
            std::get<0>(ctx).clearSharedState();

            d.push_back(std::move(data));
        }
    }
    return d;
}