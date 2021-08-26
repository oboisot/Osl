/*! ********************************************************************
 * \file QuadraticSpline.h
 * \brief Header file of Osl::Maths::Interpolator::QuadraticSpline class.
 *********************************************************************/

#ifndef OSL_MATHS_INTERPOLATOR_QUADRATICSPLINE_H
#define OSL_MATHS_INTERPOLATOR_QUADRATICSPLINE_H

#include "Osl/Globals.h"
#include "InterpolatorEnum.h"

namespace Osl { // Osl namespace

namespace Maths { // Osl::Maths namespace

namespace Interpolator { // Osl::Maths::Interpolator namespace

/*! ********************************************************************
 * \brief Class to construct a piecewise Quadratic Spline interpolator from
 *        real data.
 *
 * <h3>Principle</h3>
 *
 * This class defines a one dimensional piecewise quadratic spline
 * interpolator. Let a set of evaluation points
 * \f$(x_k)_{k\in[\vert0;N\vert]}\f$
 * of size \f$N+1\f$ being in a strictly increasing order:
 *
 * \f[
 *     x_0<x_1<\cdots<x_{n-1}<x_n
 * \f]
 *
 * The piecewise quadratic spline interpolation function at index \f$k\f$ is
 * defined by the second order polynomial:
 *
 * \f[
 *     f_k(x)=a_k(x-x_k)^2+b_k(x-x_k)+c_k,\quad
 *     \forall x\in[x_k; x_{k+1}[\quad ; \quad\forall k\in[\vert0;N-1\vert]
 * \f]
 *
 * providing a set of \f$N\f$ interpolation functions
 * \f$(f_k)_{k\in[\vert0;N-1\vert]}\f$ with their corresponding sets of
 * coefficients \f$(a_k, b_k, c_k)_{k\in[\vert0;N-1\vert]}\f$.
 *
 * <h3>Computation of the interpolator coefficients</h3>
 *
 * The piecewise quadratic spline coefficients are estimated by ensuring
 * continuity of the interpolation function and its first derivative at
 * each node, that is:
 *
 * \f[
 *     \begin{array}{rcl}
 *         f_k(x_k) & = & y_k\\
 *         f_{k+1}(x_{k+1}) & = & f_k(x_{k+1})\\
 *         f'_{k+1}(x_{k+1}) & = & f'_k(x_{k+1}) \\
 *     \end{array}
 * \f]
 *
 * with \f$y_k\f$ being the value of the function to be interpolated
 * at the given point \f$x_k\f$.
 *
 * However, this system only contains \f$3N-1\f$ equations whereas
 * \f$3N\f$ equations are needed to estimate the \f$3N\f$ coefficients
 * of the interpolation functions. To circumvent this problem, one can
 * choose to consider the first or the last interpolation function to
 * be linear. This offers two boundary conditions for estimating the
 * coefficients of the piecewise quadratic spline:
 *
 * - The <b>first</b> interpolation function is considered as linear, that
 *   is \f$a_0=0\f$. In this case the coefficients of the quadratic spline
 *   are found iteratively by solving the previous system:
 *
 *   \f[
 *     \left\{\begin{array}{rcl}
 *         c_k & = & y_k\\
 *         b_k & = & b_{k-1}+2a_{k-1}(x_k-x_{k-1})\\
 *         a_k & = & \dfrac{1}{x_{k+1}-x_{k}}
 *                   \left(\dfrac{y_{k+1}-y_{k}}{x_{k+1}-x_{k}}-b_k\right)
 *     \end{array}\right.\quad\forall k\in[\vert1;N-1\vert]
 *   \f]
 *
 *   with the initial condition:
 *
 *   \f[
 *       \left\{\begin{array}{rcl}
 *         c_0 & = & y_0\\
 *         b_0 & = & \dfrac{y_{1}-y_{0}}{x_{1}-x_{0}}\\
 *         a_0 & = & 0
 *     \end{array}\right.\quad\mbox{ for }k=0
 *   \f]
 *
 * - The <b>last</b> interpolation function is considered as linear, that
 *   is \f$a_{n-1}=0\f$. In this case the coefficients of the quadratic spline
 *   are found iteratively by solving the previous system:
 *
 *   \f[
 *     \left\{\begin{array}{rcl}
 *         c_k & = & y_k\\
 *         a_k & = & \dfrac{1}{x_{k+1}-x_{k}}
 *                   \left(b_{k+1}-\dfrac{y_{k+1}-y_{k}}{x_{k+1}-x_{k}}\right)\\
 *         b_k & = & b_{k+1}-2a_k(x_{k+1}-x_k)
 *     \end{array}\right.\quad\forall k\in[\vert N-2;0\vert]
 *   \f]
 *
 *   with the initial condition:
 *
 *   \f[
 *       \left\{\begin{array}{rcl}
 *         c_{n-1} & = & y_{n-1}\\
 *         a_{n-1} & = & 0\\
 *         b_{n-1} & = & \dfrac{y_{n}-y_{n-1}}{x_{n}-x_{n-1}}
 *     \end{array}\right.\quad\mbox{ for }k=n-1
 *   \f]
 *
 * \sa ComplexQuadraticSpline a quadratic spline interpolator
 *     class for complex data.
 *********************************************************************/
class QuadraticSpline
{
public:
    //! Default Constructor.
    QuadraticSpline();

