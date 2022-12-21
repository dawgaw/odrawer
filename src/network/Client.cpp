
#include <network/Client.hpp>
#include <utils/SerializeUtils.hpp>

void Client::start(const std::string& ipAddress, int port) {
    this->socket.connect(ipAddress, port);
    this->socket.setBlocking(false);
}

void Client::send(const std::shared_ptr<BaseShape>& data) {
    SerializeUtils::Buffer buffer(SerializeUtils::serialize(data));
    sf::Packet packet;
    packet.append(buffer.data(), buffer.size());
    socket.send(packet);
}

std::vector<std::shared_ptr<BaseShape>> Client::getData() {
    sf::Packet packet;
    if (socket.receive(packet) == sf::Socket::Status::Done) {
        uint8_t* pointerToData = reinterpret_cast<uint8_t*>(const_cast<void*>(packet.getData()));
        return {SerializeUtils::deserialize(SerializeUtils::Buffer(pointerToData, pointerToData + packet.getDataSize()))};
    }
    return {};
}