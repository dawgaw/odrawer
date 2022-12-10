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
    argh::parser argParser({"-a", "--address", "-p", "--port", "-s", "--server"});

    argParser.parse(argc, argv);

    const std::string ip = argParser({"-a", "--address"}, "127.0.0.1").str();
    printf("%s\n", ip.c_str());

    int port;
    argParser({"-p", "--port"}, 8080) >> port;
    printf("%d\n", port);

    std::unique_ptr<Client> client;
    std::unique_ptr<Server> server;

    if (argParser[{"-s", "--server"}]) {
        printf("you are server\n");
        server = std::make_unique<Server>();
        server->start(ip, port);
    }

    client = std::make_unique<Client>();
    client->start(ip, port);

    sf::RenderWindow window(sf::VideoMode(800, 400), "online drawer");
    window.setFramerateLimit(60);

    sf::Font font;
    font.loadFromFile("resources/Arialn.ttf");

    std::vector<Button> buttons;
    buttons.reserve(10);

    std::shared_ptr<BaseTool> tool;

    {  // init buttons
        const std::array<std::pair<const sf::Color, const sf::String>, 6> colors{{
            {sf::Color::Black, "Black"},
            {sf::Color::Green, "Green"},
            {sf::Color::Yellow, "Yellow"},
            {sf::Color::Magenta, "Magenta"},
            {sf::Color::Blue, "Blue"},
            {sf::Color::White, "White"},
        }};
        const std::array<std::pair<std::shared_ptr<BaseTool>, const sf::String>, 3> tools{{
            {std::make_shared<LinesTool>(sf::Color::White), "pen"},
            {std::make_shared<CircleTool>(sf::Color::White), "Circle"},
            {std::make_shared<RectangleTool>(sf::Color::White), "rect"},
        }};
        int index = 0;
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
    // permanentPicTexture.getTexture().copyToImage().saveToFile("file");

    bool isMousePressed = false;

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
                client->send(d);
                permanentPicTexture.draw(*d);
                permanentPicTexture.display();
                window.draw(permanentPic);

                tool->reset();
            }
        }

        auto recData = client->getData();
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