#include <iostream>
#include <random>
#include <future>
#include <chrono>
#include "Timer.hpp"

double parallel_calculate_pi(int amount, int max_size);

double sequence_calculate_pi(int amount);

double calculate_pi(int amount, bool parallel);


int main(int argc, const char* argv[])
{
    int amount;
    std::cin >> amount;

    {
        Timer<std::chrono::milliseconds> parallel("Parallel");
        std::cout << "Parallel: " << calculate_pi(amount, true) << std::endl;;
    }

    {
        Timer<std::chrono::milliseconds> seq("Sequence");
        std::cout << "Sequence: " << sequence_calculate_pi(amount) << std::endl;
    }

    return EXIT_SUCCESS;
}



double parallel_calculate_pi(int amount, int max_size)
{

    if (amount <= (max_size / std::thread::hardware_concurrency()))
    {
        return sequence_calculate_pi(amount);
    }
    else
    {
        int a = amount / 2;

        std::future< double > first_half = std::async(parallel_calculate_pi, a, max_size);

        double second_half = parallel_calculate_pi(a, max_size);

        return (first_half.get() + second_half) / 2;
    }
}

double sequence_calculate_pi(int amount)
{
    std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_real_distribution distribution(-1.0, 1.0);

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
        pi = parallel_calculate_pi(amount, amount);
    }
    else
    {
        pi = sequence_calculate_pi(amount);
    }

    return pi;
}