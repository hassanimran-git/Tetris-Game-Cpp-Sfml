#include <SFML/Graphics.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
#include <sstream>

#include <iostream>
using namespace std;

using namespace sf;

enum GameState
{
    Playing,
    Paused,
    Over
};

int main()
{

    srand(time(0));
    RenderWindow window(VideoMode(320, 480), title);
    Texture obj1, obj2, obj3, obj4;

    // Load image for Textures
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png");
    obj4.loadFromFile("img/GameOver.png");

    // Sprites Creation with textures
    Sprite tiles(obj1), background(obj2), frame(obj3), GameOver(obj4);

    // vars
    int delta_x = 0, colorNum = 1, TotalLines = 0;
    float timer = 0, delay = 0.3;
    bool rotate = 0, drop = 0;

    int lvl2 = 0; // so output only once

    Clock clock;
    GameState gameState = Playing;

    // Game Loop
    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
            if (e.type == Event::KeyPressed)
            {
                if (gameState == Playing)
                {
                    if (e.key.code == Keyboard::Up)
                        rotate = true;
                    else if (e.key.code == Keyboard::Left)
                        delta_x = -1;
                    else if (e.key.code == Keyboard::Right)
                        delta_x = 1;
                    else if (e.key.code == Keyboard::Space)
                        drop = 1;
                    else if (e.key.code == Keyboard::H)
                        gameState = Paused; // Switch to paused state
                }
                else if (gameState == Paused)
                {
                    if (e.key.code == Keyboard::H)
                        gameState = Playing; // Switch back to playing state
                }
            }
        }

        if (gameState == Playing)
        {

            if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                delay = 0.05;
                if (TotalLines > 5)
                {
                    delay = 0.025;
                }
            }

            ////////////////////////////////////////

            if (gameOver(N))
            {
                gameState = Over;
                continue;
            }

            immediateDrop(drop);
            fallingPiece(timer, delay, colorNum);
            movement(delta_x);
            rotationofblock(rotate);
            lineClear(M, N, TotalLines);

            if (TotalLines == 5 && lvl2 == 0)
            {
                cout << "\n5 lines Cleared!\n_________\nLevel 2!\n_________\n";
                lvl2++;
            }

            resetVars(delay, delta_x, TotalLines);

            // Drawing code for playing state
            window.clear(Color::Black);
            window.draw(background);


            for (int i = 0; i < M; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    if (gameGrid[i][j] == 0)
                        continue;
                    tiles.setTextureRect(IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                    tiles.setPosition(j * 18, i * 18);
                    tiles.move(28, 31); // Offset
                    window.draw(tiles);
                }
            }
            for (int i = 0; i < 4; i++)
            {
                tiles.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
                tiles.setPosition(point_1[i][0] * 18, point_1[i][1] * 18);
                tiles.move(28, 31);
                window.draw(tiles);
            }
            window.draw(frame);
        }
        else if (gameState == Paused)
        {
            // Drawing code for paused state
            window.clear(Color::Black);
        }
        else if (gameState == Over)
        {
            // cout << "____________________\n\nYour Score was : " << TotalLines * 10 << "\n____________________\n";
            // checkHighscore(TotalLines);
            window.clear(Color::White);
            GameOver.setScale(0.2,0.2);
            GameOver.setPosition(20, 10);
            window.draw(GameOver);

        }

        window.display();
    }

    return 0;
}
