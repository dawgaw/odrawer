#include <network/NetworkInterface.hpp>
#include <thread>

class Server : public NetworkInterface {
   private:
    std::vector<std::unique_ptr<sf::TcpSocket>> sockets;
    sf::TcpListener listener;
    std::thread thrd;

   public:
    std::vector<std::shared_ptr<BaseShape>> getData();
    void send(std::shared_ptr<BaseShape> data);
    void start();
    ~Server();
};
