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
        U += bot != top;
    }
    
    if (x > 0)
    {
        int left = tile.left;
        int right = b.getTile(x - 1, y).right;
        U += left != right;
    }

    return U;
}

double get_global_dist(Board& b)
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

bool random_transition(double delta_U, double T, std::uniform_real_distribution<double>& distrib, std::minstd_rand& g)
{
    double p = exp(-delta_U / T);
    double r = distrib(g);

    return r < p;
}

static unsigned long x=123456789, y=362436069, z=521288629;

unsigned long xorshf96(void) {
unsigned long t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;

   t = x;
   x = y;
   y = z;
   z = t ^ x ^ y;

  return z;
}

void solver(Board& board)
{
    int max_iter = 100000000;
    
    double T_min = pow(0.1f, board.dim);
    double T_max = pow(10.0f, board.dim);
    double T_step = (97 - board.dim)/100.0f;
    
    std::random_device rd;  
    auto g = std::minstd_rand(rd()); 
    auto distrib = std::uniform_real_distribution<double>(0.0f, 1.0f);

    double T = T_max;
    double U = get_global_dist(board);
    double U_new = 0.0f;

    int reheat = 0;
    int tile1 = 0;
    int tile2 = 0;

    while(U != 0.0f)
    {
        tile1 = board._unfixedTiles[xorshf96() % board.unfixedSize];
        tile2 = board._unfixedTiles[xorshf96() % board.unfixedSize];

        std::swap(board[tile1], board[tile2]);

        U_new = get_global_dist(board);

        reheat += U_new >= U;

        if (reheat > 100)
        {
            T += 1.0f;
            reheat = 0;
        }

        if (U_new <= U)
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
