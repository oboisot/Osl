/*! ********************************************************************
 * \file Sinc.h
 * \brief Header file of Osl::Maths::Interpolator::Sinc class.
 *********************************************************************/

#ifndef OSL_MATHS_INTERPOLATOR_SINC_H
#define OSL_MATHS_INTERPOLATOR_SINC_H

#include <numeric>
#include <algorithm>
#include "Osl/Globals.h"
#include "Osl/Constants.h"
#include "Osl/Maths/Comparison/almost_zero.h"
#include "Osl/Maths/Functions/sinc.h"

namespace Osl { // Osl namespace

namespace Maths { // Osl::Maths namespace

namespace Interpolator { // Osl::Maths::Interpolator namespace

class Sinc
{
public:
    //! Default Constructor.
    Sinc();

    //! Copy constructor
    Sinc(const Sinc &other);

    /*! ********************************************************************
     * \brief Sinc interpolator constructor.
     * \param [in] x the axis where the function is evaluated.
     * \param [in] y the values of the function evaluated at \f$x\f$
     *        values.
     * \note x axis must be evnely spaced.
     *********************************************************************/
    Sinc(const vector &x, const vector &y);

    //! Default Destructor
    ~Sinc();

    // ============== CLASS METHODS ==============
    // *************** GETTER ***************
    /*! ********************************************************************
     * \brief Get minimum x value.
     * \returns The minimum x value of the constructed interpolator.
     *********************************************************************/
    double getXmin() const;

    /*! ********************************************************************
     * \brief Get maximum x value.
     * \returns The maximum x value of the constructed interpolator.
     *********************************************************************/
    double getXmax() const;

    /*! ********************************************************************
     * \brief Get the defining x axis values.
     * \returns A vector containing the defining x axis values (a copy of
     * the input x vector).
     *********************************************************************/
    vector getX() const;

    // *************** SETTER ***************
    /*! ********************************************************************
     * \brief Set the Sinc interpolator points from \f$x\f$ and \f$y\f$ data.
     * \param [in] x the axis where the function is evaluated.
     * \param [in] y the values of the function evaluated at \f$x\f$ values.
     * \note This setter method initializes a new Sinc interpolator
     *       through its corresponding constructor
     *       Sinc(const vector &x, const vector &y).
     *********************************************************************/
    void setPoints(const vector &x, const vector &y);

    // ============== OPERATORS ==============
    //! Assignement from another Sinc
    Sinc operator=(const Sinc &other);

    /*! ********************************************************************
     * \brief Evaluate the function at a given point.
     * \param [in] x the value at which the function is evaluated.
     * \param [out] y the interpolated value of the function.
     * \note This function call doesn't make bound checkings.
     *********************************************************************/
    void operator()(const double &x, double &y);

private:
    double m_xmin, m_xmax;              // Min and max value of interpolation
    vector m_x,                         // Provided axis for interpolation
           m_y;                         // Function values
    double m_inv_dx;                    // inverse of xaxis variation
    std::size_t m_n;                    // Size of coefficients vectors
};

} // namespace Osl::Maths::Interpolator

} // namespace Osl::Maths

} // namespace Osl

#endif // OSL_MATHS_INTERPOLATOR_SINC_H
