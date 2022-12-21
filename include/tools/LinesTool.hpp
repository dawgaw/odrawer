#ifndef TOOLS_LINETOOL_HPP
#define TOOLS_LINETOOL_HPP

#include <shapes/Line.hpp>
#include <tools/BaseTool.hpp>

class LinesTool : public BaseTool {
   private:
    sf::Vector2f prevPos;
    std::vector<Line> lines;

   public:
    LinesTool(const sf::Color& color);
    void setPosition(const sf::Vector2f& pos);
    void onMousePressed(const sf::Vector2f& pos);
    std::shared_ptr<BaseShape> getDrawable() const;
    void reset();
};
#endif
