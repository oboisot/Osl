/*! ********************************************************************
 * \file ComplexCubicSpline.h
 * \brief Header file of Osl::Maths::Interpolator::ComplexCubicSpline
 *        class.
 *********************************************************************/

#ifndef OSL_MATHS_INTERPOLATOR_COMPLEXCUBICSPLINE_H
#define OSL_MATHS_INTERPOLATOR_COMPLEXCUBICSPLINE_H

#include "Osl/Globals.h"
#include "Osl/Constants.h"
#include "InterpolatorEnum.h"

namespace Osl { // Osl namespace

namespace Maths { // Osl::Maths namespace

namespace Interpolator { // Osl::Maths::Interpolator namespace

/*! ********************************************************************
 * \brief Class to construct a piecewise Cubic Spline interpolator from
 *        complex data.
 *
 * <h3>Principle</h3>
 *
 * This class defines a one dimensional piecewise cubic spline
 * interpolator. Let a set of evaluation points
 * \f$(x_k)_{k\in[\vert0;N\vert]}\f$
 * of size \f$N+1\f$ being in a strictly increasing order:
 *
 * \f[
 *     x_0<x_1<\cdots<x_{n-1}<x_n
 * \f]
 *
 * The piecewise cubic spline interpolation function at index \f$k\f$ is
 * defined by the third order polynomial:
 *
 * \f[
 *     f_k(x)=a_k(x-x_k)^3+b_k(x-x_k)^2+c_k(x-x_k)+d_k,\quad
 *     \forall x\in[x_k; x_{k+1}[\quad ; \quad\forall k\in[\vert0;N-1\vert]
 * \f]
 *
 * providing a set of \f$N\f$ interpolation functions
 * \f$(f_k)_{k\in[\vert0;N-1\vert]}\f$ with their corresponding sets of
 * coefficients \f$(a_k, b_k, c_k, d_k)_{k\in[\vert0;N-1\vert]}\f$.
 *
 * <h3>Computation of the interpolator coefficients</h3>
 *
 * This class provides two main cubic spline interpolators depending
 * on the available data, to know:
 *
 * - A <b>Cubic Hermite Spline</b> when evaluation points \f$x\f$,
 *   function values \f$y=f(x)\f$ and function first derivative values
 *   \f$y'=f'(x)\f$ are given.
 *
 *   Expression of the first derivative of the piecewise cubic spline
 *   is simply given by:
 *
 *   \f[
 *       f'_k(x)=3a_k(x-x_k)^2+2b_k(x-x_k)+c_k,\quad
 *       \forall x\in[x_k; x_{k+1}[\quad ;
 *       \quad\forall k\in[\vert0;N-1\vert]
 *   \f]
 *
 *   Coefficients are thus determined by ensuring continuity of the
 *   interpolation function and its first derivative at each interval
 *   nodes, resulting in the sytem of equations:
 *
 *   \f[
 *       \begin{array}{rcl}
 *          f_k(x_k) & = & y_k\\
 *          f'_k(x_k) & = & y'_k \\
 *          f_k(x_{k+1}) & = & y_{k+1}\\
 *          f'_k(x_{k+1}) & = & y'_{k+1} \\
 *       \end{array}
 *   \f]
 *
 *   Solving this system results in the evaluation of the coefficients
 *   for the piecewise cubic interpolation functions \f$f_k\f$:
 *
 *   \f[
 *       \left\{\begin{array}{rcl}
 *          a_k & = & \dfrac{1}{(x_{k+1}-x_k)^2}\left(-2
 *                    \dfrac{y_{k+1}-y_k}{x_{k+1}-x_k}+y'_k+y'_{k+1}\right) \\
 *          b_k & = & \dfrac{1}{x_{k+1}-x_k}\left(3
 *                    \dfrac{y_{k+1}-y_k}{x_{k+1}-x_k}-2y'_k-y'_{k+1}\right) \\
 *          c_k & = & y'_k \\
 *          d_k & = & y_k
 *       \end{array}\right.,
 *       \quad\forall k\in[\vert0;N-1\vert]
 *   \f]
 *
 * - A <b>Cubic Spline</b> when evaluation points \f$x\f$ and function
 *   values at these points are given \f$y=f(x)\f$. The cubic spline
 *   interpolant satisfies the following conditions:
 *
 *   1. \f$f_k(x_k)=y_k\f$ (<i>value at nodes</i>)
 *   2. \f$f_{k+1}(x_{k+1})=f_k(x_{k+1})\f$ (<i>continuity at nodes</i>)
 *   3. \f$f'_{k+1}(x_{k+1})=f'_k(x_{k+1})\f$ (<i>first derivative continuity
 *      at nodes</i>)
 *   4. \f$f''_{k+1}(x_{k+1})=f''_k(x_{k+1})\f$ (<i>second derivative continuity
 *      at nodes</i>)
 *
 *   Those relationships can be rewritten into the following system for the
 *   coefficients of the piecewise cubic spline interpolators (see \cite Burden_10
 *   pages 146-148):
 *
 *   \f[
 *       \begin{array}{rclr}
 *       d_k & = & y_k & \mbox{ (1)}\\
 *       h_{k-1}b_{k-1}+2(h_{k-1}+h_k)b_k+h_kb_{k+1} & = &
 *        \dfrac{3}{h_k}(y_{k+1}-y_k)-\dfrac{3}{h_{k-1}}(y_k-y_{k-1}) & \mbox{ (2)} \\
 *       c_k & = & \dfrac{y_{k+1}-y_k}{h_k}-\dfrac{h_k}{3}(2b_k+b_{k+1}) & \mbox{ (3)} \\
 *       a_k & = & \dfrac{b_{k+1}-b_k}{3h_k} & \mbox{ (4)}
 *       \end{array}
 *   \f]
 *
 *   where \f$h_k=x_{k+1}-x_k,\quad\forall k\in[\vert0;N-1\vert]\f$. Equation (1)
 *   finds the \f$d_k\f$ coefficients and is simply given by data, equation (2)
 *   requires to solve a linear system to estimate the \f$b_k\f$ coefficients.
 *   Once all \f$b_k\f$ coefficients are determined, coefficients \f$c_k\f$ and
 *   \f$a_k\f$ are determined through equations (3) and (4), respectively.
 *
 *   System of equation (2) can be written in a matrix form as:
 *
 *   \f[
 *       A\mathbf{x}=\mathbf{b}
 *   \f]
 *   with:
 *
 *   \f[
 *       A=\begin{pmatrix}
 *       -      & -          & -          & -       & -                  & - \\
 *       h_0    & 2(h_0+h_1) & h_1        & 0       & \cdots             & 0 \\
 *       0      & h_1        & 2(h_1+h_2) & h_2     & \ddots             & \vdots \\
 *       \vdots & \ddots     & \ddots     & \ddots  & \ddots             & 0 \\
 *       0      & \cdots     & 0          & h_{n-2} & 2(h_{n-2}+h_{n-1}) & h_{n-1} \\
 *       -      & -          & -          & -       & -                  & -
 *       \end{pmatrix}
 *   \f]
 *
 *   \f[
 *       \mathbf{x}=\begin{pmatrix}
 *       b_0 \\ b_1 \\ \vdots \\ b_n
 *       \end{pmatrix}
 *       \quad\mbox{and}\quad
 *       \mathbf{b}=\begin{pmatrix}
 *       - \\ \dfrac{3}{h_1}(y_2-y_1)-\dfrac{3}{h_0}(d_1-d_0) \\
 *       \vdots \\ \dfrac{3}{h_{n-1}}(y_n-y_{n-1})-\dfrac{3}{h_{n-2}}(y_{n-1}-y_{n-2}) \\
 *       -
 *       \end{pmatrix}
 *   \f]
 *
 *   However, equation (2) gives only access to \f$N-1\f$ equations for a
 *   \f$N+1\f$ system of equations (see matrix \f$A\f$ and vector \f$\mathbf{b}\f$),
 *   two more equations are thus required to solve this system.
 *
 *   This can be achieved by imposing two <b>boundary conditions</b> on the cubic
 *   spline interpolators, the most classical are:
 *
 *   - The <b>Natural</b> or <b>Free</b> boundary which supposes
 *     that the second derivative of the function at first and last
 *     points are equal to zero:
 *     \f[
 *         f''_0(x_0)=f''_n(x_n)=0
 *     \f]
 *     resulting in the two supplementary equations:
 *     \f[
 *         b_0=b_n=0
 *     \f]
 *     Using these two equations, matrix \f$A\f$ is thus equal to:
 *     \f[
 *       A=\begin{pmatrix}
 *       1      & 0          & 0          & \cdots  & \cdots             & 0 \\
 *       h_0    & 2(h_0+h_1) & h_1        & \ddots  &                    & \vdots \\
 *       0      & h_1        & 2(h_1+h_2) & h_2     & \ddots             & \vdots \\
 *       \vdots & \ddots     & \ddots     & \ddots  & \ddots             & 0 \\
 *       \vdots &            & \ddots     & h_{n-2} & 2(h_{n-2}+h_{n-1}) & h_{n-1} \\
 *       0      & \cdots     & \cdots     & 0       & 0                  & 1
 *       \end{pmatrix}
 *     \f]
 *     and vector \f$\mathbf{b}\f$ to:
 *     \f[
 *          \mathbf{b}=\begin{pmatrix}
 *          0 \\ \dfrac{3}{h_1}(y_2-y_1)-\dfrac{3}{h_0}(d_1-d_0) \\
 *          \vdots \\ \dfrac{3}{h_{n-1}}(y_n-y_{n-1})-\dfrac{3}{h_{n-2}}(y_{n-1}-y_{n-2}) \\
 *          0
 *         \end{pmatrix}
 *     \f]
 *     The estimation of the piecewise cubic polynomials
 *     coefficients requires the inversion of a tridiagonal matrix and
 *     follows algorithm 3.4 pages 149-150 of \cite Burden_10.
 *
 *   - The <b>Quadratic</b> boundary defines the first and last
 *     piecewise polynomials as quadratic polynomials, imposing
 *     that:
 *     \f[
 *         a_0=a_{n-1}=0
 *     \f]
 *     in order to get quadratic polynomials for the first and last
 *     interpolator. Plugging these conditions in equation (4), we
 *     obtain the matrix \f$A\f$:
 *     \f[
 *       A=\begin{pmatrix}
 *       1      & -1         & 0          & \cdots  & \cdots             & 0 \\
 *       h_0    & 2(h_0+h_1) & h_1        & \ddots  &                    & \vdots \\
 *       0      & h_1        & 2(h_1+h_2) & h_2     & \ddots             & \vdots \\
 *       \vdots & \ddots     & \ddots     & \ddots  & \ddots             & 0 \\
 *       \vdots &            & \ddots     & h_{n-2} & 2(h_{n-2}+h_{n-1}) & h_{n-1} \\
 *       0      & \cdots     & \cdots     & 0       & -1                 & 1
 *       \end{pmatrix}
 *     \f]
 *     and the corresponding vector \f$\mathbf{b}\f$:
 *     \f[
 *          \mathbf{b}=\begin{pmatrix}
 *          0 \\ \dfrac{3}{h_1}(y_2-y_1)-\dfrac{3}{h_0}(d_1-d_0) \\
 *          \vdots \\ \dfrac{3}{h_{n-1}}(y_n-y_{n-1})-\dfrac{3}{h_{n-2}}(y_{n-1}-y_{n-2}) \\
 *          0
 *         \end{pmatrix}
 *     \f]
 *     Matrix \f$A\f$ is a tridiagonal matrix and the Crout factorization
 *     for tridiagonal linear systems presented in algorithm 6.7 pages 422-423
 *     of \cite Burden_10 is used to estimate the \f$b_k\f$ coefficients.
 *
 *   - The <b>Not-a-Knot</b> boundary which imposes that the
 *     third derivative of the function  at the two first and two last
 *     piecewise polynomials are continuous:
 *     \f[
 *        f'''_0(x_1)=f'''_1(x_1)\quad\mbox{and}\quad f'''_{n-2}(x_{n-1})=f'''_{n-1}(x_{n-1})
 *     \f]
 *     resulting in the two supplementary conditions:
 *     \f[
 *         a_0=a_1\quad\mbox{and}\quad a_{n-2}=a_{n-1}
 *     \f]
 *     which, using equation (4), allows to estimate the matrix \f$A\f$ as:
 *     \f[
 *       A=\begin{pmatrix}
 *       h_1    & -(h_0+h_1) & h_0        & 0       & \cdots             & 0 \\
 *       h_0    & 2(h_0+h_1) & h_1        & 0       &                    & \vdots \\
 *       0      & h_1        & 2(h_1+h_2) & h_2     & \ddots             & \vdots \\
 *       \vdots & \ddots     & \ddots     & \ddots  & \ddots             & 0 \\
 *       \vdots &            & 0          & h_{n-2} & 2(h_{n-2}+h_{n-1}) & h_{n-1} \\
 *       0      & \cdots     & 0          & h_{n-1} & -(h_{n-2}+h_{n-1}) & h_{n-2}
 *       \end{pmatrix}
 *     \f]
 *     and vector \f$\mathbf{b}\f$ to:
 *     \f[
 *          \mathbf{b}=\begin{pmatrix}
 *          0 \\ \dfrac{3}{h_1}(y_2-y_1)-\dfrac{3}{h_0}(d_1-d_0) \\
 *          \vdots \\ \dfrac{3}{h_{n-1}}(y_n-y_{n-1})-\dfrac{3}{h_{n-2}}(y_{n-1}-y_{n-2}) \\
 *          0
 *         \end{pmatrix}
 *     \f]
 *
 * \sa CubicSpline a cubic spline interpolator class
 *     for real data.
 *********************************************************************/
class ComplexCubicSpline
{
public:
    //! Default Constructor.
    ComplexCubicSpline();

