#include <iostream>
#include <chrono>
#include "Osl.h"
#include <omp.h>

int main()
{
    omp_set_num_threads(19);
    std::cout.precision(12);

    Osl::vector x = Osl::Maths::Arrays::regspace(-10, 10, 1);
    Osl::vector y(x.size());
    for (std::size_t i = 0 ; i < x.size() ; ++i)
    {
        y[i] = x[i] * x[i];
    }

    double xinterp = 1e-05;
    double yinterp, yinterpreg;

    auto start = std::chrono::high_resolution_clock::now();
//    #pragma omp parallel for
    for (std::size_t i = 0 ; i < 10000000 ; ++i)
    {
        yinterp = Osl::Maths::Interpolator::linear_interpolation(x, y, xinterp);
    }
    auto stop = std::chrono::high_resolution_clock::now();

    auto start2 = std::chrono::high_resolution_clock::now();
//    #pragma omp parallel for
    for (std::size_t i = 0 ; i < 10000000 ; ++i)
    {
        yinterpreg = Osl::Maths::Interpolator::linear_interpolation_reg(x, y, xinterp);
    }
    auto stop2 = std::chrono::high_resolution_clock::now();

//    auto start = std::chrono::high_resolution_clock::now();
//    double yinterp;
//    #pragma omp parallel for
//    for (std::size_t i = 0 ; i < 1000000000 ; ++i)
//    {
//        yinterp = Osl::Maths::Interpolator::linear_interpolation(x, y, xinterp);
//    }
//    auto stop = std::chrono::high_resolution_clock::now();

//    auto start2 = std::chrono::high_resolution_clock::now();
//    Osl::Maths::Interpolator::LinearSpline linSpline(x, y);
//    std::size_t index = linSpline.search_index_for_interpolation(xinterp);
//    double yinterp2;
//    #pragma omp parallel for
//    for (std::size_t i = 0 ; i < 1000000000 ; ++i)
//    {
//        linSpline(xinterp, index, yinterp2);
//    }
//    auto stop2 = std::chrono::high_resolution_clock::now();


    std::cout << "x = {";
    for (std::size_t i = 0 ; i < x.size() - 1 ; ++i)
    {
        std::cout << x[i] << ", ";
    }
    std::cout << x[x.size()-1] << "}" << std::endl;

    std::cout << "y = {";
    for (std::size_t i = 0 ; i < y.size() - 1 ; ++i)
    {
        std::cout << y[i] << ", ";
    }
    std::cout << y[y.size()-1] << "}" << std::endl;

//    std::cout << "x.size() = " << x.size() << std::endl;

    std::cout << "yinterp(" << xinterp << ") = " << yinterp << std::endl;
    std::cout << "elapsed time = " << std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() * 1e-6
              << " ms" << std::endl;

    std::cout << "yinterpreg(" << xinterp << ") = " << yinterpreg << std::endl;
    std::cout << "elapsed time = " << std::chrono::duration_cast<std::chrono::nanoseconds>(stop2 - start2).count() * 1e-6
              << " ms" << std::endl;

    return 0;
}
