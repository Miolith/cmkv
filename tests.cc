#include <iostream>
#include <filesystem>
#include <chrono>
#include <array>
#include <functional>

#include "board.hh"
#include "tests.hh"

bool testSolution(std::string filename, std::function<void(Board&)> solver)
{
    Board board = loadBoard(filename);
    solver(board);
    return board.isBoardValid();
}

bool timeTest4x4(std::function<void(Board&)> solver)
{
    std::string input_file = "./data/input/s4-01.txt";
    std::array<Board, 70> boards;
    for (int i = 0; i < 70; i++)
    {
        boards[i] = loadBoard(input_file);
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    for (auto &b : boards)
    {
        solver(b);
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    
    // check that time is less than 1 second
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    return duration.count() < 1000;
}

bool timeTest6x6(std::function<void(Board&)> solver)
{
    std::string input_file = "./data/input/s6-01.txt";
    std::array<Board, 10> boards;
    for (int i = 0; i < 10; i++)
    {
        boards[i] = loadBoard(input_file);
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    for (auto &b : boards)
    {
        solver(b);
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    
    // check that time is less than 30 seconds
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    return duration.count() < 1000 * 30;
}

void testSuite(std::function<void(Board&)> solver)
{
    std::cout << "Running tests..." << std::endl;

    int passedTests = 0;
    int totalTests = 2;

    std::string path = "./data/input";
    for (const auto & entry : std::filesystem::directory_iterator(path))
    {
        totalTests++;
        std::string filename = entry.path();
        std::cout << "Testing " << filename << "... ";
        if (testSolution(filename, solver))
        {
            std::cout << "OK" << std::endl;
            passedTests++;
        }
        else
        {
            std::cout << "FAIL" << std::endl;
        }
    }

    std::cout << "Testing 4x4 time... ";
    if (timeTest4x4(solver))
    {
        std::cout << "OK" << std::endl;
        passedTests++;
    }
    else
    {
        std::cout << "FAIL" << std::endl;
    }

    std::cout << "Testing 6x6 time... ";
    if (timeTest6x6(solver))
    {
        std::cout << "OK" << std::endl;
        passedTests++;
    }
    else
    {
        std::cout << "FAIL" << std::endl;
    }

    if (passedTests == totalTests)
    {
        std::cout << "All tests passed!" << std::endl;
    }
    else
    {
        std::cout << "Some tests failed!" << std::endl;
    }
    
    std::cout << "Passed " << passedTests << " out of " << totalTests << " tests." << std::endl;
}