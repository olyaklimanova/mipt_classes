#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <forward_list>
#include <deque>
#include <algorithm>
#include <chrono>
#include "Timer.hpp"

int main()
{
    std::vector<int> v;
    std::array<int, 1000000> arr;
    std::list<int> l;
    std::forward_list<int> fl;
    std::deque<int> deq;


    for (int i = 1000000, j = 0; i > 0; --i, ++j)
    {
        v.push_back(i);
        arr[j] = i;
        l.push_back(i);
        fl.push_front(1000000 - i);
        deq.push_back(i);
    }


    {
        Timer<std::chrono::microseconds> t("vector");
        std::sort(v.begin(), v.end());
    }
    {
        Timer<std::chrono::microseconds> t("array");
        std::sort(arr.begin(), arr.end());
    }
    {
        Timer<std::chrono::microseconds> t("list");
        l.sort();
    }
    {
        Timer<std::chrono::microseconds> t("forward list");
        fl.sort();
    }
    {
        Timer<std::chrono::microseconds> t("deque");
        std::sort(deq.begin(), deq.end());
    }

    //vector worked for 127826
    //array worked for 62428
    //list worked for 462275
    //forward list worked for 328592
    //deque worked for 306019

    return 0;
}
