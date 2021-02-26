#include <cstdlib>
#include <iostream>
#include <algorithm>

#include <chrono>
#include <Timer.hpp>

#include <set>
#include <vector>
#include <array>

#define N 6

int main(int argc, char* argv[])
{
    using tick = std::chrono::nanoseconds;
    std::srand(std::chrono::steady_clock::now().time_since_epoch().count());

    int arr[N];

    std::set< int > SET;
    std::vector< int > VECTOR;
    std::array< int, N > ARRAY;

    for (int i = 0; i < N; ++i)
    {
        arr[i] = std::rand();
    }

    std::cout << "N = " << N << "\n";


    {
        Timer< tick > set_insert_and_sort("Insert in set");
        for (auto c : arr)
            SET.insert(c);
    }

    {
        Timer < tick > vec("Push_back and sort vector");

        for (auto c : arr)
            VECTOR.push_back(c);

        std::sort(VECTOR.begin(), VECTOR.end());

    }

    {
        Timer < tick > ar("Insert and sort array");

        for (int i = 0; i < N; ++i)
            ARRAY[i] = arr[i];

        std::sort(ARRAY.begin(), ARRAY.end());

    }

    //////////////milliseconds/////////////
    // N = 10000

    // "Insert in set" worked for 8

    // "Push_back and sort vector" worked for 2

    // "Insert and sort array" worked for 1

    //N = 100000
    // "Insert in set" worked for 73

    // "Push_back and sort vector" worked for 28

    // "Insert and sort array" worked for 16

    // N = 1000000

    // "Insert in set" worked for 956

    // "Push_back and sort vector" worked for 329

    // "Insert and sort array" worked for 204


    //////////nanoseconds////////////////
    // N = 10

    // "Insert in set" worked for 20737

    // "Push_back and sort vector" worked for 14118

    // "Insert and sort array" worked for 4753

    // N = 6

    // "Insert in set" worked for 19924

    // "Push_back and sort vector" worked for 20756

    // "Insert and sort array" worked for 28954

    // N = 5

    // "Insert in set" worked for 17076

    // "Push_back and sort vector" worked for 19546

    // "Insert and sort array" worked for 10066


    // В зависимости от сгенерированных чисел скорость вставки и сортировки меняется, 
    // особенно при небольшом количестве элементов и при измерении в наносекундах


    return 0;
}