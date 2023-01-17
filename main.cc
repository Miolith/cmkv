#include <iostream>

#include "board.hh"
#include "solver.hh"
#include "tests.hh"

int main(int argc, char** argv)
{
    if (getenv("TESTSUITE"))
    {
        testSuite(solver);
        return 0;
    }

    if (argc != 3)
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