#include <elements/Button.hpp>

Button::Button(const sf::Vector2f &location, const sf::String &text, const sf::Font &font, const sf::Vector2f &size,
               const sf::Color &defaultColor, const sf::Color &pressedColor, const sf::Color &fontColor)
    : location(location), size(size), pressedColor(pressedColor), defaultColor(defaultColor), fontColor(fontColor), font(&font), pressed(false) {
    this->curCol = &this->defaultColor;
    this->setText(text);
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::RectangleShape b(this->size);
    b.setPosition(this->location);
    b.setFillColor(*this->curCol);

    target.draw(b);
    target.draw(this->text);
}

void Button::update() {
    if (pressed) {
        const auto dur = std::chrono::high_resolution_clock::now() - this->pressedTime;
        if (std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() > 200) {
            curCol = &this->defaultColor;
            pressed = false;
        }
    }
}
void Button::handleClick() {
    pressedTime = std::chrono::system_clock::now();
    pressed = true;
    curCol = &this->pressedColor;
    if (onClick)
        onClick();
}

bool Button::checkClick(const sf::Vector2f &mousePos) {
    const auto offsetX = mousePos.x - this->location.x;
    const auto offsetY = mousePos.y - this->location.y;

    if (offsetX < 0 || offsetY < 0)
        return false;

    if (offsetX < this->size.x && offsetY < this->size.y) {
        this->handleClick();
        return true;
    }

    return false;
}

void Button::setText(const std::string &newText) {
    this->text.setFont(*this->font);
    this->text.setCharacterSize(16);
    this->text.setFillColor(this->fontColor);
    this->text.setString(newText);
    const sf::FloatRect &tsize = this->text.getGlobalBounds();
    const float ox = this->size.x - tsize.width;
    const float oy = this->size.y - tsize.height - 5;
    this->text.setPosition(this->location.x + ox / 2, this->location.y + oy / 2);
}

sf::String Button::getText() const {
    return this->text.getString();
}
