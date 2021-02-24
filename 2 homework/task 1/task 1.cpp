#include <iostream>
#include <vector>
#include <iomanip>
#include <exception>
#include <stdexcept>

int main()
{
    std::vector<int> v = { 1,2,3,4,5 };

    std::cout << "Vector's capacity is : " << v.capacity() << " with " << v.size() << " items in it\n";

    for (int i = v.size(); i < v.capacity(); ++i)
    {
        v.push_back(i);
        std::cout << "Vector's capacity is : " << v.capacity() << " with " << v.size() << " items in it\n";
    }

    v.push_back(v.size());
    std::cout << "Vector's capacity is : " << v.capacity() << " with " << v.size() << " items in it\n";


    //Vector's capacity is : 5 with 5 items in it
    //Vector's capacity is : 10 with 6 items in it
    //Ёмкость увеличилась в 2 раза

    std::vector<int> v1;
    v1.reserve(12);

    for (int i = v1.size(); i < v1.capacity(); ++i)
    {
        v1.push_back(i);
        std::cout << "Vector's capacity is : " << v1.capacity() << " with " << v1.size() << " items in it\n";
    }

    v1.push_back(v1.size());
    std::cout << "Vector's capacity is : " << v1.capacity() << " with " << v1.size() << " items in it\n";

    //....
    //Vector's capacity is : 12 with 12 items in it
    //Vector's capacity is : 24 with 13 items in it
    //Ёмкость увеличилась в 2 раза

    try
    {
        std::vector<int> w(1000000, 0);
        w.push_back(1);

        std::cout << "The capacity and size of vector are equal: \n capacity - "
            << w.capacity() << "\n size - " << w.size() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }

    return 0;
}