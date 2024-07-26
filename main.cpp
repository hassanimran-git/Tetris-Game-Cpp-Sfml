 /* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */

#include <SFML/Graphics.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
#include <sstream>

#include <iostream>
using namespace std; 

using namespace sf;



int main(){

    srand(time(0));
    RenderWindow window(VideoMode(320, 480), title);
    Texture obj1, obj2, obj3, obj4;
    
    // Load image for Textures
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png"); 
    obj4.loadFromFile("img/GameOver.png"); 

    // Sprites Creation with textures
    Sprite sprite(obj1), background(obj2), frame(obj3), GameOver(obj4);

    
    int delta_x=0, colorNum=1,TotalLines=0;
    float timer=0, delay=0.3;
    bool rotate=0, drop=0, pause=0;

    int lvl2=0; //so output only once

    Clock clock;

    while (window.isOpen()){
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e)){                    //Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                window.close();                            //Opened window disposes
            if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                    rotate = true;                         //Rotation gets on
                else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                    delta_x = -1;                          //Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                    delta_x = 1;                           //Change in X-Axis - Positive
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))   //Just another way to detect key presses without event listener
        {
            delay=0.05;
            if(TotalLines>5)
            {
                delay=0.025;
            }                               //If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05

        }
        
        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///

        if(gameOver(N))
        {
            //display game over
            // window.clear();
            // window.draw(GameOver);
            // window.display();

            
            cout<<"\n____________________\n\nGame over!\n____________________\n";
            cout<<"____________________\n\nYour Score was : "<<TotalLines*10<<"\n____________________\n";
            checkHighscore(TotalLines);
            // system("pause");
            break;
        }

        if (e.key.code == Keyboard::Space)    //for immediate drop
            drop=1; 
        
        if (e.key.code == Keyboard::H) //for PAUSE & PLAY with H
        {
            (pause==1)?
                pause=0:
                pause=1;
        }
        if (pause==1)
        {
            continue; //skips the rest of the loop and goes to mext iteration
            //ie waiting till next time H is pressed so it goes on;
        }

        immediateDrop(drop);

        
        fallingPiece(timer, delay, colorNum);               //Example: fallingPiece() function is called here


        movement(delta_x); 

        rotationofblock(rotate);                       


        lineClear(M,N,TotalLines);

        if(TotalLines==5 && lvl2==0)
        {
            cout<<"\n5 lines Cleared!\n_________\nLevel 2!\n_________\n";
            lvl2++;

        }

        resetVars(delay,delta_x,TotalLines); 

        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////


        window.clear(Color::Black);
        window.draw(background);
        for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                if (gameGrid[i][j]==0)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                sprite.setPosition(j*18,i*18);
                sprite.move(28,31); //offset
                window.draw(sprite);
            }
        }
        for (int i=0; i<4; i++){
            sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
            sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
            sprite.move(28,31);
            window.draw(sprite);
          }
        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);
        //---The Window that now Contains the Frame is Displayed---//
        window.display();



        
    }
    return 0;
}