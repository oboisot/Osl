// ===== TESTS Comparaison de recherche d'index =====
// **SPOILER ALERT** c'est la "binary search" qui l'emporte ;-)
//#include "Osl.h"
#include <iostream>
#include <chrono>
#include "Osl.h"

int main()
{
    std::cout.precision(12);

    Osl::vector lns = Osl::Maths::Arrays::linspace(2, 3, 4);
    Osl::vector lgs = Osl::Maths::Arrays::logspace(2, 3, 4, 2);

    auto tic = std::chrono::high_resolution_clock::now();
    Osl::vector lrs = Osl::Maths::Arrays::regspace(0, 1, 1e-7);
    auto toc = std::chrono::high_resolution_clock::now();

    std::cout << "lns = {";
    for (std::size_t i = 0 ; i < lns.size() - 1 ; ++i)
    {
        std::cout << lns[i] << ", ";
    }
    std::cout << lns[lns.size()-1] << "}" << std::endl;

    std::cout << "lgs = {";
    for (std::size_t i = 0 ; i < lgs.size() - 1 ; ++i)
    {
        std::cout << lgs[i] << ", ";
    }
    std::cout << lgs[lgs.size()-1] << "}" << std::endl;

//    std::cout << "lrs = {";
//    for (std::size_t i = 0 ; i < lrs.size() - 1 ; ++i)
//    {
//        std::cout << lrs[i] << ", ";
//    }
//    std::cout << lrs[lrs.size()-1] << "}" << std::endl;


    std::cout << "lrs.size() = " << lrs.size()
              << " [elapsed time = " << std::chrono::duration_cast<std::chrono::nanoseconds>(toc-tic).count() * 1e-3
              << " µs]" << std::endl;
    return 0;
}
