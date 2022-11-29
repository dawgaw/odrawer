#include <network/Server.hpp>
#include <utils/SerializeUtils.hpp>

Server::~Server() {
    if (this->listenThread)
        this->listenThread->terminate();
    this->listener.close();
}

void Server::start(const char* ip, int port) {
    this->listener.listen(port, ip);
    this->listenThread = std::make_unique<sf::Thread>([this] {
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
}

void Server::sendAllExcept(sf::Packet& packet, const std::unique_ptr<sf::TcpSocket>& socket) {
    for (auto&& i : sockets) {
        if (i.get() != socket.get())
            i->send(packet);
    }
}

void Server::send(const std::shared_ptr<BaseShape>& data) {
    SerializeUtils::Buffer buffer(SerializeUtils::serialize(data));
    sf::Packet p;
    p.append(buffer.data(), buffer.size());
    this->sendAllExcept(p, nullptr);
}

std::vector<std::shared_ptr<BaseShape>> Server::getData() {
    std::vector<std::shared_ptr<BaseShape>> d;
    for (auto&& i : sockets) {
        sf::Packet p;
        if (i->receive(p) == sf::Socket::Status::Done) {
            std::shared_ptr<BaseShape> data = SerializeUtils::deserialize(SerializeUtils::Buffer((uint8_t*)p.getData(), (uint8_t*)p.getData() + p.getDataSize()));
            this->sendAllExcept(p, i);
            d.push_back(std::move(data));
        }
    }
    return d;
}