#include <array>
#include <variant>
#include <string>

struct Tile
{
    bool fixed = false;
    int top = 0;
    int right = 0;
    int bottom = 0;
    int left = 0;
};

class Board
{
    public:
        int size;
        void setTile(int x, int y, Tile tile);
        Tile getTile(int x, int y);
        void print();
        bool isBoardValid();
        Tile& operator[](int index) { return _board[index]; }

    private:
        std::array<Tile, 36> _board;
};

Board loadBoard(std::string filename);