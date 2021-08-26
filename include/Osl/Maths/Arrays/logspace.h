/*! ********************************************************************
 * \file logspace.h
 * \brief Header file for Osl::Maths::Arrays::logspace functions.
 *
 * This header provides convenient functions to create logarithmically
 * spaced vector.
 *********************************************************************/

#ifndef OSL_MATHS_ARRAYS_LOGSPACE_H
#define OSL_MATHS_ARRAYS_LOGSPACE_H

#include <cmath>
#include "Osl/Globals.h"

namespace Osl { // Osl namespace

namespace  Maths { // Osl::Maths namespace

namespace  Arrays { // Osl::Maths::Arrays namespace

/*! ********************************************************************
 * \brief Generate a logarithmically spaced vector.
 *
 * Generate a logarithmically spaced vector from \em start to \em stop
 * containing \em n points in a given base.
 *
 * \param [in] start, stop the start and stop values of the logspaced vector.
 * \param [in] n the number of elements in the logspaced vector.
 * \param [in] base the logarithmic base to use, default to base 10.
 * \returns x the logarithmically spaced vector.
 *********************************************************************/
inline vector logspace(const double &start, const double &stop,
                       const std::size_t &n, const double &base=10.0)
{
    double delta = (stop - start) / static_cast<double>(n - 1); // Step of linspace
    vector x(n, std::pow(base, start)); // Initialization of the resulting vector with base^start value
    for (std::size_t i = 1 ; i < n ; ++i)
    {
        x[i] *= std::pow(base, static_cast<double>(i) * delta);
    }
    return x;
}

/*! ********************************************************************
 * \brief Generate a logarithmically spaced vector.
 *
 * Generate a logarithmically spaced vector from \em start to \em stop
 * containing \em n points in a given base.
 *
 * \param [in] start, stop the start and stop values of the logspaced vector.
 * \param [in] n the number of elements in the logspaced vector.
 * \param [out] x the logarithmically spaced vector.
 * \param [in] base the logarithmic base to use, default to base 10.
 *********************************************************************/
inline void logspace(const double &start, const double &stop, const std::size_t &n,
                     vector &x, const double &base=10.0)
{
    double delta = (stop - start) / static_cast<double>(n - 1); // Step of linspace
    x.resize(n);
    for (std::size_t i = 0 ; i < n ; ++i)
    {
        x[i] = std::pow(base, start + static_cast<double>(i) * delta);
    }
}

} // namespace Osl::Maths::Arrays

} // namespace Osl::Maths

} // namespace Osl

#endif // OSL_MATHS_ARRAYS_LOGSPACE_H