    //! Copy constructor
    ComplexCubicSpline(const ComplexCubicSpline &other);

    /*! ********************************************************************
     * \brief Cubic spline interpolator constructor for complex data.
     * \param [in] x the axis where the function is evaluated.
     * \param [in] y the values of the complex function evaluated at \f$x\f$
     *        values.
     * \param [in] bc an enumeration to determine what boundary condition to
     *             use for the cubic spline interpolator. Default to
     *             CubicSplineBoundary::natural.
     *********************************************************************/
    ComplexCubicSpline(const vector &x, const cvector &y,
                       enum CubicSplineBoundary bc=CubicSplineBoundary::natural);

    /*! ********************************************************************
     * \brief Hermite cubic spline interpolator constructor for complex data.
     * \param [in] x the axis where the function is evaluated.
     * \param [in] y the values of the complex function evaluated at \f$x\f$
     *        values.
     * \param [in] yp the values of the complex function first derivative
     *        evaluated at \f$x\f$ values.
     *********************************************************************/
    ComplexCubicSpline(const vector &x, const cvector &y, const cvector &yp);

    //! Default Destructor
    ~ComplexCubicSpline();

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
     *        interpolator.
     * \param [out] b A vector containing the \f$b_k\f$ coefficients of the
     *        interpolator.
     * \param [out] c A vector containing the \f$c_k\f$ coefficients of the
     *        interpolator.
     * \param [out] d A vector containing the \f$d_k\f$ coefficients of the
     *        interpolator.
     * \note The size of these vectors are the size of the input data minus 1.
     *********************************************************************/
    void getCoeffs(cvector &a, cvector &b, cvector &c, cvector &d);

