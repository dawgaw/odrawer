#include <chrono>
#include <iostream>
#include <network/Server.hpp>
#include <thread>
#include <utils/SerializeUtils.hpp>

Server::~Server() {
    this->listenThread->terminate();
}

void Server::start(const std::string& ipAddress, int port) {
    this->listener.listen(port, ipAddress);
    this->listener.setBlocking(false);

    this->listenThread = std::make_unique<sf::Thread>([this] {
        std::unique_ptr<sf::TcpSocket> newClient = nullptr;
        do {
            newClient = std::make_unique<sf::TcpSocket>();

            if (this->listener.accept(*newClient) == sf::Socket::Status::Done) {
                this->clients.push_back(std::move(newClient));
                this->clients.back()->setBlocking(false);
                std::cout << "server:new connection\n";
            }

            this->clients.erase(std::remove_if(this->clients.begin(), this->clients.end(), [](std::unique_ptr<sf::TcpSocket>& client) {
                                    if (client->getRemoteAddress() == sf::IpAddress::None) {
                                        std::cout << "server:client disconnected\n";
                                        return true;
                                    }
                                    return false;
                                }),
                                this->clients.end());

            sf::Packet packet;
            for (auto&& rClient : this->clients) {
                if (rClient->receive(packet) == sf::Socket::Status::Done) {
                    for (auto&& client : this->clients) {
                        if (client != rClient) {
                            client->send(packet);
                        }
                    }
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));

        } while (true);
    });
    this->listenThread->launch();
}
