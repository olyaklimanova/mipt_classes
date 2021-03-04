#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <random>


class prime_table
{
public:
    std::vector< int > operator()()
    {
        return table;
    }

    void generate(int upper_bound = 300)
    {
        if (table.back() < upper_bound)
        {
            for (int i = table.back(); table.back() < upper_bound; ++i)
            {
                bool prime = 1;
                for (auto c : table)
                {
                    if (!(i % c))
                    {
                        prime = 0;
                        break;
                    }
                }
                if (prime)
                    table.push_back(i);
            }
        }
    }

    bool is_prime(int value)
    {
        generate(value);
        return ((std::find(std::begin(table), std::end(table), value) != std::end(table)) ? 1 : 0);
    }

private:
    std::vector< int > table = { 2, 3 };
};


int main()
{
    // 
    auto file_out = std::make_shared< std::ofstream >("text.txt");
    std::vector< int > vec(10);

    // Fill vector with gradually increasein numbers
    std::iota(std::begin(vec), std::end(vec), 0);

    // Push back elements in vector frim stream std::cin
    std::copy(
        std::istream_iterator< int >(std::cin),
        std::istream_iterator< int >(),
        std::back_inserter(vec));


    // Make random numbers generator and distriburion for them
    std::default_random_engine gen;
    std::uniform_int_distribution<unsigned> distribution(0, vec.size() - 1);

    // Random sort using generator created above
    int i = 0;
    for (; i < gen() % (gen() / 100); ++i)
    {
        std::swap(vec[distribution(gen)], vec[distribution(gen)]);
    }

    // Sort vector to erase repeats using std::unique and vector's method erase
    std::sort(std::begin(vec), std::end(vec));
    vec.erase(std::unique(std::begin(vec), std::end(vec)), std::end(vec));

    // Count elements which are odd numbers
    *file_out << "In vec " << std::count_if(std::begin(vec), std::end(vec), [](int item) {
        return item % 2;
        }) << " odd elements" << std::endl;


    // Make an item of class that counts prime numbers
    prime_table pt;
    *file_out << "Prime numbers in vec :\n";
    std::for_each(std::begin(vec), std::end(vec), [&pt, file_out](int& item) {
        if (pt.is_prime(item))
            *file_out << item << " is prime number\n";
        });

    // Replace elements in vec by their squares
    std::transform(std::begin(vec), std::end(vec), std::begin(vec), [](int& item) {
        return pow(item, 2);
        });


    std::vector < int > vec2(10);

    // Fill vec2 with random numbers using generator
    for (auto& c : vec2)
        c = gen() % (gen() / 100);


    *file_out << "Sum of Vec2 elements: " <<
        std::accumulate(std::begin(vec2), std::end(vec2), 0)
        << std::endl;

    // Replace first 4 elements in vec2 with 1
    int j = 0;
    std::replace_if(std::begin(vec2), std::end(vec2), [&j](int& item) {j++; return j <= 4; }, 1);

    // Make all vectors one size to transform them together
    vec.resize(10);
    vec2.resize(10);

    std::vector< int > vec3;

    // Fill vec3 with substituted elements of vec and vec2
    std::transform(std::begin(vec), std::end(vec),
        std::begin(vec2), std::back_inserter(vec3), [](int lhs, int rhs) {
            return lhs - rhs;
        });

    // Replace all negative numbers in vec3 with 0
    std::replace_if(std::begin(vec3), std::end(vec3), [](int& item) {
        return item < 0;
        }, 0);

    // Erase all 0 in vec3
    vec3.erase(std::remove_if(std::begin(vec3), std::end(vec3), [](int item) {
        return item == 0;
        }), std::end(vec3));

    // Reverse vec3
    std::reverse(std::begin(vec3), std::end(vec3));

    // Fill vec3 to make it exact size
    vec3.resize(10);
    for (auto& c : vec3)
        c = gen() % (gen() / 100);

    // Finding top3 element in vec3
    std::nth_element(std::begin(vec3), std::next(std::begin(vec3), 2), std::end(vec3), [](int lhs, int rhs) {return lhs > rhs; });

    *file_out << "Top3 elements: " << (vec3[0] > vec3[1] ? vec[0] : vec3[1]) << " " <<
        (vec3[0] < vec3[1] ? vec3[0] : vec3[1]) << " " << vec3[2] << std::endl;

    // Merge vec and vec2 into vec4
    std::vector< int > vec4;
    std::merge(std::begin(vec), std::end(vec), std::begin(vec2),
        std::end(vec2), std::back_inserter(vec4));

    *file_out << "Vec : ";
    std::for_each(std::begin(vec), std::end(vec), [file_out](int& item) {
        *file_out << item << " ";
        });
    *file_out << "\nVec sorted : ";
    std::sort(std::begin(vec), std::end(vec), [](int lhs, int rhs) {return lhs < rhs; });
    std::for_each(std::begin(vec), std::end(vec), [file_out](int& item) {
        *file_out << item << " ";
        });

    *file_out << "\nVec2 : ";

    std::for_each(std::begin(vec2), std::end(vec2), [file_out](int& item) {
        *file_out << item << " ";
        });
    *file_out << "\nVec2 sorted : ";
    std::sort(std::begin(vec2), std::end(vec2), [](int lhs, int rhs) {return lhs < rhs; });
    std::for_each(std::begin(vec2), std::end(vec2), [file_out](int& item) {
        *file_out << item << " ";
        });

    *file_out << "\nVec3 : ";

    std::for_each(std::begin(vec3), std::end(vec3), [file_out](int& item) {
        *file_out << item << " ";
        });
    *file_out << "\nVec3 sorted : ";
    std::sort(std::begin(vec3), std::end(vec3), [](int lhs, int rhs) {return lhs > rhs; });

    std::for_each(std::begin(vec3), std::end(vec3), [file_out](int& item) {
        *file_out << item << " ";
        });

    *file_out << "\nVec4 : ";

    std::for_each(std::begin(vec4), std::end(vec4), [file_out](int& item) {
        *file_out << item << " ";
        });

    auto pair = std::equal_range(std::begin(vec4), std::end(vec4), 1);
    *file_out << "\n \"1\" are from " << *pair.first << " to " << *pair.second << std::endl;

    return 0;
}