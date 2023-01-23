#include "board.h"
#include <iostream>

Board::Board(std::size_t h, std::size_t w)
{
    height = h;
    width = w;

    board = new short*[height];
    propagation = new short*[height];
    for(std::size_t i = 0; i < height; ++i)
    {
        board[i] = new short[width];
        propagation[i] = new short[width];
    }
}

Board::~Board()
{
    for(std::size_t i = 0; i < height; ++i)
    {
        delete[] board[i];
        delete[] propagation[i];
    }
    delete[] board;
    delete[] propagation;
}

short Board::countNeighbours(std::size_t row, std::size_t column)
{
    if(row >= height || column >= width)
    {
        throw std::out_of_range("Point out of range of the board!\n");
    }

    short counter = 0;                         //    -1 0 1
    short x[] = {-1, -1, 0, 1, 1,  1,  0, -1}; // -1  7 0 1
    short y[] = { 0,  1, 1, 1, 0, -1, -1, -1}; //  0  6 X 2
                                               //  1  5 4 3
    if(row == 0)
    {
        x[0] = x[1] = x[7] = short(height - 1);
    }
    else if(row == height - 1)
    {
        x[3] = x[4] = x[5] = -short(height - 1);
    }
    
    if(column == 0)
    {
        y[5] = y[6] = y[7] = short(width - 1);
    }
    else if(column == width - 1)
    {
        y[1] = y[2] = y[3] = -short(width - 1);
    }

    for(unsigned long i = 0; i < sizeof(x) / sizeof(short); ++i)
    {
        auto r = row + x[i];
        auto c = column + y[i];
        if(board[r][c] == live)
        {
            counter++;
        }
    }

    return counter;
}

void Board::printBoard()
{
    for(std::size_t row = 0; row < height; ++row)
    {
        for(std::size_t cell = 0; cell < width; ++cell)
        {
            if(board[row][cell] == live)
            {
                std::cout << "0";
            }
            else
            {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
}

void Board::setCellLive(std::size_t row, std::size_t column)
{
    if(row < height && column < width && board)
    {
        board[row][column] = live;
    }
    else
    {
        std::cerr << "Can't set cell state to \"live\"!\n";

        return;
    }
}

void Board::switchCell(std::size_t row, std::size_t column)
{
    if(row < height && column < width && board)
    {
        board[row][column] = board[row][column] == dead ? live : dead;
    }
    else
    {
        std::cerr << "Can't switch cell state!\n";

        return;
    }
}

void Board::updateBoard() // nextGeneration
{
    for(std::size_t row = 0; row < height; ++row)
    {
        for(std::size_t cell = 0; cell < width; ++cell)
        {
            short neighbours;
            try
            {
                neighbours = countNeighbours(row, cell);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                return;
            }
            
            if(board[row][cell] == live)
            {
                if(neighbours < 2 || neighbours > 3)
                {
                    propagation[row][cell] = kill;
                }
                else
                {
                    propagation[row][cell] = save;
                }
            }
            else // dead
            {
                if(neighbours == 3)
                {
                    propagation[row][cell] = born;
                }
            }
        }
    }

    for(std::size_t row = 0; row < height; ++row)
    {
        for(std::size_t cell = 0; cell < width; ++cell)
        {
            board[row][cell] += propagation[row][cell];
            propagation[row][cell] = 0;
        }
    }
}
