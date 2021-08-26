/*! ********************************************************************
 * \file InterpolatorEnum.h
 * \brief Header file of Osl::Maths::Interpolator enumerations.
 *********************************************************************/

#ifndef OSL_MATHS_INTERPOLATOR_INTERPOLATORENUM_H
#define OSL_MATHS_INTERPOLATOR_INTERPOLATORENUM_H

namespace Osl { // Osl namespace

namespace Maths { // Osl::Maths namespace

namespace Interpolator { // Osl::Maths::Interpolator namespace

/*! ********************************************************************
 * \enum CubicSplineBoundary
 * \brief Enumeration for the initialization of the Cubic Spline
 *        Interpolator classes.
 *********************************************************************/
enum class CubicSplineBoundary
{
    /*! Create a cubic spline interpolator with "natural" boundary conditions.*/
    natural,
    /*! Create a cubic spline interpolator with first and last polynomials being
     * quadratic polynomials.*/
    quadratic,
    /*! Create a cubic spline interpolator with "not-a-knot" boundary conditions.*/
    notAKnot
};

/*! ********************************************************************
 * \enum QuadraticSplineBoundary
 * \brief Enumeration for the initialization of the Quadratic Spline
 *        Interpolator classes.
 *********************************************************************/
enum class QuadraticSplineBoundary
{
    /*! Create a quadratic spline interpolator with first polynomial
     * being linear.*/
    linearFirst,
    /*! Create a quadratic spline interpolator with last polynomial
     * being linear.*/
    linearLast
};

} // namespace Osl::Maths::Interpolator

} // namespace Osl::Maths

} // namespace Osl

#endif // OSL_MATHS_INTERPOLATOR_INTERPOLATORENUM_H
