#include <argh.h>

#include <SFML/Graphics.hpp>
#include <elements/Button.hpp>
#include <iostream>
#include <network/Client.hpp>
#include <network/Server.hpp>
#include <tools/CircleTool.hpp>
#include <tools/LinesTool.hpp>
#include <tools/RectangleTool.hpp>

int main(int argc, const char *argv[]) {
    std::unique_ptr<NetworkInterface>
        nint;

    argh::parser argParser({"-s", "--server", "-p", "--port", "-a", "--address"});
    argParser.parse(argc, argv);

    int port = 8080;
    if (argParser[{"p", "port"}])
        argParser({"p", "port"}) >> port;

    const char *ip = "127.0.0.1";
    if (argParser[{"a", "address"}])
        ip = argParser({"a", "address"}).str().c_str();

    if (argParser[{"s", "server"}]) {
        std::cout << "server\n";
        nint = std::make_unique<Server>();
    } else {
        std::cout << "client\n";
        nint = std::make_unique<Client>();
    }

    sf::RenderWindow window(sf::VideoMode(800, 400), "online drawer");
    window.setFramerateLimit(60);

    sf::Font font;
    font.loadFromFile("resources/Arialn.ttf");

    std::vector<Button> buttons;
    buttons.reserve(10);

    BaseTool *tool;

    bool isMousePressed = false;

    nint->start(ip, port);

    {  // init buttons
        const std::array<std::pair<const sf::Color, const sf::String>, 6> colors{{
            {sf::Color::Black, "Black"},
            {sf::Color::Green, "Green"},
            {sf::Color::Yellow, "Yellow"},
            {sf::Color::Magenta, "Magenta"},
            {sf::Color::Blue, "Blue"},
            {sf::Color::White, "White"},
        }};
        const std::array<std::pair<BaseTool *, const sf::String>, 3> tools{{
            {new LinesTool(sf::Color::White), "pen"},
            {new CircleTool(sf::Color::White), "Circle"},
            {new RectangleTool(sf::Color::White), "rect"},
        }};
        auto index = 0;
        for (auto &&i : colors) {
            buttons.emplace_back(sf::Vector2f(100 * index, 20), i.second, font);
            buttons.back().onClick = [color = i.first, &tool]() {
                tool->setColor(color);
            };
            index++;
        }
        index = 0;
        for (auto &&i : tools) {
            buttons.emplace_back(sf::Vector2f(100 * index, 50), i.second, font);
            buttons.back().onClick = [&tool, t = i.first]() {
                tool = t;
            };
            index++;
        }
        tool = tools.at(0).first;
    }

    sf::RenderTexture permanentPicTexture;
    permanentPicTexture.create(window.getSize().x, window.getSize().y);
    sf::Sprite permanentPic(permanentPicTexture.getTexture());
    // permanentPic.scale({1, -1});
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    window.close();
                } break;

                case sf::Event::MouseButtonPressed: {
                    bool processed = false;
                    for (auto &&i : buttons) {
                        if (i.checkClick(window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y}))) {
                            processed = true;
                            break;
                        }
                    }
                    if (!processed) {
                        isMousePressed = true;
                        tool->onMousePressed(window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y}));
                    }
                } break;

                case sf::Event::MouseButtonReleased: {
                    isMousePressed = false;
                    tool->onMouseReleased(window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y}));
                } break;

                case sf::Event::MouseMoved: {
                    if (isMousePressed) {
                        tool->setPosition(window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y}));
                    }
                } break;
                default:
                    break;
            }
        }
        window.clear();

        std::shared_ptr<BaseShape> d = tool->getDrawable();
        window.draw(permanentPic);
        if (d) {
            if (isMousePressed)
                window.draw(*d);
            else {
                nint->send(d);
                permanentPicTexture.draw(*d);
                permanentPicTexture.display();
                window.draw(permanentPic);

                tool->reset();
            }
        }

        auto recData = nint->getData();
        for (auto &&i : recData) {
            permanentPicTexture.draw(*i);
            permanentPicTexture.display();
        }

        for (auto &&i : buttons) {
            i.update();
            window.draw(i);
        }

        window.display();
    }
    return 0;
}