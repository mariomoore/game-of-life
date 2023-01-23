#pragma once

#include <cstddef> // size_t

class Board
{
    enum State { dead, live};
    enum Action { kill = -1, save, born };
    std::size_t height;
    std::size_t width;
    short** board;
    short** propagation;

    short countNeighbours(std::size_t row, std::size_t column);
public:
    Board(std::size_t h, std::size_t w);
    ~Board();
    std::size_t getHeight() { return height; }
    void printBoard();
    void setCellLive(std::size_t row, std::size_t column);
    void switchCell(std::size_t row, std::size_t column);
    void updateBoard();
};
