#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <algorithm>


int main()
{
    std::regex date_pattern("[^\\d](\\d{4}:([01]\\d):([0123]\\d))[^\\d]");
    std::regex time_pattern("[^\\d](([012]\\d):([012345]\\d):([012345]\\d))[^\\d]");

    std::cout << "Able to distinguish these formats:\n" <<
        "Date: YYYY:MM:DD\n" <<
        "Time: HH:MM:SS" << std::endl;

    std::string str(std::istreambuf_iterator< char >(std::cin), std::istreambuf_iterator< char >());

    std::sregex_token_iterator time_it(str.begin(), str.end(), time_pattern, 1);
    std::sregex_token_iterator date_it(str.begin(), str.end(), date_pattern, 1);

    std::sregex_token_iterator end_it;
    for (; time_it != end_it; ++time_it)
    {
        std::cout << *time_it << std::endl;
    }

    for (; date_it != end_it; ++date_it)
        std::cout << *date_it << std::endl;

    return 0;
}