#include <iostream>
#include <fstream>
#include <random>
#include <string>

int main(int argc, const char* argv[])
{
    //  Open file
    std::fstream file("test.txt", std::ios::in | std::ios::out | std::ios::trunc);

    //  Fill file
    int length = 7;

    std::default_random_engine gen(42);
    std::uniform_int_distribution< int > distr(97, 122);

    for (int i = 0; i < 20; ++i)
    {
        for (int j = 0; j < length; ++j)
            file << static_cast<char> (distr(gen));
        file << std::endl;
    }

    //  Find a line
    int line;
    std::string str;

    std::cout << "Choose the line: ";
    std::cin >> line;

    file.seekg(0);
    std::getline(file, str);

    file.seekg((line - 1) * (str.size() + 2), std::ios::beg);

    std::getline(file, str);

    std::cout << str << std::endl;

    return 0;
}