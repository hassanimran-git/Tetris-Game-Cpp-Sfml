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
    Menu,
    Playing,
    Paused,
    Over,
    HighScore
};

void drawMenu(RenderWindow &window, Text &newGameText, Text &highScoreText, Text &exitText, Sprite &MenuBack)
{
    window.clear(Color::Black);
    window.draw(MenuBack);
    window.draw(newGameText);
    window.draw(highScoreText);
    window.draw(exitText);
    window.display();
}

void drawHighScore(RenderWindow &window, Text &highScoreText, Text &backText)
{
    window.clear(Color::Black);
    window.draw(highScoreText);
    window.draw(backText);
    window.display();
}

int main()
{
    srand(time(0));
    RenderWindow window(VideoMode(320, 480), title);
    Texture obj1, obj2, obj3, obj4, obj5;

    // Load image for Textures
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png");
    obj4.loadFromFile("img/GameOver.png");
    obj5.loadFromFile("img/Menu.png");

    // Sprites Creation with textures
    Sprite tiles(obj1), background(obj2), frame(obj3), GameOver(obj4), MenuBack(obj5);

    // Font and text for menu
    Font font;
    if (!font.loadFromFile("img/font2.ttf"))
        return -1;

    Text newGameText("[1] New Game", font, 30);
    newGameText.setPosition(50, 150 + 30);
    newGameText.setFillColor(Color::White);

    Text highScoreText("[2] High Score", font, 30);
    highScoreText.setPosition(50, 200 + 50);
    highScoreText.setFillColor(Color::White);

    Text exitText("[3] Exit", font, 30);
    exitText.setPosition(50, 250 + 70);
    exitText.setFillColor(Color::White);

    Text PlayerHighScoreText("", font, 40);
    PlayerHighScoreText.setPosition(50, 200);
    PlayerHighScoreText.setFillColor(Color::White);

    Text backText("[esc] MENU", font, 20);
    backText.setPosition(80, 400);
    backText.setFillColor(Color::White);

    Text ScoreOutput("", font, 20);
    Text HighscoreOutput("New HighScore!\nEnter Your Name : \n", font, 20);

    // vars
    int delta_x = 0, colorNum = 1, TotalLines = 0;
    float timer = 0, delay = 0.3;
    bool rotate = 0, drop = 0;

    Clock clock;
    GameState gameState = Menu;

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
                if (gameState == Menu)
                {
                    if (e.key.code == Keyboard::Num1)
                    {

                        // delta_x = 0;
                        // colorNum = 1;
                        // TotalLines = 0;
                        // timer = 0;
                        // delay = 0.3;
                        // rotate = 0;
                        // drop = 0;
                        // window.clear(Color::Black);
                        gameState = Playing;
                    }
                    else if (e.key.code == Keyboard::Num2)
                        gameState = HighScore;
                    else if (e.key.code == Keyboard::Num3)
                        window.close();
                }
                else if (gameState == HighScore)
                {
                    if (e.key.code == Keyboard::Escape)
                        gameState = Menu;
                }
                else if (gameState == Playing)
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
                else if (gameState == Over)
                {
                    if (e.key.code == Keyboard::Escape)
                        gameState = Menu;
                }
            }
        }

        if (gameState == Menu)
        {
            drawMenu(window, newGameText, highScoreText, exitText, MenuBack);
        }
        else if (gameState == HighScore)
        {
            string name, highestScore;
            ifstream input("highestscore.txt");
            input >> highestScore >> name;
            input.close();
            PlayerHighScoreText.setString(name + " : " + highestScore);
            drawHighScore(window, PlayerHighScoreText, backText);
        }
        else if (gameState == Playing)
        {
            if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                delay = 0.05;
                if (TotalLines > 5)
                {
                    delay = 0.025;
                }
            }

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

            resetVars(delay, delta_x, TotalLines);

            // Drawing code for playing state
            window.clear(Color::Black);
            // window.draw(background);

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
            window.clear(Color::White);
            GameOver.setScale(0.2, 0.2);
            GameOver.setPosition(40, 10);
            window.draw(GameOver);
            ScoreOutput.setFillColor(Color::Black);
            ScoreOutput.setString("Your Score was : " + to_string(TotalLines * 10));
            ScoreOutput.setPosition(50, 200);
            window.draw(ScoreOutput);

            if (checkHighscore(TotalLines))
            {
                HighscoreOutput.setFillColor(Color::Black);
                HighscoreOutput.setPosition(50, 250);
                window.draw(HighscoreOutput);

                /*
                cout << "Congragulations!You Have Set a New Highscore!\n";
                string name = " ";
                cout << "Enter Your Username to Save your Score :";
                cin >> name;
                output << "   " << name; // writing name to file
                */
            }
        }

        window.display();
    }

    return 0;
}
