#include <iostream>
#include <fstream>
#include <regex>
#include <string>


int main()
{
    std::ofstream file_output("output.txt", std::ios::trunc);
    std::regex mail_pattern("([[:alnum:][:punct:]]*)@([^-][[:alnum:].-]*[^-])");
    std::regex sep_pattern("[ \t\n]*[),:\";()][ \t\n]*");

    std::smatch m;
    std::string str(std::istreambuf_iterator< char >(std::cin), std::istreambuf_iterator< char >());

    std::sregex_token_iterator it(std::begin(str), std::end(str), sep_pattern, -1);
    std::sregex_token_iterator end;
    for (; it != end; ++it)
    {
        std::string tmp(it->str());
        std::sregex_token_iterator ptr(std::begin(tmp), std::end(tmp), mail_pattern, 2);
        for (; ptr != end; ++ptr)
        {
            file_output << "domain: " << *ptr << std::endl;
        }
    }

    return 0;
}