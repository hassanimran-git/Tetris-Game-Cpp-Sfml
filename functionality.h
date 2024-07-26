/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

//---Piece Starts to Fall When Game Starts---//

#include <fstream>
#include <iostream>
using namespace std;

void fallingPiece(float &timer, float &delay, int &colorNum)
{
    if (timer > delay)
    {
        for (int i = 0; i < 4; i++)
        {
            point_2[i][0] = point_1[i][0];
            point_2[i][1] = point_1[i][1];
            point_1[i][1] += 1; // How much units downward
        }
        if (!anamoly())
        {
            for (int i = 0; i < 4; i++)
            {
                gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
            }

            colorNum = 1 + rand() % 7; // generate random b/w 1-7***
            int n = rand() % 7;

            //--- Un-Comment this Part When You Make BLOCKS array---//

            for (int i = 0; i < 4; i++)
            {
                point_1[i][0] = BLOCKS[n][i] % 2;
                point_1[i][1] = BLOCKS[n][i] / 2;
            }
        }
        timer = 0;
    }
}

/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///

void movement(int &delta_x) // Left right movement
{
    for (int i = 0; i < 4; i++)
    {
        point_2[i][0] = point_1[i][0];
        point_2[i][1] = point_1[i][1];
        // point_1 has been temporaily stored in point_2 b4 manipulating

        point_1[i][0] += delta_x;
    }
    if (!anamoly())
    {
        for (int i = 0; i < 4; i++)
        {
            point_1[i][0] = point_2[i][0];
            point_1[i][1] = point_2[i][1];
        }
    }
    // point_1 restored from point 2 if out of frame anomaly
}

void resetVars(float &delay, int &delta_x, int &TotalLines) // resets variable back to orignal value for next loop***
{
    delay = 0.3; // reset delay so piece fast only as long as down key pressed
    delta_x = 0;
    if (TotalLines >= 5)
    {
        delay = 0.2;
    }
}

void immediateDrop(bool &drop)
{
    while (drop)
    {
        int i = 0;
        while (i < 4)
        {
            point_2[i][1] = point_1[i][1];
            point_1[i][1] += 1;
            i++;
        }
        if (!anamoly())
        {
            i = 0;
            while (i < 4)
            {
                point_1[i][1] = point_2[i][1];
                drop = 0;
                i++;
            }
        }
    }
}

void lineClear(int M, int N, int &TotalLines) // M=Rows , N=Columns
{
    bool clear = 0;

    for (int i = 0; i < M; i++) // iterating rows
    {
        clear = 1;                  // reset clear to 1 at before each for loop
        for (int j = 0; j < N; j++) // iterating cols
        {
            if (gameGrid[i][j] == 0)
            {
                // Clear becomes false as soon as exmpty box encountered
                clear = 0;
                break;
            }
        }
        if (clear == 1)
        {
            // iterating the Row that is full removing each box
            for (int j = 0; j < N; j++)
            {
                for (int y = 0; y < M; y++)
                {
                    gameGrid[i - y][j] = gameGrid[i - 1 - y][j];
                    // going back up copy each line down
                    //  gameGrid[i-1][j]=gameGrid[i-2][j];
                    //  gameGrid[i-2][j]=gameGrid[i-3][j]
                    if ((i - 2 - y) < 0) // if next to be copied is over the top end loop
                    {
                        break;
                    }
                }
            }
            TotalLines++;
            cout << "\nline Clear!\n+10 points\nScore : " << TotalLines * 10 << endl;

            break;
        }
    }
}

bool gameOver(int N)
{
    for (int i = 0; i < N; i++)
    {
        if (gameGrid[0][i] != 0)
        {
            return true;
        }
    }
    return false;
}

void checkHighscore(int &TotalLines)
{
    int highestScore = 0;
    std::ifstream input("highestscore.txt"); // file opened for reading
    input >> highestScore;                   // taking input from the file into variable
    if (highestScore < (TotalLines * 10))
    {
        std::ofstream output("highestscore.txt"); // file opened for writing
        output << (TotalLines * 10);              // writing new highscore back to file
        cout << "Congragulations!You Have Set a New Highscore!\n";
        string name = " ";
        cout << "Enter Your Username to Save your Score :";
        cin >> name;
        output << "   " << name; // writing name to file
    }
}

void rotationofblock(bool &rotate)
{
    if (rotate)
    {
        int centerxaxis = point_1[2][0];
        int centeryaxis = point_1[2][1];
        for (int i = 0; i < 4; i += 1)
        {
            point_2[i][0] = point_1[i][0];
            point_2[i][1] = point_1[i][1];
            int rotationaroundxaxis = 0;
            int rotationaroundyaxis = 0;
            rotationaroundxaxis = point_1[i][1] - centeryaxis;
            rotationaroundyaxis = point_1[i][0] - centerxaxis;
            point_1[i][0] = centerxaxis - rotationaroundxaxis;
            point_1[i][1] = centeryaxis + rotationaroundyaxis;
        }
        if (!anamoly())
            for (int i = 0; i < 4; i++)
            {
                point_1[i][0] = point_2[i][0];
                point_1[i][1] = point_2[i][1];
            }
    }
    rotate = 0;
}

///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
