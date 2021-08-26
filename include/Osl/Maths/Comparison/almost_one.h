/*! ********************************************************************
 * \file almost_one.h
 * \brief Header file for the Osl::Maths::Comparison::almost_one functions
 *********************************************************************/

#ifndef OSL_MATHS_COMPARISON_ALMOST_ONE_H
#define OSL_MATHS_COMPARISON_ALMOST_ONE_H

#include "Osl/Globals.h"
#include "Osl/Constants.h"

namespace Osl { // Osl namespace

namespace  Maths { // Osl::Maths namespace

namespace Comparison { // Osl::Maths::Comparison namespace

// ===== ALMOST ONE =====
/*! ********************************************************************
 * \brief Function to estimate when a real double precision floating points
 *        equals one in a machine sense.
 *
 * This function compares the given real number \f$x\f$ to \f$1\f$
 * against the machine resolution for double \f$res\f$:
 *
 * \f[
 *     \left\vert x-1\right\vert\leq res
 * \f]
 *
 * with the machine resolution defined in Osl::Constants::n_machine_res.
 * When this equality holds, the real number is considered as equal
 * to one.
 *
 * \param [in] x the numbers to be compared to one.
 * \returns true if x equals one in a machine sense, false otherwise.
 * \sa bool almost_one(complex z)
 *********************************************************************/
inline bool almost_one(double x)
{
    return std::abs(x - 1.0) <= Constants::n_machine_res;
}

/*! ********************************************************************
 * \brief Function to estimate when a complex double precision floating points
 *        equals one in a machine sense.
 *
 * This function compares the given complex number \f$z\f$ real part
 * to \f$1\f$ and its imaginary part to \f$0\f$ against the machine
 * resolution for double \f$res\f$:
 *
 * \f[
 *     \left\vert\mathcal{R}(x)-1\right\vert\leq res
 *     \quad\mbox{and}\quad
 *     \left\vert\mathcal{I}(x)\right\vert\leq res
 * \f]
 *
 * with the machine resolution defined in Osl::Constants::n_machine_res.
 * When this equality holds, the complex number is considered as equal
 * to one.
 *
 * \param [in] z the number to be compared to one.
 * \returns true if z equals zero in a machine sense, false otherwise.
 * \sa bool almost_one(double x)
 *********************************************************************/
inline bool almost_one(complex z)
{
    return (std::abs(z.real() - 1.0) <= Constants::n_machine_res) &&
           (std::abs(z.imag()) <= Constants::n_machine_res);
}

} // namespace Osl::Maths::Comparison

} // namespace Osl::Maths

} // namespace Osl

#endif // OSL_MATHS_COMPARISON_ALMOST_ONE_H
