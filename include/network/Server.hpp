#ifndef SERVER_HPP
#define SERVER_HPP

#include <SFML/Network.hpp>
#include <SFML/System/Thread.hpp>
#include <memory>
class Server {
   private:
    std::vector<std::unique_ptr<sf::TcpSocket>> sockets;
    sf::TcpListener listener;
    std::unique_ptr<sf::Thread> listenThread;

   public:
    void start(const char* ip, int port);
    ~Server() {
        this->listenThread->terminate();
    }
};

#endif