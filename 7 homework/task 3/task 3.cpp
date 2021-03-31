#include <iostream>
#include <future>
#include <thread>
#include <algorithm>
#include <numeric>
#include <vector>
#include "../task 1/Timer.hpp"

template< typename Iterator, typename Function >
void for_each_parallel(Iterator begin, Iterator end, Function f)
{
    auto length = std::distance(begin, end);

    std::size_t min_for_thread = 125000;

    if (length <= min_for_thread)
        std::for_each(begin, end, f);
    else
    {
        Iterator middle = std::next(begin, length / 2);

        std::future< void > first_half = std::async(for_each_parallel< Iterator, Function >, begin, middle, f);
        for_each_parallel< Iterator, Function >(middle, end, f);

        first_half.wait();
    }
}

int main()
{
    std::vector< int > v1(1000000);
    std::vector< int > v2(1000000);

    std::iota(std::begin(v1), std::end(v1), 1);
    std::iota(std::begin(v2), std::end(v2), 1);

    {
        Timer<std::chrono::microseconds> for_each("Standart for_each");
        std::for_each(std::begin(v1), std::end(v1),
            [](int& value)
            {
                value *= value;
            });
    }

    {
        Timer<std::chrono::microseconds> for_each_par("Parallel version of for_each");
        for_each_parallel(std::begin(v2), std::end(v2),
            [](int& value)
            {
                value *= value;
            });
    }

    // "Standart for_each" worked for 8762

    // "Parallel version of for_each" worked for 4732


    return 0;
}