#ifndef SERVER_HPP
#define SERVER_HPP

#include <SFML/System/Thread.hpp>
#include <network/NetworkInterface.hpp>

class Server : public NetworkInterface {
   private:
    std::vector<std::unique_ptr<sf::TcpSocket>> sockets;
    sf::TcpListener listener;
    std::unique_ptr<sf::Thread> listenThread;

   public:
    std::vector<std::shared_ptr<BaseShape>> getData();
    void send(const std::shared_ptr<BaseShape>& data);
    void sendAllExcept(sf::Packet& packet, const std::unique_ptr<sf::TcpSocket>& socket = nullptr);
    void start(const char* ip, int port);
    ~Server();
};

#endif