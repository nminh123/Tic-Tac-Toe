#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Constants.hpp"

int main(int, char**)
{
    // sf::Window window(sf::VideoMode(sf::Vector2u(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT), "Tic tac toe");
    sf::RenderWindow window(sf::VideoMode({Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT}), "Tic tac toe", sf::Style::Default);
    window.setFramerateLimit(Constants::FRAME_PER_SECOND);

    // sf::CircleShape O;
    // O.setPointCount(Constants::O_POINTCOUNT);
    sf::RectangleShape X;

    while(window.isOpen())
    {
        while(const std::optional event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            {
                window.close();
            }
        }

        float window_min = (Constants::WINDOW_WIDTH < Constants::WINDOW_HEIGHT) ? Constants::WINDOW_WIDTH : Constants::WINDOW_HEIGHT;
        window.clear();
        // X Symbol
        X.setSize({200.f, 20.f});
        X.setOrigin(X.getGeometricCenter());
        X.setFillColor(sf::Color::Green);
        X.setPosition({Constants::WINDOW_WIDTH / 2.f, Constants::WINDOW_HEIGHT / 2.f});
        X.setRotation(sf::degrees(45));
        window.draw(X);
        X.setRotation(sf::degrees(-45));
        window.draw(X);

        // O Symbol
        // O.setRadius(Constants::O_RADIUS);
        // O.setOrigin(O.getGeometricCenter());
        // O.setFillColor(sf::Color::Blue);
        // O.setOutlineColor(Constants::O_COLOR);
        // O.setOutlineThickness(-5.f);
        // O.setPosition({Constants::WINDOW_WIDTH / 2.f, Constants::WINDOW_HEIGHT / 2.f});
        // window.draw(O);
        window.display();
    }
    return 0;
}