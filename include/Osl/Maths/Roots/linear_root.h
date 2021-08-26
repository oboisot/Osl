/*! ********************************************************************
 * \file linear_root.h
 * \brief Header file for Osl::Maths::Roots::linear_root functions.
 *
 * This header provides analytical functions for roots finding from
 * linear polynomials.
 *********************************************************************/

#ifndef OSL_MATHS_ROOTS_LINEAR_ROOT_H
#define OSL_MATHS_ROOTS_LINEAR_ROOT_H

#include "Osl/Globals.h"
#include "Osl/Maths/Comparison/true_zero.h"

namespace Osl { // Osl namespace

namespace  Maths { // Osl::Maths namespace

namespace  Roots { // Osl::Maths::Roots namespace

/*! ********************************************************************
 * \brief Function to find root of a first order (linear) polynomial
 *        with complex coefficients.
 *
 * This function finds the root of a first order polynomial of the form:
 *
 * \f[
 *      f(x)=ax+b
 * \f]
 *
 * with \f$a\f$ and \f$b\f$ complex coefficients.
 *
 * \param [in] a, b the polynomial coefficients starting from its higher
 *        order.
 * \param [out] x the root of the linear polynomial.
 *********************************************************************/
inline void linear_root(const complex &a, const complex &b, complex &x)
{
    if (std::norm(a) > 0.0) // if |a|^2 > 0 => a != 0
        x = Comparison::true_zero(-b / a);
    else
        throw std::invalid_argument("Osl::Maths::Roots::linear_root(): "
                                    "Coefficient 'a' can't be zero.");
}

/*! ********************************************************************
 * \brief Function to find root of a first order (linear) polynomial
 *        with real coefficients.
 *
 * This function finds the root of a first order polynomial of the form:
 *
 * \f[
 *      f(x)=ax+b
 * \f]
 *
 * with \f$a\f$ and \f$b\f$ real coefficients.
 *
 * \param [in] a, b the polynomial coefficients starting from its higher
 *        order.
 * \param [out] x the root of the linear polynomial.
 *********************************************************************/
inline void linear_root(const double &a, const double &b, double &x)
{
    if (a != 0.0)
        x = Comparison::true_zero(-b / a);
    else
        throw std::invalid_argument("Osl::Maths::Roots::linear_root(): "
                                    "Coefficient 'a' can't be zero.");
}

} // namespace Osl::Maths::Roots

} // namespace Osl::Maths

} // namespace Osl

#endif // OSL_MATHS_ROOTS_LINEAR_ROOT_H
