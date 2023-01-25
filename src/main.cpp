
#include "board.h"
#include <cstdio> // printf
#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h> // usleep

// https://cboard.cprogramming.com/c-programming/108832-what-if-i-want-run-kbhit-background-process-like-why-not-work-proprely.html
int _kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

void setCoordinates(std::size_t row = 0, std::size_t column = 0)
{
    std::printf("\033[%ld;%ldH", row, column);
}

void setGlider(Board& brd, std::size_t row = 0, std::size_t column = 0)
{
    // Trzeba poprawić, aby nie wychodziło poza zakres board
    brd.setCellLive(row + 0, column + 1);
    brd.setCellLive(row + 1, column + 2);
    brd.setCellLive(row + 2, column + 0);
    brd.setCellLive(row + 2, column + 1);
    brd.setCellLive(row + 2, column + 2);
}

int main()
{
    Board board(10, 20);
    setGlider(board, 1, 1);

    system("clear");

    std::size_t generation = 0;
    while(!_kbhit())
    {
        setCoordinates();
        std::cout << "Generation: " << generation++ << std::endl;
        board.printBoard();
        board.updateBoard();
        usleep(500000);
    }

    return 0;
}
