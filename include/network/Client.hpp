#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <SFML/Network.hpp>
#include <memory>
#include <shapes/BaseShape.hpp>

class Client {
   private:
    sf::TcpSocket socket;

   public:
    std::vector<std::shared_ptr<BaseShape>> getData();
    void send(const std::shared_ptr<BaseShape>& data);
    void start(const char* ip, int port);
};
#endif