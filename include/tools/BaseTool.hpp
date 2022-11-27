#include <SFML/Graphics.hpp>

#ifndef BASETOOL_HPP
#define BASETOOL_HPP
class BaseTool {
   public:
    BaseTool(const sf::Color& color);

    void setColor(const sf::Color& color);

    virtual sf::Drawable* getDrawable() const = 0;
    virtual void setPosition(const sf::Vector2f& pos) = 0;
    virtual void reset() = 0;
    virtual void onMouseReleased(const sf::Vector2f& pos){};
    virtual void onMousePressed(const sf::Vector2f& pos){};

   protected:
    sf::Color color;
};
#endif
