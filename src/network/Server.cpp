#include <chrono>
#include <network/Server.hpp>
#include <thread>
#include <utils/SerializeUtils.hpp>

Server::~Server() {
    this->listenThread->terminate();
}

void Server::start(const std::string& ip, int port) {
    this->listener.listen(port, ip);
    this->listener.setBlocking(false);
    this->listenThread = std::make_unique<sf::Thread>([this] {
        do {
            std::unique_ptr<sf::TcpSocket> socket = std::make_unique<sf::TcpSocket>();
            if (this->listener.accept(*socket) == sf::Socket::Status::Done) {
                this->sockets.push_back(std::move(socket));
                this->sockets.back()->setBlocking(false);
                printf("server:new connection\n");
            }
            this->sockets.erase(std::remove_if(this->sockets.begin(), this->sockets.end(), [](std::unique_ptr<sf::TcpSocket>& i) {
                                    if (i->getRemoteAddress() == sf::IpAddress::None) {
                                        printf("server:client disconnected\n");
                                        return true;
                                    }
                                    return false;
                                }),
                                this->sockets.end());

            sf::Packet p;
            for (auto&& i : this->sockets) {
                if (i->receive(p) == sf::Socket::Status::Done) {
                    for (auto&& j : this->sockets) {
                        if (j != i) {
                            j->send(p);
                        }
                    }
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));

        } while (true);
    });
    this->listenThread->launch();
}
