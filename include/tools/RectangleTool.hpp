#ifndef RECTANGLETOOL_HPP
#define RECTANGLETOOL_HPP

#include <tools/BaseTool.hpp>

class RectangleTool : public BaseTool {
   private:
    sf::Vector2f first_pos, last_pos;

   public:
    RectangleTool(const sf::Color& color);
    void setPosition(const sf::Vector2f& pos);
    void onMousePressed(const sf::Vector2f& pos);
    std::shared_ptr<BaseShape> getDrawable() const;
    void reset();
};
#endif
