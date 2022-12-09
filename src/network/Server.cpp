#include <network/Server.hpp>
#include <utils/SerializeUtils.hpp>

void Server::start(const char* ip, int port) {
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

            // for (auto&& i : this->sockets) {
            //     if (i->getRemoteAddress() == sf::IpAddress::None) {
            //         printf("disco\n");
            //     }
            // }

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

        } while (true);
    });
    this->listenThread->launch();
}