    // *************** SETTER ***************
    /*! ********************************************************************
     * \brief Set the ComplexCubicSpline points from \f$x\f$ and \f$y\f$
     *        data.
     * \param [in] x the axis where the function is evaluated.
     * \param [in] y the values of the complex function evaluated at \f$x\f$ values.
     * \param [in] bc an enumeration to determine what boundary condition to
     *             use for the cubic spline interpolator. Default to
     *             CubicSplineBoundary::natural.
     * \note This setter method initializes a new ComplexCubicSpline
     *       through its corresponding constructor
     *       ComplexCubicSpline(const vector &x, const vector &y, enum CubicSplineBoundary bc).
     *********************************************************************/
    void setPoints(const vector &x, const cvector &y,
                   enum CubicSplineBoundary bc = CubicSplineBoundary::natural);

    /*! ********************************************************************
     * \brief Set the CubicSplineInterpolator points from \f$x\f$, \f$y\f$
     *        and \f$y'\f$ data using the Nominal cubic spline method.
     * \param [in] x the axis where the function is evaluated.
     * \param [in] y the values of the complex function evaluated at \f$x\f$ values.
     * \param [in] yp the values of the complex function first derivative evaluated
     *        at \f$x\f$ values.
     * \note This setter method initializes a new ComplexCubicSpline
     *       through its corresponding constructor
     *       ComplexCubicSpline(const vector &x, const vector &y, const vector &yp).
     *********************************************************************/
    void setPoints(const vector &x, const cvector &y, const cvector &yp);

