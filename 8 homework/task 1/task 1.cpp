#include <iostream>
#include <random>
#include <future>
#include <chrono>
#include <mutex>
#include "Timer.hpp"


std::mutex mutex;

void parallel_calculate_pi(int amount, int max_size, int& good_ones);

double sequence_calculate_pi(int amount);

double calculate_pi(int amount, bool parallel);


int main(int argc, const char* argv[])
{
    int amount;
    std::cin >> amount;

    {
        Timer<std::chrono::milliseconds> parallel("Parallel");
        std::cout << "Parallel: " << calculate_pi(amount, true);
    }

    {
        Timer<std::chrono::milliseconds> seq("Sequence");
        std::cout << "Sequence: " << calculate_pi(amount, false);
    }

    return EXIT_SUCCESS;
}



void parallel_calculate_pi(int amount, int max_size, int& good_ones)
{

    if (amount <= (max_size / std::thread::hardware_concurrency()))
    {
        std::lock_guard< std::mutex > block(mutex);

        std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
        std::uniform_real_distribution< double > distribution(-1.0, 1.0);

        for (int i = 0; i < amount; ++i)
        {
            if (pow(distribution(gen), 2) + pow(distribution(gen), 2) < 1)
                ++good_ones;
        }
    }
    else
    {
        int a = amount / 2;

        std::future< void > first_half = std::async(parallel_calculate_pi, a, max_size, std::ref(good_ones));

        parallel_calculate_pi(a, max_size, std::ref(good_ones));

        first_half.wait();
    }
}

double sequence_calculate_pi(int amount)
{
    std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_real_distribution< double > distribution(-1.0, 1.0);

    int good_ones = 0;

    for (int i = 0; i < amount; ++i)
    {
        if (pow(distribution(gen), 2) + pow(distribution(gen), 2) < 1)
            ++good_ones;
    }

    return 4.0 * good_ones / amount;
}

double calculate_pi(int amount, bool parallel)
{
    double pi;
    if (parallel)
    {
        int good_ones = 0;
        parallel_calculate_pi(amount, amount, std::ref(good_ones));
        pi = 4.0 * good_ones / amount;
    }
    else
    {
        pi = sequence_calculate_pi(amount);
    }

    return pi;
}