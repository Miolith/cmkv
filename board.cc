#include "board.hh"
#include <iostream>

template<std::size_t N>
void Board<N>::setTile(int x, int y, Tile tile)
{
    this->at(x + y * N) = tile;
}

template<std::size_t N>
Tile Board<N>::getTile(int x, int y)
{
    return this->at(x + y * N);
}

template<std::size_t N>
void Board<N>::print()
{
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            std::cout << this->getTile(x, y).top << " ";
        }
        std::cout << std::endl;
    }
}

template<std::size_t N>
bool Board<N>::isBoardValid()
{
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
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