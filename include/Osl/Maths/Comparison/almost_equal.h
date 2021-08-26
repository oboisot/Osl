/*! ********************************************************************
 * \file almost_equal.h
 * \brief Header file for the Osl::Maths::Comparison::almost_equal functions
 *********************************************************************/

#ifndef OSL_MATHS_COMPARISON_ALMOST_EQUAL_H
#define OSL_MATHS_COMPARISON_ALMOST_EQUAL_H

#include "Osl/Globals.h"
#include "Osl/Constants.h"

namespace Osl { // Osl namespace

namespace  Maths { // Osl::Maths namespace

namespace Comparison { // Osl::Maths::Comparison namespace

// ===== ALMOST EQUAL =====
/*! ********************************************************************
 * \brief Function to compare two real double precision floating points.
 *
 * This function compares two double precision floating points \f$x\f$
 * and \f$y\f$ against the machine resolution for double \f$res\f$:
 *
 * \f[
 *     \left\vert x-y\right\vert\leq res
 * \f]
 *
 * with the machine resolution defined in Osl::Constants::n_machine_res.
 * When this equality holds, the two numbers are considered as almost
 * equal.
 *
 * \param [in] x, y the two numbers to be compared.
 * \returns true if x and y are equal in a machine sense, false otherwise.
 * \sa bool almost_equal(complex x, complex y)
 *********************************************************************/
inline bool almost_equal(double x, double y)
{
    return std::abs(x - y) <= Constants::n_machine_res;
}

/*! ********************************************************************
 * \brief Function to compare two complex double precision floating points.
 *
 * This function compares two complex double precision floating points \f$x\f$
 * and \f$y\f$ against the machine resolution for double \f$res\f$.
 * The comparison is made on both real and imaginary parts of the
 * two complex numbers as follows:
 *
 * \f[
 *     \left\vert\mathcal{R}(x)-\mathcal{R}(y)\right\vert\leq res
 *     \quad\mbox{and}\quad
 *     \left\vert\mathcal{I}(x)-\mathcal{I}(y)\right\vert\leq res
 * \f]
 *
 * with the machine resolution defined in Osl::Constants::n_machine_res.
 * When these equality holds, the two complex numbers are considered as
 * almost equal.
 *
 * \param [in] x, y the two complex numbers to be compared.
 * \returns true if x and y are equal in a machine sense, false otherwise.
 * \sa bool almost_equal(double x, double y)
 *********************************************************************/
inline bool almost_equal(complex x, complex y)
{
    return (std::abs(x.real() - y.real()) <= Constants::n_machine_res) &&
           (std::abs(x.imag() - y.imag()) <= Constants::n_machine_res);
}



} // namespace Osl::Maths::Comparison

} // namespace Osl::Maths

} // namespace Osl

#endif // OSL_MATHS_COMPARISON_ALMOST_EQUAL_H
