#ifndef TOOLS_CIRCLETOOL_HPP
#define TOOLS_CIRCLETOOL_HPP

#include <tools/BaseTool.hpp>

class CircleTool : public BaseTool {
   private:
    sf::Vector2f first_pos, last_pos;

   public:
    CircleTool(const sf::Color& color);
    void setPosition(const sf::Vector2f& pos);
    void onMousePressed(const sf::Vector2f& pos);
    std::shared_ptr<BaseShape> getDrawable() const;
    void reset();
};
#endif
