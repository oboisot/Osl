/*! ********************************************************************
 * \file sinc.h
 * \brief Header file for Osl::Maths::Functions::sinc functions.
 *
 * This header provides an implementation of the normalized sinus
 * cardinal function.
 *********************************************************************/

#ifndef OSL_MATHS_FUNCTIONS_SINC_H
#define OSL_MATHS_FUNCTIONS_SINC_H

#include <cmath>
#include "Osl/Constants.h"

namespace Osl { // Osl namespace

namespace  Maths { // Osl::Maths namespace

namespace  Functions { // Osl::Maths::Functions namespace

/*! ********************************************************************
 * \brief Compute the normalized sinus cardinal function.
 *
 * Compute the normalized sinus cardinal function:
 *
 * \f[
 *     \mathrm{sinc}(x)=\dfrac{\sin(\pi x)}{\pi x}
 * \f]
 *
 * \param [in] x, the argument of the sinc function.
 * \returns the value of sinc in x.
 *********************************************************************/
inline double sinc(const double &x)
{
    double arg = Constants::m_pi * x;
    if (std::abs(x) < 1e-6)
        return 1.0 - Constants::m_1_6 * arg * arg;
    return std::sin(arg) / arg;
}

/*! ********************************************************************
 * \brief Compute the normalized sinus cardinal function.
 *
 * Compute the normalized sinus cardinal function:
 *
 * \f[
 *     \mathrm{sinc}(x)=\dfrac{\sin(\pi x)}{\pi x}
 * \f]
 *
 * \param [in] x, the argument of the sinc function.
 * \param [out] y, the value of sinc in x.
 *********************************************************************/
inline void sinc(const double &x, double &y)
{
    double arg = Constants::m_pi * x;
    if (std::abs(x) < 1e-6)
    {
        y = 1.0 - Constants::m_1_6 * arg * arg;
    }
    else
    {
        y = std::sin(arg) / arg;
    }
}


} // namespace Osl::Maths::Functions

} // namespace Osl::Maths

} // namespace Osl

#endif // OSL_MATHS_FUNCTIONS_SINC_H
