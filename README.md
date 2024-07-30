# Tetris Game in C++ using SFML

## Table of Contents
- [Introduction]
- [Features]
- [Controls]
- [Game States]
- [Instructions]
- [Installation]
- [Usage]
- [Files]

## Introduction
This project is a classic Tetris game developed in C++ using the SFML (Simple and Fast Multimedia Library). The game includes various features such as a main menu, game over screen, high scores, and different game states like playing, paused, and viewing high scores. It uses basic PF concepts

## Features
- Classic Tetris gameplay
- Main menu for navigation
- High score tracking and display
- Pause and resume functionality
- Real-time scoring
- User input for player names upon achieving a high score
- Various game states (Menu, Playing, Paused, Game Over, High Score)

## Controls
- **Left Arrow**: Move left
- **Right Arrow**: Move right
- **Up Arrow**: Rotate piece
- **Down Arrow**: Speed up the fall of the piece
- **Spacebar**: Drop piece instantly
- **P**: Pause/Resume game
- **H**: Pause/Resume game
- **1**: Start a new game (from the menu)
- **2**: View high scores (from the menu)
- **3**: Exit game (from the menu)
- **Esc**: Return to menu (from game over or high score screen)

## Game States
1. **Menu**: The starting screen where players can start a new game, view high scores, or exit.
2. **Playing**: The main game state where the Tetris game is played.
3. **Paused**: A state where the game is paused and can be resumed.
4. **Game Over**: The state when the game ends, either when the player loses or a new high score is achieved.
5. **High Score**: A screen displaying the highest scores achieved by players.

## Instructions
1. **Starting the Game**:
   - Open the executable to start the game.
   - From the menu, press `1` to start a new game.

2. **Playing the Game**:
   - Use the arrow keys and spacebar to control the pieces.
   - Score points by clearing lines.

3. **Pausing the Game**:
   - Press `P` to pause and resume the game.

4. **Game Over**:
   - Enter your name if you achieve a high score.
   - Press `Esc` to return to the main menu.

5. **Viewing High Scores**:
   - From the menu, press `2` to view the high scores.

## Installation
1. **Clone the Repository**:
   git clone https://github.com/yourusername/tetris-sfml.git

2. **Install SFML**:
   - Download and install SFML from the [official website](https://www.sfml-dev.org/download.php).

3. **Compile the Project**:
   - Use the "buildrun.sh" file to compile and run the project

## Usage
**Running the Game**:
   - After compiling, run the executable file generated.
   - Follow the on-screen instructions to navigate through the menu and play the game.

## Files
- `main.cpp`: Contains the main game loop and event handling.
- `pieces.h` and `pieces.cpp`: Handles the Tetris pieces.
- `functionality.h` and `functionality.cpp`: Contains game logic such as piece movement and collision detection.
- `utils.h`: Contains utility functions.
- `img/`: Directory containing images and fonts used in the game.
- `highestscore.txt`: File to store and retrieve the highest scores.
