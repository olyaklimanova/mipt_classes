#include <iostream>
#include <fstream>
#include <iomanip>

//  For randomizer
#include <chrono>
#include <cstdlib>

// Containers
#include <set>
#include <string>

// Hash function from boost

template < typename T >
void hash_combine(std::size_t& seed, const T& value) noexcept
{
    seed ^= std::hash < T >()(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template < typename T >
void hash_value(std::size_t& seed, const T& value) noexcept
{
    hash_combine(seed, value);
}

template < typename T, typename ... Types >
void hash_value(std::size_t& seed, const T& value, const Types & ... args) noexcept
{
    hash_combine(seed, value);
    hash_value(seed, args...);
}

template < typename ... Types >
std::size_t hash_value(const Types & ... args) noexcept
{
    std::size_t seed = 0;
    hash_value(seed, args...);
    return seed;
}

//  Randomizer for std::string
std::set< std::string > MAKE_SET_OF_RANDOM_STRINGS(std::size_t SET_SIZE, std::size_t STRING_SIZE);

int main(int argc, char* argv[])
{
    //  Amount of cells in Hash-table
    std::size_t SIZE_OF_TABLE = 64;

    if (argc == 3)
    {
        SIZE_OF_TABLE = *argv[2];
    }


    //  Open file with settings: write and delete everything in it if it isn't empty
    std::ofstream FILE_OUT(argv[1], std::ios_base::out | std::ios_base::trunc);

    //  Randomizer
    std::srand(std::chrono::steady_clock::now().time_since_epoch().count());

    //  Container and variable for counting collisions
    std::set<int> TO_COUNT_COLLISIONS;
    int collisions;

    //////  Names of columns in Data.csv file
    FILE_OUT << "Num,Hash" << "\n";
    //////

    //  i - number of an element
    int i = 0;


    //  Hash random numbers
    for (; i < 1000; ++i)
    {
        if (!TO_COUNT_COLLISIONS.insert(hash_value<int>(rand()) % SIZE_OF_TABLE).second)
            FILE_OUT << i << "," << ++collisions << '\n';
    }

    // Hash std::string using function written by myself
    for (auto c : MAKE_SET_OF_RANDOM_STRINGS(1000, 5))
    {
        ++i;
        if (!TO_COUNT_COLLISIONS.insert(hash_value<std::string>(c) % SIZE_OF_TABLE).second)
            FILE_OUT << i << "," << ++collisions << '\n';
    }


    return 0;
}


std::set< std::string > MAKE_SET_OF_RANDOM_STRINGS(std::size_t SET_SIZE, std::size_t STRING_SIZE)
{
    std::set< std::string > result;

    std::srand(std::chrono::steady_clock::now().time_since_epoch().count());

    for (int iWord = 0; iWord < SET_SIZE; ++iWord)
    {
        std::string word;
        for (int iLetter = 0; iLetter < STRING_SIZE; ++iLetter)
        {
            //  Converting random number into alphabet symbol
            word += static_cast<char>(97 + rand() % (122 - 97));
        }
        result.insert(word).second ? : --iWord;
    }

    return result;
}