rm main.o Tetris
g++ -c main.cpp
g++ main.o -o Tetris -lsfml-graphics -lsfml-window -lsfml-system
./Tetris
