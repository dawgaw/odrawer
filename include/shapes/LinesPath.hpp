#ifndef LINESPATH_HPP
#define LINESPATH_HPP

#include <shapes/Line.hpp>

class LinesPath : public BaseShape {
   private:
    std::vector<Line> lines;

    template <typename S>
    friend void serialize(S& s, LinesPath& o);
    friend class bitsery::Access;

   public:
    LinesPath() = default;
    LinesPath(const std::vector<Line>& lines);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void addLine(const Line& line);
};
#endif