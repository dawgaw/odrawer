#ifndef NETWORK_SERVER_HPP
#define NETWORK_SERVER_HPP

#include <SFML/Network.hpp>
#include <SFML/System/Thread.hpp>
#include <memory>
class Server {
   private:
    std::vector<std::unique_ptr<sf::TcpSocket>> clients;
    sf::TcpListener listener;
    std::unique_ptr<sf::Thread> listenThread;

   public:
    void start(const std::string& ipAddress, int port);
    ~Server();
};

#endif