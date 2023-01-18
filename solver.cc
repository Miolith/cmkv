#include <random>
#include <cmath>
#include <algorithm>

#include "board.hh"
#include "solver.hh"

// Tetravex solver using simulated annealing and metropolis algorithm

double get_distance(Board& b, int x, int y)
{
    double U = 0;
    auto tile = b.getTile(x, y);
    if (y > 0)
    {
        int top = tile.top;
        int bot = b.getTile(x, y - 1).bottom;
        U += bot == top ? 0 : 1;
    }
    
    if (x > 0)
    {
        int left = tile.left;
        int right = b.getTile(x - 1, y).right;
        U += left == right ? 0 : 1;
    }

    return U;
}

double get_probability(Board& b)
{
    double U = 0.0f;

    for (int x = 0; x < b.dim; x++)
    {
        for (int y = 0; y < b.dim; y++)
        {
            U += get_distance(b, x, y);
        }
    }

    return U;
}

bool random_transition(double delta_U, double T, std::uniform_real_distribution<double>& distrib, std::mt19937& g)
{
    double p = exp(-delta_U / T);
    double r = distrib(g);

    return r < p;
}

void solver(Board& board)
{
    int max_iter = 100000;
    double T_min = 0.01f;
    double T_max = board.size;

    std::random_device rd;  
	auto g = std::mt19937(rd()); 
	auto distrib = std::uniform_real_distribution<double>(0.0, 1.0);

    double T = T_max;
    double T_step = 0.99;

    double U = get_probability(board);
    double U_new = 0.0f;

    int reheat = 0;

    while(U != 0.0f)
    {
        int tile1 = 0;
        int tile2 = 0;

        while (tile1 == tile2 || board[tile2].fixed || board[tile1].fixed)
        {
            tile1 = rand() % board.size;
            tile2 = rand() % board.size;
        }

        std::swap(board[tile1], board[tile2]);

        U_new = get_probability(board);

        reheat += U_new >= U ? 1 : 0;

        if (reheat > 100)
        {
            T += 1.0f;
            reheat = 0;
        }

        if (U_new < U)
        {
            U = U_new;
        }
        else
        {
            double delta_U = U_new - U;
            if (random_transition(delta_U, T, distrib, g))
            {
                U = U_new;
            }
            else
            {
                std::swap(board[tile1], board[tile2]);
            }
        }

        T *= T_step;
        T = std::max(T, T_min);

        if (max_iter-- == 0)
            break;
    }
}
