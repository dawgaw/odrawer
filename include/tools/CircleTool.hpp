#include <tools/BaseTool.hpp>
#ifndef CIRCLETOOL_HPP
#define CIRCLETOOL_HPP
class CircleTool : public BaseTool {
   private:
    sf::Vector2f first_pos, last_pos;

   public:
    CircleTool(const sf::Color& color);
    void setPosition(const sf::Vector2f& pos);
    void onMousePressed(const sf::Vector2f& pos);
    sf::Drawable* getDrawable() const;
    void reset();
};
#endif
