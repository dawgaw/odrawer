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
    void start(const std::string& ip, int port);
    ~Server();
};

#endif