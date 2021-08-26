/*! ********************************************************************
 * \file true_zero.h
 * \brief Header file for the Osl::Maths::Comparison::true_zero functions
 *********************************************************************/

#ifndef OSL_MATHS_COMPARISON_TRUE_ZERO_H
#define OSL_MATHS_COMPARISON_TRUE_ZERO_H

#include "Osl/Globals.h"
#include "Osl/Constants.h"

namespace Osl { // Osl namespace

namespace  Maths { // Osl::Maths namespace

namespace Comparison { // Osl::Maths::Comparison namespace

// ===== TRUE ZERO =====
/*! ********************************************************************
 * \brief Convenient function to replace an almost zero real value with
 *        a true zero.
 *
 * This function compares the given real number \f$x\f$ to \f$0\f$
 * against the machine resolution for double \f$res\f$ and returns
 * a true zero when the inequality holds.
 *
 * \param [in] x the number to be compared to zero.
 * \returns 0 if x is almost zero, x otherwise.
 * \sa almost_zero(double x)
 * \sa true_zero(complex z)
 *********************************************************************/
inline double true_zero(double x)
{
    if (std::abs(x) <= Constants::n_machine_res) // almostZero
        return 0.0;
    return x;
}

/*! ********************************************************************
 * \brief Convenient function to replace an almost zero complex value with
 *        a true complex zero.
 *
 * This function compares the given complex number \f$z\f$ to \f$0\f$
 * against the machine resolution for double \f$res\f$ and returns
 * a true complex zero when the inequality holds.
 *
 * \param [in] z the number to be compared to zero.
 * \returns 0 if z is almost zero, z otherwise.
 * \sa almost_zero(complex z)
 * \sa true_zero(double x)
 *********************************************************************/
inline complex true_zero(complex z)
{
    if (std::abs(z.real()) <= Constants::n_machine_res) // almostZero
        z.real(0.0);
    if (std::abs(z.imag()) <= Constants::n_machine_res) // almostZero
        z.imag(0.0);
    return z;
}

} // namespace Osl::Maths::Comparison

} // namespace Osl::Maths

} // namespace Osl

#endif // OSL_MATHS_COMPARISON_TRUE_ZERO_H