    // ============== OPERATORS ==============
    //! Assignement from another ComplexCubicSpline
    ComplexCubicSpline operator=(const ComplexCubicSpline &other);

    /*! ********************************************************************
     * \brief Evaluate the complex function at a given point.
     * \param [in] x the value at which the function is evaluated.
     * \param [out] y the interpolated complex value of the function.
     * \note This function call doesn't make bound checkings.
     *********************************************************************/
    void operator()(const double &x, complex &y);

    /*! ********************************************************************
     * \brief Evaluate the complex function and its first derivative at a
     *        given point.
     * \param [in] x the value at which the function is evaluated.
     * \param [out] y the interpolated complex value of the function.
     * \param [out] yp the interpolated complex value of the first derivative
     *              of the function.
     * \note This function call doesn't make bound checkings.
     *********************************************************************/
    void operator()(const double &x, complex &y, complex &yp);

    /*! ********************************************************************
     * \brief Evaluate the complex function, its first and second derivatives
     *        at a given point.
     * \param [in] x the value at which the function is evaluated.
     * \param [out] y the interpolated complex value of the function.
     * \param [out] yp the interpolated complex value of the first derivative
     *              of the function.
     * \param [out] ypp the interpolated complex value of the second
     *              derivative of the function.
     * \note This function call doesn't make bound checkings.
     *********************************************************************/
    void operator()(const double &x, complex &y, complex &yp, complex &ypp);

