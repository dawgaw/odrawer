#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <network/NetworkInterface.hpp>

class Client : public NetworkInterface {
   private:
    sf::TcpSocket socket;

   public:
    std::vector<std::shared_ptr<BaseShape>> getData();
    void send(const std::shared_ptr<BaseShape>& data);
    void start(const char* ip, int port);
};
#endif