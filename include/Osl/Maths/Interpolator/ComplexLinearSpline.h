/*! ********************************************************************
 * \file ComplexLinearSpline.h
 * \brief Header file of Osl::Maths::Interpolator::ComplexLinearSpline
 *        class.
 *********************************************************************/

#ifndef OSL_MATHS_INTERPOLATOR_COMPLEXLINEARSPLINE_H
#define OSL_MATHS_INTERPOLATOR_COMPLEXLINEARSPLINE_H

#include "Osl/Globals.h"

namespace Osl { // Osl namespace

namespace Maths { // Osl::Maths namespace

namespace Interpolator { // Osl::Maths::Interpolator namespace

/*! ********************************************************************
 * \brief Class to construct a piecewise Linear Spline interpolator from
 *        complex data.
 *
 * <h3>Principle</h3>
 *
 * This class defines a one dimensional piecewise linear spline
 * interpolator. Let a set of evaluation points
 * \f$(x_k)_{k\in[\vert0;N\vert]}\f$
 * of size \f$N+1\f$ being in a strictly increasing order:
 *
 * \f[
 *     x_0<x_1<\cdots<x_{n-1}<x_n
 * \f]
 *
 * The piecewise Linear Spline interpolation function at index \f$k\f$
 * is defined by the first order polynomial:
 *
 * \f[
 *     f_k(x)=a_k(x-x_k) + b_k,\quad\forall x\in[x_k;x_{k+1}[\quad ;
 *     \quad\forall k\in[\vert0;N-1\vert]
 * \f]
 *
 * providing a set of \f$N\f$ interpolation functions
 * \f$(f_k)_{k\in[\vert0;N-1\vert]}\f$ with their corresponding coefficients
 * \f$(a_k, b_k)_{k\in[\vert0;N-1\vert]}\f$.
 *
 * <h3>Computation of the interpolator coefficients</h3>
 *
 * Coefficients are determined by ensuring the continuity of the
 * interpolation function at each interval nodes:
 *
 * \f[
 *     \begin{array}{rcl}
 *         f_k(x_k) & = & y_k\\
 *         f_k(x_{k+1}) & = & y_{k+1}\\
 *     \end{array}
 * \f]
 *
 * Solving this system results in the evaluation of the coefficients
 * for the piecewise linear interpolation functions \f$f_k\f$:
 *
 * \f[
 *     \left\{\begin{array}{rcl}
 *         a_k & = & \dfrac{y_{k+1}-y_k}{x_{k+1}-x_k} \\
 *         b_k & = & y_k
 *     \end{array}\right.,
 *     \quad\forall k\in[\vert0;N-1\vert]
 * \f]
 *
 * \sa LinearSpline a linear spline interpolator class
 *     for real data.
 *********************************************************************/
class ComplexLinearSpline
{
public:
    //! Default Constructor.
    ComplexLinearSpline();

    //! Copy constructor
    ComplexLinearSpline(const ComplexLinearSpline &other);

    /*! ********************************************************************
     * \brief Linear spline interpolator constructor for complex data.
     * \param [in] x the axis where the function is evaluated.
     * \param [in] y the values of the complex function evaluated at \f$x\f$ values.
     *********************************************************************/
    ComplexLinearSpline(const vector &x, const cvector &y);

    //! Default Destructor
    ~ComplexLinearSpline();

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

    /*! ********************************************************************
     * \brief Get the interpolator complex coefficients.
     * \param [out] a A vector containing the \f$a_k\f$ coefficients of the
     *        interpolator of the real part of the function.
     * \param [out] b A vector containing the \f$b_k\f$ coefficients of the
     *        interpolator of the real part of the function.
     * \note The size of these vectors are the size of the input data minus 1.
     *********************************************************************/
    void getCoeffs(cvector &a, cvector &b);

    // *************** SETTER ***************
    /*! ********************************************************************
     * \brief Set the ComplexLinearSpline points from \f$x\f$ and \f$y\f$
     *        complex data.
     * \param [in] x the axis where the function is evaluated.
     * \param [in] y the values of the complex function evaluated at \f$x\f$
     *             values.
     * \note This setter method initializes a new ComplexLinearSpline
     *       through its corresponding constructor
     *       ComplexLinearSpline(const vector &x, const cvector &y).
     *********************************************************************/
    void setPoints(const vector &x, const cvector &y);

    // ============== OPERATORS ==============
    //! Assignement from another LinearSpline
    ComplexLinearSpline operator=(const ComplexLinearSpline &other);

    /*! ********************************************************************
     * \brief Evaluate the complex function at a given point.
     * \param [in] x the value at which the complex function is evaluated.
     * \param [out] y the interpolated value of the complex function.
     * \note This function call doesn't make bound checkings.
     *********************************************************************/
    void operator()(const double &x, complex &y);

    /*! ********************************************************************
     * \brief Evaluate the complex function at a given point.
     *
     * This function call overload allows efficient call when interpolating
     * between two values of the provided data through the \em index parameter.
     * (This avoid the search for index).
     *
     * \param [in] x the value at which the complex function is evaluated.
     * \param [in] index the index to which compute the interpolated values.
     * \param [out] y the interpolated value of the complex function.
     * \note 1. This function call doesn't make bound checkings.
     * \note 2. It is up to you to check or be sure that \em index and the value
     *          where the function is interpolated \em x coincides.
     *********************************************************************/
    void operator()(const double &x, const std::size_t &index, complex &y);

    // =========== LINEAR SPLINE METHODS ===========
    /*! ********************************************************************
     * \brief Evaluate the complex function at a given point with bound checkings.
     * \param [in] x the value at which the complex function is evaluated.
     * \param [in] extrapolate whether to authorize extrapolation or not.
     *             Default to false.
     * \returns The complex value of the complex function at the given point.
     *********************************************************************/
    complex at(const double &x, bool extrapolate=false);

    /*! ********************************************************************
     * \brief Search the index for spline interpolation.
     *
     * This function makes use of binary search to find the first index
     * \f$i\f$ of reference axis \f$x[i]\f$ (in strictly increasing order)
     * such that, for the search value \f$x_{eval}\f$:
     *
     * \f[
     *     x_{eval} \geq x[i]
     * \f]
     *
     * \param [in] xeval the value for which the index is searched.
     * \returns The index to evaluate the spline function at xeval.
     * \note 1. If \f$x_{eval}\geq\underset{i}{\max}(x[i])\f$, last index minus 1
     *          is returned.
     * \note 2. If \f$x_{eval}\leq\underset{i}{\min}(x[i])\f$, index 0 is returned.
     *********************************************************************/
    std::size_t search_index_for_interpolation(const double &xeval);

private:
    double m_xmin, m_xmax;  // Min and max value of interpolation
    vector m_x;             // Provided axis for interpolation
    cvector m_a, m_b;        // Interpolation coefficients of complex function
    std::size_t m_n;        // Size of coefficients vectors
};

} // namespace Osl::Maths::Interpolator

} // namespace Osl::Maths

} // namespace Osl

#endif // OSL_MATHS_INTERPOLATOR_COMPLEXLINEARSPLINE_H