    /*! ********************************************************************
     * \brief Evaluate the complex function at a given point.
     *
     * This function call overload allows efficient call when interpolating
     * between two values of the provided data through the 'index' parameter.
     * (This avoid the search for index).
     *
     * \param [in] x the value at which the function is evaluated.
     * \param [in] index the index to which compute the interpolated values.
     * \param [out] y the interpolated complex value of the function.
     * \note 1. This function call doesn't make bound checkings.
     * \note 2. It is up to you to check or be sure that \em index and the value
     *          where the function is interpolated \em x coincides.
     *********************************************************************/
    void operator()(const double &x, const std::size_t &index,
                    complex &y);

    /*! ********************************************************************
     * \brief Evaluate the complex function and its derivative at a given point.
     *
     * This function call overload allows efficient call when interpolating
     * between two values of the provided data through the 'index' parameter.
     * (This avoid the search for index).
     *
     * \param [in] x the value at which the function is evaluated.
     * \param [in] index the index to which compute the interpolated values.
     * \param [out] y the interpolated complex value of the function.
     * \param [out] yp the interpolated complex value of the first derivative
     *              of the function.
     * \note 1. This function call doesn't make bound checkings.
     * \note 2. It is up to you to check or be sure that \em index and the value
     *          where the function is interpolated \em x coincides.
     *********************************************************************/
    void operator()(const double &x, const std::size_t &index,
                    complex &y, complex &yp);

    /*! ********************************************************************
     * \brief Evaluate the complex function, its first and second derivatives
     *        at a given point.
     *
     * This function call overload allows efficient call when interpolating
     * between two values of the provided data through the 'index' parameter.
     * (This avoid the search for index).
     *
     * \param [in] x the value at which the function is evaluated.
     * \param [in] index the index to which compute the interpolated values.
     * \param [out] y the complex interpolated value of the function.
     * \param [out] yp the interpolated complex value of the first derivative
     *              of the function.
     * \param [out] ypp the interpolated complex value of the second
     *              derivative of the function.
     * \note 1. This function call doesn't make bound checkings.
     * \note 2. It is up to you to check or be sure that \em index and the value
     *          where the function is interpolated \em x coincides.
     *********************************************************************/
    void operator()(const double &x, const std::size_t &index,
                    complex &y, complex &yp, complex &ypp);

    // =========== CUBIC SPLINE METHODS ===========
    /*! ********************************************************************
     * \brief Evaluate the complex function at a given point with bound
     *        checkings.
     * \param [in] x the value at which the function is evaluated.
     * \param [in] extrapolate whether to authorize extrapolation or not.
     *             Default to false.
     * \returns The complex value of the function at the given point.
     *********************************************************************/
    complex at(const double &x, bool extrapolate=false);

    /*! ********************************************************************
     * \brief Evaluate the first derivative of the complex function at a
     *        given point with bound checkings.
     * \param [in] x the value at which the function is evaluated.
     * \param [in] extrapolate whether to authorize extrapolation or not.
     *             Default to false.
     * \returns The complex value of the first derivative of the function at the
     *          given point.
     *********************************************************************/
    complex prime(const double &x, bool extrapolate=false);

    /*! ********************************************************************
     * \brief Evaluate the second derivative of the complex function at a
     *        given point with bound checkings.
     * \param [in] x the value at which the function is evaluated.
     * \param [in] extrapolate whether to authorize extrapolation or not.
     *             Default to false.
     * \returns The complex value of the second derivative of the function at the
     *          given point.
     *********************************************************************/
    complex primeprime(const double &x, bool extrapolate=false);

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
    double m_xmin, m_xmax;              // Min and max value of interpolation
    vector m_x;                         // Provided axis for interpolation
    cvector m_a, m_b, m_c, m_d;          // Interpolation coefficients of complex function
    std::size_t m_n;                    // Size of coefficients vectors
};

} // namespace Osl::Maths::Interpolator

} // namespace Osl::Maths

} // namespace Osl

#endif // OSL_MATHS_INTERPOLATOR_COMPLEXCUBICSPLINE_H
