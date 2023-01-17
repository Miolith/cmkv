#include "board.hh"
#include <iostream>

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cout << "Usage: " << argv[0] << " <board file> <output file>" << std::endl;
        return 1;
    }

    try
    {
        Board board = loadBoard(argv[1]);
        board.dump(std::cout);
    }
    catch (std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}