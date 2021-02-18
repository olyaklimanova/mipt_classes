#include <iostream>
#include <vector>
#include <iomanip>

int main()
{
    std::cout << "\n\n 1." << std::endl;
    std::vector<int> v;

    std::cout << "Vector has " << v.size() << " elements, and his capacity is "
        << v.capacity() << std::endl;

    for (int i = 1; i <= 5; ++i)
    {
        v.push_back(i);
    }

    std::cout << "Vector has " << v.size() << " elements, and his capacity is "
        << v.capacity() << std::endl;

    std::size_t begin_capacity = v.capacity();

    for (int i = ++v.back(); i <= v.capacity(); ++i)
    {
        v.push_back(i);
    }

    std::cout << "The capacity and size of vector are equal: \n capacity - "
        << v.capacity() << "\n size - " << v.size() << std::endl;

    v.push_back(v.size() + 1);

    std::cout << "After adding one more element capacity became " <<
        v.capacity() << "\nSo it has increased in " <<
        v.capacity() / begin_capacity << " times." << std::endl;

    std::cout << "\n\n 2." << std::endl;
    std::vector<int> g;
    g.reserve(6);

    std::cout << "Vector has " << g.size() << " elements, and his capacity is "
        << g.capacity() << std::endl;

    std::size_t begin_capacity_2 = g.capacity();

    for (int i = ++g.back(); i <= g.capacity(); ++i)
    {
        g.push_back(i);
    }

    std::cout << "The capacity and size of vector are equal: \n capacity - "
        << g.capacity() << "\n size - " << g.size() << std::endl;

    /*g.push_back(12);
    std::cout << "After adding one more element capacity became " <<
    g.capacity() << "\nSo it has increased in " <<
    g.capacity() / begin_capacity_2 << " times." << std::endl;*/


    //############################################################################
    // При добавлении элемента, который должен увеличить ёмкость 
    // вектора происходит ошибка "Аварийный останов (стек памяти сброшен на диск)",
    // если ёмкость вектора задана перед его заполнением командой reserve
    //############################################################################


    std::cout << "\n\n 3." << std::endl;
    std::vector<int> w;
    w.reserve(100000);

    std::cout << "Vector has " << w.size() << " elements, and his capacity is "
        << w.capacity() << std::endl;

    std::size_t begin_capacity_3 = w.capacity();

    for (int i = ++w.back(); i <= w.capacity(); ++i)
    {
        w.push_back(i);
    }

    std::cout << "The capacity and size of vector are equal: \n capacity - "
        << w.capacity() << "\n size - " << w.size() << std::endl;

    //############################################################################
    // При попытке выделить ёмкость в 100000000000 вылетает исключение
    // std::bad_alloc
    // При 100000 "Ошибка сегментирования (стек памяти сброшен на диск)"
    //############################################################################

    return 0;
}