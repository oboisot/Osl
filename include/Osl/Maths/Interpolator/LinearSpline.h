/*! ********************************************************************
 * \file LinearSpline.h
 * \brief Header file of Osl::Maths::Interpolator::LinearSpline class.
 *********************************************************************/

#ifndef OSL_MATHS_INTERPOLATOR_LINEARSPLINE_H
#define OSL_MATHS_INTERPOLATOR_LINEARSPLINE_H

#include "Osl/Globals.h"

namespace Osl { // Osl namespace

namespace Maths { // Osl::Maths namespace

namespace Interpolator { // Osl::Maths::Interpolator namespace

/*! ********************************************************************
 * \brief Class to construct a piecewise Linear Spline interpolator from
 *        real data.
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
 * \sa ComplexLinearSpline a linear spline interpolator class
 *     for complex data.
 *********************************************************************/
class LinearSpline
{
public:
    //! Default Constructor.
    LinearSpline();

    //! Copy constructor
    LinearSpline(const LinearSpline &other);

    /*! ********************************************************************
     * \brief Linear spline interpolator constructor.
     * \param [in] x the axis where the function is evaluated.
     * \param [in] y the values of the function evaluated at \f$x\f$ values.
     *********************************************************************/
    LinearSpline(const vector &x, const vector &y);

    //! Default Destructor
    ~LinearSpline();

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
     * \brief Get the interpolator coefficients.
     * \param [out] a A vector containing the \f$a_k\f$ coefficients of the
     *        interpolator.
     * \param [out] b A vector containing the \f$b_k\f$ coefficients of the
     *        interpolator.
     * \note The size of these vectors are the size of the input data minus 1.
     *********************************************************************/
    void getCoeffs(vector &a, vector &b);

    // *************** SETTER ***************
    /*! ********************************************************************
     * \brief Set the LinearSpline points from \f$x\f$ and \f$y\f$
     *        data.
     * \param [in] x the axis where the function is evaluated.
     * \param [in] y the values of the function evaluated at \f$x\f$ values.
     * \note This setter method initializes a new LinearSpline
     *       through its corresponding constructor
     *       LinearSpline(const vector &x, const vector &y).
     *********************************************************************/
    void setPoints(const vector &x, const vector &y);

    // ============== OPERATORS ==============
    //! Assignement from another LinearSplineInterpolator
    LinearSpline operator=(const LinearSpline &other);

    /*! ********************************************************************
     * \brief Evaluate the function at a given point.
     * \param [in] x the value at which the function is evaluated.
     * \param [out] y the interpolated value of the function.
     * \note This function call doesn't make bound checkings.
     *********************************************************************/
    void operator()(const double &x, double &y);

    /*! ********************************************************************
     * \brief Evaluate the function at a given point.
     *
     * This function call overload allows efficient call when interpolating
     * between two values of the provided data through the \em index parameter.
     * (This avoid the search for index).
     *
     * \param [in] x the value at which the function is evaluated.
     * \param [in] index the index to which compute the interpolated values.
     * \param [out] y the interpolated value of the function.
     * \note 1. This function call doesn't make bound checkings.
     * \note 2. It is up to you to check or be sure that \em index and the value
     *          where the function is interpolated \em x coincides.
     *********************************************************************/
    void operator()(const double &x, const std::size_t &index, double &y);

    // =========== LINEAR SPLINE METHODS ===========
    /*! ********************************************************************
     * \brief Evaluate the function at a given point with bound checkings.
     * \param [in] x the value at which the function is evaluated.
     * \param [in] extrapolate whether to authorize extrapolation or not.
     *             Default to false.
     * \returns The value of the function at the given point.
     *********************************************************************/
    double at(const double &x, bool extrapolate=false);

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
    vector m_a, m_b;        // Interpolation coefficients of real function
    std::size_t m_n;        // Size of coefficients vectors
};

/*! ********************************************************************
 * \brief Linear interpolation function.
 *
 * \param [in] x a reference to the reference axis of the function.
 * \param [in] y a reference to the value of the function in x.
 * \param [in] xeval the value for which the function is interpolated.
 * \returns The interpolated value in xeval.
 * \note This function call doesn't make bound checkings nor extrapolation
 *       checking.
 *********************************************************************/
double linear_interpolation(const vector &x, const vector &y, const double &xeval);

/*! ********************************************************************
 * \brief Linear interpolation function.
 *
 * \param [in] x a reference to the reference axis of the function.
 * \param [in] y a reference to the value of the function in x.
 * \param [in] xeval the value for which the function is interpolated.
 * \param [out] yinterp The interpolated value in xeval.
 * \note This function call doesn't make bound checkings nor extrapolation
 *       checking.
 *********************************************************************/
void linear_interpolation(const vector &x, const vector &y, const double &xeval,
                          double &yinterp);

/*! ********************************************************************
 * \brief Linear interpolation function for evenly spaced x axis.
 *
 * Linear interpolation function for evenly spaced x axis, that is,
 * x axis can be written as:
 *
 * \f[
 *     x[i]=x[0]+i\Delta x
 * \f]
 *
 * for each index \f$i\f$ and some regular spacing \f$\Delta x\f$.
 *
 * \param [in] x a reference to the reference axis of the function.
 * \param [in] y a reference to the value of the function in x.
 * \param [in] xeval the value for which the function is interpolated.
 * \returns The interpolated value in xeval.
 * \note This function call doesn't make bound checkings nor extrapolation
 *       checking.
 *********************************************************************/
double linear_interpolation_reg(const vector &x, const vector &y, const double &xeval);

/*! ********************************************************************
 * \brief Linear interpolation function for evenly spaced x axis.
 *
 * Linear interpolation function for evenly spaced x axis, that is,
 * x axis can be written as:
 *
 * \f[
 *     x[i]=x[0]+i\Delta x
 * \f]
 *
 * for each index \f$i\f$ and some regular spacing \f$\Delta x\f$.
 *
 * \param [in] x a reference to the reference axis of the function.
 * \param [in] y a reference to the value of the function in x.
 * \param [in] xeval the value for which the function is interpolated.
 * \param [out] yinterp The interpolated value in xeval.
 * \note This function call doesn't make bound checkings nor extrapolation
 *       checking.
 *********************************************************************/
void linear_interpolation_reg(const vector &x, const vector&y, const double &xeval,
                              double &yinterp);

void linear_interpolation_reg_nochecks(const double *x, const double *y,
                                       const double &xeval, const double &dx,
                                       double &yinterp);

} // namespace Osl::Maths::Interpolator

} // namespace Osl::Maths

} // namespace Osl

#endif // OSL_MATHS_INTERPOLATOR_LINEARSPLINE_H
