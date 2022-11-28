#ifndef NETWORK_INTERFACE_HPP
#define NETWORK_INTERFACE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <memory>
#include <shapes/BaseShape.hpp>
#include <vector>

class NetworkInterface {
   public:
    virtual void start() = 0;
    virtual std::vector<std::shared_ptr<BaseShape>> getData() = 0;
    virtual void send(std::shared_ptr<BaseShape> data) = 0;
};

#endif