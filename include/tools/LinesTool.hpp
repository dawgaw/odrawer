#include <shapes/Line.hpp>
#include <tools/BaseTool.hpp>

#ifndef LINETOOL_HPP
#define LINETOOL_HPP
class LinesTool : public BaseTool {
   private:
    sf::Vector2f prevPos;
    std::vector<Line> lines;

   public:
    LinesTool(const sf::Color& color);
    void setPosition(const sf::Vector2f& pos);
    void onMousePressed(const sf::Vector2f& pos);
    sf::Drawable* getDrawable() const;
    void reset();
};
#endif
