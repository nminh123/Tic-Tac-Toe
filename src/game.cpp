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
    sf::RectangleShape cursor;
    O.setPointCount(Constants::O_POINTCOUNT);

    char state[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};

    int cursor_x = 1, cursor_y = 1;
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

    auto DrawWinningLine = [&](float position_x, float position_y, float angle, float size = 1.f)
    {
        winningLine.setSize({600.f * size, 10.f});
        winningLine.setOrigin(winningLine.getGeometricCenter());
        winningLine.setFillColor(sf::Color::White);
        winningLine.setPosition({position_x, position_y});
        winningLine.setRotation(sf::degrees(angle));
        window.draw(winningLine);
    };

    auto DrawCursor = [&](float position_x, float position_y)
    {
        cursor.setSize({Constants::CURSOR_WIDTH, Constants::CURSOR_HEIGHT});
        cursor.setOrigin(cursor.getGeometricCenter());
        cursor.setFillColor(sf::Color::Transparent);
        cursor.setOutlineColor(Constants::CURSOR_OUTLINE_COLOR);
        cursor.setOutlineThickness(-10.f);
        cursor.setPosition({position_x, position_y});
        window.draw(cursor);
    };

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            {
                window.close();
            }
            else if (event->is<sf::Event::Resized>())
            {
                // update view
                sf::View view(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize())));
                window.setView(view);
            }
            else if(auto* key = event->getIf<sf::Event::KeyPressed>())
            {
                if((key->scancode == sf::Keyboard::Scancode::A || key->scancode == sf::Keyboard::Scancode::Left) and (cursor_x > 0))
                    cursor_x--;
                else if((key->scancode == sf::Keyboard::Scancode::D || key->scancode == sf::Keyboard::Scancode::Right) and (cursor_x < 2))
                    cursor_x++;
                else if((key->scancode == sf::Keyboard::Scancode::W || key->scancode == sf::Keyboard::Scancode::Up) and (cursor_y > 0))
                    cursor_y--;
                else if((key->scancode == sf::Keyboard::Scancode::S || key->scancode == sf::Keyboard::Scancode::Down) and (cursor_y < 2))
                    cursor_y++;

                if(key->scancode == sf::Keyboard::Scancode::X || key->scancode == sf::Keyboard::Scancode::LShift)
                    state[cursor_y][cursor_x] = 'X';
                else if(key->scancode == sf::Keyboard::Scancode::O || key->scancode == sf::Keyboard::Scancode::RShift)
                    state[cursor_y][cursor_x] = 'O';
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
            {
                // Horizontal
                DrawWinningLine(Constants::WINDOW_WIDTH / 2, Constants::WINDOW_HEIGHT / 2 + 200.f * (i - 1), 0);
            }
            else if ((state[0][i] != ' ') and ((state[0][i] == state[1][i]) and (state[1][i] == state[2][i])))
            {
                // Verticle
                DrawWinningLine(Constants::WINDOW_WIDTH / 2 + 200.f * (i - 1), Constants::WINDOW_HEIGHT / 2, 90);
            }
            // else if(state[])
        }

        if((state[0][0] != ' ') and ((state[0][0] == state[1][1]) and (state[1][1] == state[2][2])))
        {
            DrawWinningLine(Constants::WINDOW_WIDTH / 2, Constants::WINDOW_HEIGHT / 2, 45.f, 1.4f);
        }
        else if((state[2][0] != ' ') and ((state[2][0] == state[1][1]) and (state[1][1]) == state[0][2]))
        {
            DrawWinningLine(Constants::WINDOW_WIDTH / 2, Constants::WINDOW_HEIGHT / 2, -45.f, 1.4f);
        } 

        DrawCursor(Constants::WINDOW_WIDTH / 2 + 200.f * (cursor_x - 1), Constants::WINDOW_HEIGHT / 2 + 200.f * (cursor_y - 1));
        window.display();
    }
    return 0;
}