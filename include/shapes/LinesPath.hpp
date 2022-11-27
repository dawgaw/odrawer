#include <shapes/Line.hpp>

#ifndef LINESPATH_HPP
#define LINESPATH_HPP
class LinesPath : public sf::Drawable {
   private:
    std::vector<Line> lines;

   public:
    LinesPath(const std::vector<Line> &lines);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void addLine(const Line &line);
};
#endif