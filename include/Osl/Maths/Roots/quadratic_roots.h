/*! ********************************************************************
 * \file quadratic_roots.h
 * \brief Header file for Osl::Maths::Roots::quadratic_roots functions.
 *
 * This header provides analytical functions for roots finding from
 * quadratic polynomials.
 *********************************************************************/

#ifndef OSL_MATHS_ROOTS_QUADRATIC_ROOTS_H
#define OSL_MATHS_ROOTS_QUADRATIC_ROOTS_H

#include "Osl/Globals.h"
#include "Osl/Maths/Comparison/true_zero.h"

namespace Osl { // Osl namespace

namespace  Maths { // Osl::Maths namespace

namespace  Roots { // Osl::Maths::Roots namespace

/*! ********************************************************************
 * \brief Function to find roots of a second order (quadratic) polynomial
 *        with complex coefficients.
 *
 * This function finds the roots of a second order polynomial of the form:
 *
 * \f[
 *      f(x)=ax^2+bx+c
 * \f]
 *
 * with \f$a\f$, \f$b\f$ and \f$c\f$ complex coefficients.
 *
 * \param [in] a, b, c the polynomial coefficients starting from its higher
 *        order.
 * \param [out] x1, x2 the two roots of the quadratic polynomial.
 *********************************************************************/
inline void quadratic_roots(const complex &a, const complex &b, const complex &c,
                            complex &x1, complex &x2)
{
    if (std::norm(a) > 0.0) // if |a|^2 > 0 => a != 0
    {
        complex s0 = -0.5 * b / a,
                s1 = 0.5 * std::sqrt(b * b - 4.0 * a * c) / a;
        // Quadratic roots
        x1 = Comparison::true_zero(s0 + s1);
        x2 = Comparison::true_zero(s0 - s1);
    }
    else
        throw std::invalid_argument("Osl::Maths::Roots::quadratic_roots(): "
                                    "Coefficient 'a' can't be zero.");
}

/*! ********************************************************************
 * \brief Function to find roots of a second order (quadratic) polynomial
 *        with real coefficients.
 *
 * This function finds the roots of a second order polynomial of the form:
 *
 * \f[
 *      f(x)=ax^2+bx+c
 * \f]
 *
 * with \f$a\f$, \f$b\f$ and \f$c\f$ complex coefficients.
 *
 * \param [in] a, b, c the polynomial coefficients starting from its higher
 *        order.
 * \param [out] x1, x2 the two roots of the quadratic polynomial.
 * \note This function simply casts real coefficients into complex
 *       and uses the quadraticRoots(const complex &a, const complex &b, const complex &c, complex &x1, complex &x2)
 *       function.
 *********************************************************************/
inline void quadratic_roots(const double &a, const double &b, const double &c,
                            complex &x1, complex &x2)
{
    quadratic_roots(complex(a, 0.0), complex(b, 0.0), complex(c, 0.0), x1, x2);
}

} // namespace Osl::Maths::Roots

} // namespace Osl::Maths

} // namespace Osl

#endif // OSL_MATHS_ROOTS_QUADRATIC_ROOTS_H
