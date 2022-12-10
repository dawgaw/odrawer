
#include <network/Client.hpp>
#include <utils/SerializeUtils.hpp>

void Client::start(const std::string& ip, int port) {
    this->socket.connect(ip, port);
    this->socket.setBlocking(false);
}

void Client::send(const std::shared_ptr<BaseShape>& data) {
    SerializeUtils::Buffer buffer(SerializeUtils::serialize(data));
    sf::Packet p;
    p.append(buffer.data(), buffer.size());
    socket.send(p);
}

std::vector<std::shared_ptr<BaseShape>> Client::getData() {
    std::vector<std::shared_ptr<BaseShape>> d;
    sf::Packet p;
    if (socket.receive(p) == sf::Socket::Status::Done) {
        d.push_back(SerializeUtils::deserialize(SerializeUtils::Buffer((uint8_t*)p.getData(), (uint8_t*)p.getData() + p.getDataSize())));
    }
    return d;
}