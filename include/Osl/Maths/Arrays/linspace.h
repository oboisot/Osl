/*! ********************************************************************
 * \file linspace.h
 * \brief Header file for Osl::Maths::Arrays::linspace functions.
 *
 * This header provides convenient functions to create linearly spaced
 * vector.
 *********************************************************************/

#ifndef OSL_MATHS_ARRAYS_LINSPACE_H
#define OSL_MATHS_ARRAYS_LINSPACE_H

#include "Osl/Globals.h"

namespace Osl { // Osl namespace

namespace  Maths { // Osl::Maths namespace

namespace  Arrays { // Osl::Maths::Arrays namespace

/*! ********************************************************************
 * \brief Generate a linearly spaced vector.
 *
 * Generate a linearly spaced vector from \em start to \em stop containing
 * \em n linearly spaced points.
 *
 * \param [in] start, stop the start and stop values of the linspaced vector.
 * \param [in] n the number of elements in the linspaced vector.
 * \returns x the linearly spaced vector.
 *********************************************************************/
inline vector linspace(const double &start, const double &stop, const std::size_t &n)
{
    double delta = (stop - start) / static_cast<double>(n - 1); // Step of linspace
    vector x(n, start); // Initialization of the resulting vector with start value
    for (std::size_t i = 1 ; i < n ; ++i)
    {
        x[i] += static_cast<double>(i) * delta;
    }
    return x;
}

/*! ********************************************************************
 * \brief Generate a linearly spaced vector.
 *
 * Generate a linearly spaced vector from \em start to \em stop containing
 * \em n linearly spaced points.
 *
 * \param [in] start, stop the start and stop values of the linspaced vector.
 * \param [in] n the number of elements in the linspaced vector.
 * \param [out] x the linearly spaced vector.
 *********************************************************************/
inline void linspace(const double &start, const double &stop, const std::size_t &n,
                     vector &x)
{
    double delta = (stop - start) / static_cast<double>(n - 1); // Step of linspace
    x.resize(n);
    for (std::size_t i = 0 ; i < n ; ++i)
    {
        x[i] = start + static_cast<double>(i) * delta;
    }
}

} // namespace Osl::Maths::Arrays

} // namespace Osl::Maths

} // namespace Osl

#endif // OSL_MATHS_ARRAYS_LINSPACE_H
