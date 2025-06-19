#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Constants.hpp"

int main(int, char **)
{
    sf::RenderWindow window(sf::VideoMode({Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT}), "Tic tac toe", sf::Style::Default);
    window.setFramerateLimit(Constants::FRAME_PER_SECOND);

    sf::CircleShape O;
    sf::RectangleShape X;
    sf::RectangleShape winningLine;
    O.setPointCount(Constants::O_POINTCOUNT);

    char state[3][3] = {
        {'O', ' ', ' '},
        {'O', ' ', ' '},
        {'O', ' ', ' '}};

    auto DrawX = [&](float position_x, float position_y)
    {
        // X Symbol
        X.setSize({200.f, 20.f});
        X.setOrigin(X.getGeometricCenter());
        X.setFillColor(sf::Color::Green);
        X.setPosition({position_x, position_y});
        X.setRotation(sf::degrees(45));
        window.draw(X);
        X.setRotation(sf::degrees(-45));
        window.draw(X);
    };

    auto DrawO = [&](float position_x, float position_y)
    {
        // O Symbol
        O.setRadius(Constants::O_RADIUS);
        O.setOrigin(O.getGeometricCenter());
        O.setFillColor(sf::Color::Transparent);
        O.setOutlineColor(Constants::O_COLOR);
        O.setOutlineThickness(-20.f);
        O.setPosition({position_x, position_y});
        window.draw(O);
    };

    auto DrawWinningLine = [&](float position_x, float position_y, float angle)
    {
        winningLine.setSize({600.f, 10.f});
        winningLine.setOrigin(winningLine.getGeometricCenter());
        winningLine.setFillColor(sf::Color::White);
        winningLine.setPosition({position_x, position_y});
        winningLine.setRotation(sf::degrees(angle));
        window.draw(winningLine);
    };

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            {
                window.close();
            }
        }

        float window_min = (Constants::WINDOW_WIDTH < Constants::WINDOW_HEIGHT) ? Constants::WINDOW_WIDTH : Constants::WINDOW_HEIGHT;
        window.clear(sf::Color(64, 64, 64));
        for (int j = 0; j < 3; j++)
        {
            for (int i = 0; i < 3; i++)
            {
                if (state[j][i] == 'O')
                    DrawO(Constants::WINDOW_WIDTH / 2 + 200.f * (i - 1), Constants::WINDOW_HEIGHT / 2 + 200.f * (j - 1));
                else if (state[j][i] == 'X')
                    DrawX(Constants::WINDOW_WIDTH / 2 + 200.f * (i - 1), Constants::WINDOW_HEIGHT / 2 + 200.f * (j - 1));
            }
        }

        for (int i = 0; i < 3; i++)
        {
            if ((state[i][0] != ' ') and ((state[i][0] == state[i][1]) and (state[i][1] == state[i][2])))
                // Horizontal
                DrawWinningLine(Constants::WINDOW_WIDTH / 2, Constants::WINDOW_HEIGHT / 2 + 200.f * (i - 1), 0);
            else if ((state[0][i] != ' ') and ((state[0][i] == state[1][i]) and (state[1][i] == state[2][i])))
                // Verticle
                DrawWinningLine(Constants::WINDOW_WIDTH / 2 + 200.f * (i - 1), Constants::WINDOW_HEIGHT / 2, 90);
        }
        window.display();
    }
    return 0;
}