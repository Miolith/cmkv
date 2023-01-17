#include "board.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void Board::setTile(int x, int y, Tile tile)
{
    _board.at(x + y * size) = tile;
}

Tile Board::getTile(int x, int y)
{
    return _board.at(x + y * size);
}

void Board::print()
{
    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            std::cout << this->getTile(x, y).top << " ";
        }
        std::cout << std::endl;
    }
}

bool Board::isBoardValid()
{
    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            Tile tile = this->getTile(x, y);
            if (x > 0)
            {
                Tile leftTile = this->getTile(x - 1, y);
                if (leftTile.right != tile.left)
                {
                    return false;
                }
            }
            if (y > 0)
            {
                Tile topTile = this->getTile(x, y - 1);
                if (topTile.bottom != tile.top)
                {
                    return false;
                }
            }
        }
    }
    return true;
}


Board loadBoard(std::string filename)
{
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line);
    
    Board board;
    int size = 0;
    while ( getline(file, line) )
    {
        std::istringstream iss(line);
        char top, right, bottom, left;
        if (!(iss >> top >> right >> bottom >> left))
        {
            throw "Invalid board file";
        }
        Tile tile;
        tile.top = top - '0';
        tile.right = right - '0';
        tile.bottom = bottom - '0';
        tile.left = left - '0';

        char dump, fixed;
        if ((iss >> dump >> fixed))
        { 
            if (fixed == '@')
            {
                board[size].fixed = true;
            }
        }
        board[size] = tile;
        size++;
    }
    board.size = size;
    return board;
}