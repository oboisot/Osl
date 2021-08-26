/*! ********************************************************************
 * \file regspace.h
 * \brief Header file for Osl::Maths::Arrays::regspace functions.
 *
 * This header provides convenient functions to create regularly
 * spaced vector.
 *********************************************************************/

#ifndef OSL_MATHS_ARRAYS_REGSPACE_H
#define OSL_MATHS_ARRAYS_REGSPACE_H

#include "Osl/Globals.h"

namespace Osl { // Osl namespace

namespace  Maths { // Osl::Maths namespace

namespace  Arrays { // Osl::Maths::Arrays namespace

inline vector regspace(const double &start, const double &stop, const double &delta)
{
    std::size_t n = static_cast<std::size_t>((stop - start) / delta) + 1;
    vector x(n, start); // Initialization of the resulting vector with start value
    for (std::size_t i = 1 ; i < n ; ++i)
    {
        x[i] += static_cast<double>(i) * delta;
    }
    return x;
}

inline void regspace(const double &start, const double &stop, const double &delta,
                     vector &x)
{
    std::size_t n = static_cast<std::size_t>((stop - start) / delta) + 1;
    x.resize(n); // Initialization of the resulting vector with start value
    for (std::size_t i = 0 ; i < n ; ++i)
    {
        x[i] = start + static_cast<double>(i) * delta;
    }
}

//inline vector regspace(const double &start, const double &delta, const std::size_t &n)
//{
//    vector x(n, start); // Initialization of the resulting vector with start value
//    for (std::size_t i = 1 ; i < n ; ++i)
//    {
//        x[i] += static_cast<double>(i) * delta;
//    }
//    return x;
//}

} // namespace Osl::Maths::Arrays

} // namespace Osl::Maths

} // namespace Osl

#endif // OSL_MATHS_ARRAYS_REGSPACE_H
