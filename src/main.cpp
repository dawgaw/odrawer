#include <argh.h>

#include <SFML/Graphics.hpp>
#include <array>
#include <elements/Button.hpp>
#include <iostream>
#include <network/Client.hpp>
#include <network/Server.hpp>
#include <tools/CircleTool.hpp>
#include <tools/LinesTool.hpp>
#include <tools/RectangleTool.hpp>

constexpr int DEFAULT_PORT = 8080;
constexpr int DEFAULT_HEIGHT = 400;
constexpr int DEFAULT_WIDTH = 800;
constexpr float BUTTON_OFFSET_Y = 20;
constexpr float BUTTON_OFFSET_X = 10;
constexpr float BUTTON_SIZE_Y = 40;
constexpr float BUTTON_SIZE_X = 80;
constexpr int FRAME_RATE = 60;

std::vector<Button> initButtons(const sf::Font &font, std::shared_ptr<BaseTool> &tool) {
    const std::array<std::pair<const sf::Color, const sf::String>, 6> colors{{
        {sf::Color::Black, "Black"},
        {sf::Color::Green, "Green"},
        {sf::Color::Yellow, "Yellow"},
        {sf::Color::Magenta, "Magenta"},
        {sf::Color::Blue, "Blue"},
        {sf::Color::White, "White"},
    }};
    const std::array<std::pair<std::shared_ptr<BaseTool>, const sf::String>, 3> tools{{
        {std::make_shared<LinesTool>(sf::Color::White), "Pen"},
        {std::make_shared<CircleTool>(sf::Color::White), "Circle"},
        {std::make_shared<RectangleTool>(sf::Color::White), "Rect"},
    }};

    std::vector<Button> buttons;
    buttons.reserve(tools.size() + colors.size());

    int index = 0;
    for (auto &&item : colors) {
        buttons.emplace_back(sf::Vector2f((BUTTON_SIZE_X + BUTTON_OFFSET_X) * index, BUTTON_OFFSET_Y), item.second, font, sf::Vector2f(BUTTON_SIZE_X, BUTTON_SIZE_Y));
        buttons.back().onClick = [&tool, color = item.first]() {
            tool->setColor(color);
        };
        index++;
    }
    index = 0;
    for (auto &&item : tools) {
        buttons.emplace_back(sf::Vector2f((BUTTON_SIZE_X + BUTTON_OFFSET_X) * index, BUTTON_OFFSET_Y * 2 + BUTTON_SIZE_Y), item.second, font, sf::Vector2f(BUTTON_SIZE_X, BUTTON_SIZE_Y));
        buttons.back().onClick = [&tool, item = item.first]() {
            tool = item;
        };
        index++;
    }
    tool = tools.at(0).first;

    return std::move(buttons);
}

int main(int argc, const char *argv[]) {
    argh::parser argParser({"-a", "--address", "-p", "--port", "-s", "--server"});

    argParser.parse(argc, argv);

    const std::string serverAddress = argParser({"-a", "--address"}, "127.0.0.1").str();
    std::cout << "ip:" << serverAddress << "\n";

    int port = DEFAULT_PORT;
    argParser({"-p", "--port"}, port) >> port;
    std::cout << "port:" << port << "\n";

    std::unique_ptr<Client> client = nullptr;
    std::unique_ptr<Server> server = nullptr;

    if (argParser[{"-s", "--server"}]) {
        std::cout << "you are server\n";
        server = std::make_unique<Server>();
        server->start(serverAddress, port);
    }

    client = std::make_unique<Client>();
    client->start(serverAddress, port);

    sf::RenderWindow window(sf::VideoMode(DEFAULT_WIDTH, DEFAULT_HEIGHT), "online drawer");
    window.setFramerateLimit(FRAME_RATE);

    sf::Font font;
    font.loadFromFile("resources/Arialn.ttf");

    std::shared_ptr<BaseTool> tool;
    std::vector<Button> buttons = std::move(initButtons(font, tool));

    sf::RenderTexture permanentPicTexture;
    permanentPicTexture.create(window.getSize().x, window.getSize().y);
    const sf::Sprite permanentPic(permanentPicTexture.getTexture());
    // permanentPicTexture.getTexture().copyToImage().saveToFile("file");

    bool isMousePressed = false;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    window.close();
                } break;

                case sf::Event::MouseButtonPressed: {
                    bool processed = false;
                    for (auto &&item : buttons) {
                        if (item.checkClick(window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y}))) {
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

        const std::shared_ptr<BaseShape> data = tool->getDrawable();
        window.draw(permanentPic);
        if (data) {
            if (isMousePressed) {
                window.draw(*data);
            } else {
                client->send(data);
                permanentPicTexture.draw(*data);
                permanentPicTexture.display();
                window.draw(permanentPic);

                tool->reset();
            }
        }

        auto recData = client->getData();
        for (auto &&item : recData) {
            permanentPicTexture.draw(*item);
            permanentPicTexture.display();
        }

        for (auto &&item : buttons) {
            item.update();
            window.draw(item);
        }

        window.display();
    }
    return 0;
}