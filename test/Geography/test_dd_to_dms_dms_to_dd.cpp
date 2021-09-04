// ===== TESTS Osl::Geography::dd_to_dms and Osl::Geography::dms_to_dd =====
#include "Osl.h"
#include <iostream>

int main()
{
    std::cout << "It Works !" << std::endl << std::endl;

    double dd(-5.22);
    double d, m, s;
    Osl::Geography::dd_to_dms(dd, d, m, s);

    std::cout << "dd = " << dd
              << " --> (d, m, s) = (" << d << ", "
                                      << m << ", "
                                      << s << ")"
              << std::endl;

    double ddd;
    ddd = Osl::Geography::dms_to_dd(d, m, s);
//    Osl::Geography::dms_to_dd(d, m, s, ddd);
    std::cout << "(d, m, s) = (" << d << ", " << m << ", " << s
              << ") --> dd = " << ddd << std::endl;


    return 0;
}