    //! Copy constructor
    QuadraticSpline(const QuadraticSpline &other);

    /*! ********************************************************************
     * \brief Quadratic spline interpolator constructor.
     * \param [in] x the axis where the function is evaluated.
     * \param [in] y the values of the function evaluated at \f$x\f$ values.
     * \param [in] bc an enumeration to determine what boundary condition to
     *             use for the quadratic spline interpolator. Default to
     *             QuadraticSplineBoundary::linearFirst.
     *********************************************************************/
    QuadraticSpline(const vector &x, const vector &y,
                     enum QuadraticSplineBoundary bc = QuadraticSplineBoundary::linearFirst);

    //! Default Destructor
    ~QuadraticSpline();

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
     * \param [out] c A vector containing the \f$c_k\f$ coefficients of the
     *        interpolator.
     * \note The size of these vectors are the size of the input data minus 1.
     *********************************************************************/
    void getCoeffs(vector &a, vector &b, vector &c);

    // *************** SETTER ***************
    /*! ********************************************************************
     * \brief Set the QuadraticSplineInterpolator points from \f$x\f$ and
     *        \f$y\f$ data.
     * \param [in] x the axis where the function is evaluated.
     * \param [in] y the values of the function evaluated at \f$x\f$ values.
     * \param [in] bc an enumeration to determine what boundary condition to
     *             use for the quadratic spline interpolator. Default to
     *             QuadraticSplineBoundary::linearFirst.
     * \note This setter method initializes a new QuadraticSpline
     *       through its corresponding constructor
     *       QuadraticSpline(const vector &x, const vector &y, enum QuadraticSplineBoundary bc).
     *********************************************************************/
    void setPoints(const vector &x, const vector &y,
                   enum QuadraticSplineBoundary bc = QuadraticSplineBoundary::linearFirst);

    // ============== OPERATORS ==============
    //! Assignement from another QuadraticSplineInterpolator
    QuadraticSpline operator=(const QuadraticSpline &other);

    /*! ********************************************************************
     * \brief Evaluate the function at a given point.
     * \param [in] x the value at which the function is evaluated.
     * \param [out] y the interpolated value of the function.
     * \note This function call doesn't make bound checkings.
     *********************************************************************/
    void operator()(const double &x, double &y);

    /*! ********************************************************************
     * \brief Evaluate the function at a given point.
     * \param [in] x the value at which the function is evaluated.
     * \param [out] y the interpolated value of the function.
     * \param [out] yp the interpolated value of the first derivative of the
     *              function.
     * \note This function call doesn't make bound checkings.
     *********************************************************************/
    void operator()(const double &x, double &y, double &yp);

    /*! ********************************************************************
     * \brief Evaluate the function at a given point.
     *
     * This function call overload allows efficient call when interpolating
     * between two values of the provided data through the 'index' parameter.
     * (This avoid the search for index).
     *
     * \param [in] x the value at which the function is evaluated.
     * \param [in] index the index to which compute the interpolated values.
     * \param [out] y the interpolated value of the function.
     * \note 1. This function call doesn't make bound checkings.
     * \note 2. It is up to you to check or be sure that \em index and the value
     *          where the function is interpolated \em x coincides.
     *********************************************************************/
    void operator()(const double &x, const std::size_t &index,
                    double &y);

    /*! ********************************************************************
     * \brief Evaluate the function and its derivative at a given point.
     *
     * This function call overload allows efficient call when interpolating
     * between two values of the provided data through the 'index' parameter.
     * (This avoid the search for index).
     *
     * \param [in] x the value at which the function is evaluated.
     * \param [in] index the index to which compute the interpolated values.
     * \param [out] y the interpolated value of the function.
     * \param [out] yp the interpolated value of the first derivative of the
     *              function.
     * \note 1. This function call doesn't make bound checkings.
     * \note 2. It is up to you to check or be sure that \em index and the value
     *          where the function is interpolated \em x coincides.
     *********************************************************************/
    void operator()(const double &x, const std::size_t &index,
                    double &y, double &yp);

    // =========== QUADRATIC SPLINE METHODS ===========
    /*! ********************************************************************
     * \brief Evaluate the function at a given point.
     * \param [in] x the value at which the function is evaluated.
     * \param [in] extrapolate whether to authorize extrapolation or not.
     *             Defaute to false.
     * \returns The value of the function at the given point.
     *********************************************************************/
    double at(const double &x, bool extrapolate=false);

    /*! ********************************************************************
     * \brief Evaluate the first derivative of the function at a given point.
     * \param [in] x the value at which the function is evaluated.
     * \param [in] extrapolate whether to authorize extrapolation or not.
     *             Defaute to false.
     * \returns The value of the first derivative of the function at the
     *          given point.
     *********************************************************************/
    double prime(const double &x, bool extrapolate=false);

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
    vector m_a, m_b, m_c;   // Interpolation coefficients
    std::size_t m_n;        // Size of coefficients vectors
};

} // namespace Osl::Maths::Interpolator

} // namespace Osl::Maths

} // namespace Osl

#endif // OSL_MATHS_INTERPOLATOR_QUADRATICSPLINE_H
