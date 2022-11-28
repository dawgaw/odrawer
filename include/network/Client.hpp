#include <network/NetworkInterface.hpp>

class Client : public NetworkInterface {
   private:
    sf::TcpSocket socket;

   public:
    std::vector<std::shared_ptr<BaseShape>> getData();
    void send(std::shared_ptr<BaseShape> data);
    void start();
};
