#ifndef BASETOOL_HPP
#define BASETOOL_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <shapes/BaseShape.hpp>

class BaseTool {
   public:
    BaseTool(const sf::Color& color);

    void setColor(const sf::Color& color);

    virtual std::shared_ptr<BaseShape> getDrawable() const = 0;
    virtual void setPosition(const sf::Vector2f& pos) = 0;
    virtual void reset() = 0;
    virtual void onMouseReleased(const sf::Vector2f& pos){};
    virtual void onMousePressed(const sf::Vector2f& pos){};

   protected:
    sf::Color color;
};
#endif
