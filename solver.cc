#include <random>
#include <cmath>
#include <algorithm>

#include "board.hh"
#include "solver.hh"

// Tetravex solver using simulated annealing and metropolis algorithm

double get_distance(Board& b, int i, int j)
{
    double U = 0;
    
    if (i - 1 > 0)
    {
        int top = b.getTile(i, j).top;
        int bot = b.getTile(i-1, j).bottom;
        U += bot == top ? 0 : 1;
    }
    
    if (i + 1 < b.dim)
    {
        int bot = b.getTile(i, j).bottom;
        int top = b.getTile(i+1, j).top;
        U += bot == top ? 0 : 1;
    }
    
    if (j - 1 > 0)
    {
        int left = b.getTile(i, j).left;
        int right = b.getTile(i, j-1).right;
        U += left == right ? 0 : 1;
    }

    
    if (j + 1 < b.dim)
    {
        int right = b.getTile(i, j).right;
        int left = b.getTile(i, j+1).left;
        U += right == left ? 0 : 1;
    }

    return U;
}

double get_probability(Board& b)
{
    double U = 0.0f;

    for (int i = 0; i < b.dim; i++)
    {
        for (int j = 0; j < b.dim; j++)
        {
            U += get_distance(b, i, j);
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
    int max_iter = 1000000;
    double T_min = .0f;
    double T_max = 10000.0f;

    std::random_device rd;  
	auto g = std::mt19937(rd()); 
	auto distrib = std::uniform_real_distribution<double>(0.0, 1.0);

    double T = T_max;
    double T_step = 0.99;

    double U = get_probability(board);
    double U_new = 0.0f;

    while(U != 0.0f)
    {
        int tile1 = rand() % board.size;
        int tile2 = rand() % board.size;

        while (tile1 == tile2 || board[tile2].fixed || board[tile1].fixed)
        {
            tile1 = rand() % board.size;
            tile2 = rand() % board.size;
        }

        std::swap(board[tile1], board[tile2]);

        U_new = get_probability(board);

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
