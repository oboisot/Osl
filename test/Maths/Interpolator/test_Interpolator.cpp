#include "Osl.h"
#include <iostream>
#include <chrono>

int main()
{
    std::cout << "It Works !" << std::endl << std::endl;

    using namespace Osl;
    using namespace Osl::Maths;

    vector  x(100, -1.0);
    for (vector::iterator it = x.begin() + 1 ; it != x.end() ; ++it)
    {
        *it = *(it-1) + 0.1;
    }

    Interpolator::CubicSpline f(x, x, Interpolator::CubicSplineBoundary::natural);
    double v;

    std::size_t n = 0;
    auto t1 = std::chrono::high_resolution_clock::now();
    for (double xi = x.front() ; xi <= x.back() ; xi += 0.00001)
    {
        f(xi, v);
        n++;
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "CubicSpline execution time = "
              << std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count()
              << " ms [" << n << " iterations]" << std::endl;

//    std::cout << std::endl;

    Interpolator::Sinc fsc(x, x);
    n = 0;
    t1 = std::chrono::high_resolution_clock::now();
    for (double xi = x.front() ; xi <= x.back() ; xi += 0.00001)
    {
        fsc(xi, v);
        n++;
    }
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Sinc execution time = "
              << std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count()
              << " ms [" << n << " iterations]" << std::endl;

    return 0;
}
