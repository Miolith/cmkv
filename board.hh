#include <array>


struct Tile
{
    bool fixed = false;
    int top = 0;
    int right = 0;
    int bottom = 0;
    int left = 0;
};

template<std::size_t N>
class Board : std::array<Tile, N>
{
    public:
        Board() : std::array<Tile, N>() {}

        void setTile(int x, int y, Tile tile);
        Tile getTile(int x, int y);
        void print();
        bool isBoardValid();
};

// instanciate 3x3, 4x4, 5x5 and 6x6 boards
template class Board<3>;
template class Board<4>;
template class Board<5>;
template class Board<6>;