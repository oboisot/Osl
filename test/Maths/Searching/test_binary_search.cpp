// ===== TESTS Comparaison de recherche d'index =====
// **SPOILER ALERT** c'est la "binary search" qui l'emporte ;-)
//#include "Osl.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>

std::size_t search_index( std::vector<double> &x, double x0)
{
    std::size_t size = x.size(),
                index = 0;
    if (x0 >= x.back()) // x0 >= xmax we take the n-1 index
        index = size - 2;
    else
        while (x0 >= x[index+1])
            ++index;
    return index; // if none of the if-else condition are found, index=0 is returned
}

std::size_t search_index2( std::vector<double> &x, double x0)
{
    std::size_t size = x.size(),
                index;
    if (x0 >= x.back())
    {
        index = size - 2;
    }
    else if (x0 <= x.front())
    {
        index = 0;
    }
    else
    {
        // Search index of coefficients for interpolation
        index = x.rend() -
                std::find_if(x.rbegin(), x.rend(),
                             [&x0](double xx){return xx <= x0;}) - 1;
    }
    return index;
}

std::size_t binary_search_greater_equal( std::vector<double> &x, const double &x0 )
{
    if (x0 >= x.back())
        return x.size() - 2;
    if (x0 <= x.front())
        return 0;
    std::size_t left = 0, right = x.size() - 1, mid;
    while (right - left > 1)
    {
        mid = (left + right) / 2;
        if (x0 >= x[mid])
            left = mid;
        else
            right = mid;
    }
    return left; // We want the value <= x0
}


int main()
{
    std::cout.precision(10);
    //std::vector<double> x{1, 2, 5, 8, 10.1, 15};
    std::vector<double> x(100000);
    std::iota(x.begin(), x.end(), -50000);

    double x0 = 15;
//    double x0 = -9999;

    auto tic = std::chrono::high_resolution_clock::now();
    std::size_t index = search_index(x, x0);
    auto toc = std::chrono::high_resolution_clock::now();


    std::cout << x0 << " >= " << x[index] << " found at index : " << index << std::endl;
    std::cout << "elapsed time : " << std::chrono::duration_cast<std::chrono::nanoseconds>(toc - tic).count() << "ns\n";

    tic = std::chrono::high_resolution_clock::now();
    std::size_t index2 = search_index2(x, x0);
    toc = std::chrono::high_resolution_clock::now();

    std::cout << x0 << " >= " << x[index2] << " found at index : " << index2 << std::endl;
    std::cout << "elapsed time : " << std::chrono::duration_cast<std::chrono::nanoseconds>(toc - tic).count() << "ns\n";

    tic = std::chrono::high_resolution_clock::now();
    std::size_t index3 = binary_search_greater_equal(x, x0);
    toc = std::chrono::high_resolution_clock::now();

    std::cout << x0 << " >= " << x[index3] << " found at index : " << index3 << std::endl;
    std::cout << "elapsed time : " << std::chrono::duration_cast<std::chrono::nanoseconds>(toc - tic).count() << "ns\n";

    return 0;
}
