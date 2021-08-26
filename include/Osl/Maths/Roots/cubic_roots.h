/*! ********************************************************************
 * \file cubic_roots.h
 * \brief Header file for Osl::Maths::Roots::cubic_roots functions.
 *
 * This header provides analytical functions for roots finding from
 * cubic polynomials.
 *********************************************************************/

#ifndef OSL_MATHS_ROOTS_CUBIC_ROOTS_H
#define OSL_MATHS_ROOTS_CUBIC_ROOTS_H

#include "Osl/Globals.h"
#include "Osl/Maths/Comparison/true_zero.h"

namespace Osl { // Osl namespace

namespace  Maths { // Osl::Maths namespace

namespace  Roots { // Osl::Maths::Roots namespace

/*! ********************************************************************
 * \brief Function to find the principal cubic root of a complex number.
 *
 * This function finds the principal cubic root of a complex number, the
 * algorithm is inpired from <a
 * href="https://stackoverflow.com/questions/40439739/
 * cube-root-of-a-number-c?answertab=active#tab-top"
 * target=_blank>Stackoverflow</a> post.
 *
 * \param [in] z the complex number.
 * \return The principal cubic root of z.
 *********************************************************************/
inline complex cbrt(const complex &z)
{
    if (z.real() < 0.0)
        return -std::pow(-z, Constants::m_1_3);
    return std::pow(z, Constants::m_1_3);
}

/*! ********************************************************************
 * \brief Function to find roots of a third order (cubic) polynomial
 *        with complex coefficients.
 *
 * This function finds the roots of a third order polynomial of the form:
 *
 * \f[
 *      f(x)=ax^3+bx^2+cx+d
 * \f]
 *
 * with \f$a\f$, \f$b\f$, \f$c\f$ and \f$d\f$ complex coefficients using
 * <a href="https://proofwiki.org/wiki/Cardano's_Formula"
 * target=_blank>Cardano's formula</a>.
 *
 * \param [in] a, b, c, d the polynomial coefficients starting from its higher
 *        order.
 * \param [out] x1, x2, x3 the three roots of the quadratic polynomial.
 * \note The returned first root x1 is ensured to be real.
 *********************************************************************/
inline void cubic_roots(const complex &a, const complex &b, const complex &c, const complex &d,
                        complex &x1, complex &x2, complex &x3)
{
    if (std::norm(a) > 0.0) // if |a|^2 > 0 => a != 0
    {
        complex a2 = a * a, b2 = b * b, ac = a * c; // Precompute reusable values
        complex Q = (3.0 * ac - b2) / (9.0 * a2),
                R = (9.0 * ac * b - 27.0 * a2 * d - 2.0 * b2 * b) / (54.0 * a2 * a);
        complex sqrtD = std::sqrt(Q * Q * Q + R * R);
        complex S = cbrt(R + sqrtD),
                U = cbrt(R - sqrtD);
        complex s0 = -b / (3.0 * a),
                s1 = -0.5 * (S + U),
                s2 = complex(0, 0.5 * Constants::m_sqrt_3) * (S - U); // i*sqrt(3)/2 * (S - U)
        // Cubic roots
        x1 = Comparison::true_zero(S + U + s0); // Should be the real solution
        x2 = Comparison::true_zero(s1 + s2 + s0);
        x3 = Comparison::true_zero(s1 - s2 + s0);
    }
    else
        throw std::invalid_argument("Osl::Maths::Roots::cubic_roots(): "
                                    "Coefficient 'a' can't be zero.");
}

/*! ********************************************************************
 * \brief Function to find roots of a third order (cubic) polynomial
 *        with real coefficients.
 *
 * This function finds the roots of a third order polynomial of the form:
 *
 * \f[
 *      f(x)=ax^3+bx^2+cx+d
 * \f]
 *
 * with \f$a\f$, \f$b\f$, \f$c\f$ and \f$d\f$ real coefficients using
 * <a href="https://proofwiki.org/wiki/Cardano's_Formula"
 * target=_blank>Cardano's formula</a>.
 *
 * \param [in] a, b, c, d the polynomial coefficients starting from its higher
 *        order.
 * \param [out] x1, x2, x3 the three roots of the quadratic polynomial.
 * \note This function simply casts real coefficients into complex
 *       and uses the cubicRoots(const complex &a, const complex &b, const complex &c, const complex &d, complex &x1, complex &x2, complex &x3)
 *       function.
 *********************************************************************/
inline void cubic_roots(const double &a, const double &b, const double &c, const double &d,
                        complex &x1, complex &x2, complex &x3)
{
    cubic_roots(complex(a, 0.0), complex(b, 0.0), complex(c, 0.0), complex(d, 0.0),
                x1, x2, x3);
}


} // namespace Osl::Maths::Roots

} // namespace Osl::Maths

} // namespace Osl

#endif // OSL_MATHS_ROOTS_CUBIC_ROOTS_H
