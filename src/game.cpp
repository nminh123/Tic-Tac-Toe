#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Constants.hpp"

int main(int, char**)
{
    // sf::Window window(sf::VideoMode(sf::Vector2u(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT), "Tic tac toe");
    sf::RenderWindow window(sf::VideoMode({Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT}), "Tic tac toe", sf::Style::Default);
    window.setFramerateLimit(Constants::FRAME_PER_SECOND);

    while(window.isOpen())
    {
        while(const std::optional event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            {
                window.close();
            }
        }
        window.clear();
        window.display();
    }
    return 0;
}