#include <iostream>
#include <execution>
#include <algorithm>
#include <random>
#include "Timer.hpp"

int main()
{
    std::vector< int > v1(1000000, 1);
    std::vector< int > v2;


    {
        Timer< std::chrono::microseconds > std_f_e("Standart for_each");
        std::for_each(std::begin(v1), std::end(v1), [](int& value) { value += 25; });
    }
    {
        Timer< std::chrono::microseconds > par_f_e("Parallel for_each");
        std::for_each(std::execution::par, std::begin(v1), std::end(v1), [](int& value) { value -= 25; });
    }

    {
        Timer< std::chrono::microseconds > seq_p_s("Sequence partial_sum");
        std::partial_sum(std::begin(v1), std::end(v1), std::back_insert_iterator(v2));
    }
    v2.clear();
    {
        Timer< std::chrono::microseconds > par_i_s("Parallel inclusive_scan");
        std::inclusive_scan(std::execution::par, std::begin(v1), std::end(v1), std::back_insert_iterator(v2));
    }
    std::mt19937 distr;
    std::shuffle(std::begin(v2), std::end(v2), distr);


    {
        Timer< std::chrono::microseconds > seq_i_p("Sequence inner_product");
        std::inner_product(std::begin(v1), std::end(v1), std::begin(v2), 0);
    }
    {
        Timer< std::chrono::microseconds > par_t_r("Parallel transform_reduce");
        std::transform_reduce(std::begin(v1), std::end(v1), std::begin(v2), 0.0);
    }

    return 0;
}