#include <iostream>
#include <locale>
#include <stdexcept>
#include <iomanip>

int main()
{
    try
    {
        // Setting locale 
#ifdef _MSC_VER
        std::cout.imbue(std::locale("de-ch.1252"));
#else
        std::cout.imbue(std::locale("ru_RU.UTF-8"));
#endif

        std::cin.imbue(std::locale("en_US.UTF-8"));

        // Variables
        long double money;

        // Actions

        std::cout << "Money that I need to by a helicopter: ";
        std::cin >> std::get_money(money);

        std::cout << std::showbase << std::put_money(money, false) << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}