/*! ********************************************************************
 * \file almost_zero.h
 * \brief Header file for the Osl::Maths::Comparison::almost_zero functions.
 *********************************************************************/

#ifndef OSL_MATHS_COMPARISON_ALMOST_ZERO_H
#define OSL_MATHS_COMPARISON_ALMOST_ZERO_H

#include "Osl/Globals.h"
#include "Osl/Constants.h"

namespace Osl { // Osl namespace

namespace  Maths { // Osl::Maths namespace

namespace Comparison { // Osl::Maths::Comparison namespace

// ===== ALMOST ZERO =====
/*! ********************************************************************
 * \brief Function to estimate when a real double precision floating points
 *        equals zero in a machine sense.
 *
 * This function compares the given number \f$x\f$ to \f$0\f$
 * against the machine resolution for double \f$res\f$:
 *
 * \f[
 *     \left\vert x\right\vert\leq res
 * \f]
 *
 * with the machine resolution defined in Osl::Constants::n_machine_res.
 * When this equality holds, the real number is considered as equal
 * to zero.
 *
 * \param [in] x the number to be compared to zero.
 * \returns true if x equals zero in a machine sense, false otherwise.
 * \sa bool almost_zero(complex z)
 *********************************************************************/
inline bool almost_zero(double x)
{
    return std::abs(x) <= Constants::n_machine_res;
}

/*! ********************************************************************
 * \brief Function to estimate when a complex double precision floating points
 *        equals zero in a machine sense.
 *
 * This function compares the given complex number \f$z\f$ real and
 * imaginary part to \f$0\f$ against the machine resolution for double
 * \f$res\f$:
 *
 * \f[
 *     \left\vert\mathcal{R}(z)\right\vert\leq res
 *     \quad\mbox{and}\quad
 *     \left\vert\mathcal{I}(z)\right\vert\leq res
 * \f]
 *
 * with the machine resolution defined in Osl::Constants::n_machine_res.
 * When this equality holds, the complex number is considered as equal
 * to zero.
 *
 * \param [in] z the number to be compared to zero.
 * \returns true if z equals zero in a machine sense, false otherwise.
 * \sa bool almost_zero(double x)
 *********************************************************************/
inline bool almost_zero(complex z)
{
    return (std::abs(z.real()) <= Constants::n_machine_res) &&
           (std::abs(z.imag()) <= Constants::n_machine_res);
}

} // namespace Osl::Maths::Comparison

} // namespace Osl::Maths

} // namespace Osl

#endif // OSL_MATHS_COMPARISON_ALMOST_ZERO_H
