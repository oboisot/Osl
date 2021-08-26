/*! ********************************************************************
 * \file quartic_roots.h
 * \brief Header file for Osl::Maths::Roots::quartic_roots functions.
 *
 * This header provides analytical functions for roots finding from
 * quartic polynomials.
 *********************************************************************/

#ifndef OSL_MATHS_QUARTIC_ROOTS_H
#define OSL_MATHS_QUARTIC_ROOTS_H

#include "Osl/Globals.h"
#include "Osl/Maths/Comparison/almost_zero.h"
#include "Osl/Maths/Comparison/true_zero.h"
#include "Osl/Maths/Roots/quadratic_roots.h"
#include "Osl/Maths/Roots/cubic_roots.h"

namespace Osl { // Osl namespace

namespace  Maths { // Osl::Maths namespace

namespace  Roots { // Osl::Maths::Roots namespace

/*! ********************************************************************
 * \brief Function to find roots of a fourth order (quartic) polynomial
 *        with complex coefficients.
 *
 * This function finds the roots of a fourth order polynomial of the form:
 *
 * \f[
 *      f(x)=ax^4+bx^3+cx^2+dx+e
 * \f]
 *
 * with \f$a\f$, \f$b\f$, \f$c\f$, \f$d\f$ and \f$e\f$ complex coefficients using
 * <a href="http://www.1728.org/quartic2.htm" target=_blank>Ferrari's solution</a>.
 *
 * \param [in] a, b, c, d, e the polynomial coefficients starting from its higher
 *        order.
 * \param [out] x1, x2, x3, x4 the four roots of the quartic polynomial.
 *********************************************************************/
inline void quartic_roots(const complex &a, const complex &b, const complex &c,
                          const complex &d, const complex &e,
                          complex &x1, complex &x2, complex &x3, complex &x4)
{
    // Case of a biquadratic form
    if ((std::norm(b) == 0.0) && (std::norm(d) == 0.0)) // Case b = d = 0
    {
        // Solving of the quadratic roots
        complex zp, zm;
        quadratic_roots(a, c, e, zp, zm);
        // Finding the quartic roots
        complex sqrtzp = Comparison::true_zero(std::sqrt(zp)),
                sqrtzm = Comparison::true_zero(std::sqrt(zm));
        x1 = sqrtzm;
        x2 = -sqrtzm;
        x3 = sqrtzp;
        x4 = -sqrtzp;
    }
    else
    {
        if (std::norm(a) > 0.0) // a != 0
        {
            // Note: 3/8 = 0.375, 1/4 = 0.25, 1/8 = 0.125, 1/16 = 0.0625, 1/64 = 0.015625, 3/256 = 0.01171875
            // Conversion to a depressed quartic
            complex inva = 1.0 / a;
            complex nb = b * inva, nc = c * inva, nd = d * inva, ne = e * inva;
            complex nb2 = nb * nb; // Precompute reusable values
            complex f = nc - 0.375 * nb2,
                    g = nd + 0.125 * nb2 * nb - 0.5 * nb * nc,
                    h = ne - 0.01171875 * nb2 * nb2 + 0.0625 * nb2 * nc - 0.25 * nb * nd;
            // Computation of the roots of the cubic resolvent
            complex r1, r2, r3;
            cubic_roots(1.0, 0.5 * f, 0.0625 * (f * f - 4.0 * h), -0.015625 * g * g, r1, r2, r3);
            // We take the two complex roots (if complex), that is r2 and r3. If one of them
            // is zero, we take r1
            complex p, q;
            if (!Comparison::almost_zero(r2))
            {
                p = std::sqrt(r2);
                if (!Comparison::almost_zero(r3))
                    q = std::sqrt(r3); // p = sqrt(r2), q = sqrt(r3)
                else
                    q = std::sqrt(r1); // p = sqrt(r2), q = sqrt(r1)
            }
            else // p = sqrt(r1), q = sqrt(r3)
            {
                p = std::sqrt(r1);
                q = std::sqrt(r3);
            }
            //
            complex r = -0.125 * g / (p * q),
                    s = 0.25 * nb;
            x1 = Comparison::true_zero(p + q + r - s);
            x2 = Comparison::true_zero(p - q - r - s);
            x3 = Comparison::true_zero(-p + q - r - s);
            x4 = Comparison::true_zero(-p - q + r - s);
        }
        else
            throw std::invalid_argument("Osl::Maths::Roots::quartic_roots(): "
                                        "Coefficient 'a' can't be zero.");
    }
}

/*! ********************************************************************
 * \brief Function to find roots of a fourth order (quartic) polynomial
 *        with real coefficients.
 *
 * This function finds the roots of a fourth order polynomial of the form:
 *
 * \f[
 *      f(x)=ax^4+bx^3+cx^2+dx+e
 * \f]
 *
 * with \f$a\f$, \f$b\f$, \f$c\f$, \f$d\f$ and \f$e\f$ complex coefficients using
 * <a href="http://www.1728.org/quartic2.htm" target=_blank>Ferrari's solution</a>.
 *
 * \param [in] a, b, c, d, e the polynomial coefficients starting from its higher
 *        order.
 * \param [out] x1, x2, x3, x4 the four roots of the quartic polynomial.
 * \note This function simply casts real coefficients into complex
 *       and uses the quarticRoots(const complex &a, const complex &b, const complex &c, const complex &d, const complex &e, complex &x1, complex &x2, complex &x3, complex &x4)
 *       function.
 *********************************************************************/
inline void quartic_roots(const double &a, const double &b, const double &c,
                          const double &d, const double &e,
                          complex &x1, complex &x2, complex &x3, complex &x4)
{
    quartic_roots(complex(a, 0.0), complex(b, 0.0), complex(c, 0.0),
                  complex(d, 0.0), complex(e, 0.0), x1, x2, x3, x4);
}

} // namespace Osl::Maths::Roots

} // namespace Osl::Maths

} // namespace Osl

#endif // OSL_MATHS_QUARTIC_ROOTS_H
