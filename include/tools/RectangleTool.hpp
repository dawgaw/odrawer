#include <tools/BaseTool.hpp>
#ifndef RECTANGLETOOL_HPP
#define RECTANGLETOOL_HPP

class RectangleTool : public BaseTool {
   private:
    sf::Vector2f first_pos, last_pos;

   public:
    RectangleTool(const sf::Color& color);
    void setPosition(const sf::Vector2f& pos);
    void onMousePressed(const sf::Vector2f& pos);
    sf::Drawable* getDrawable() const;
    void reset();
};
#endif
