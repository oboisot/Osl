/*! ********************************************************************
 * \file CubicSpline3D.h
 * \brief Header file of Osl::Geometry::Interpolator::CubicSpline3D
 *        class.
 *********************************************************************/

#ifndef OSL_GEOMETRY_INTERPOLATOR3D_CUBICSPLINE3D_H
#define OSL_GEOMETRY_INTERPOLATOR3D_CUBICSPLINE3D_H

#include <algorithm>
#include "Osl/Geometry/Vector3D.h"

namespace Osl { // namespace Osl

namespace Geometry { // namespace Osl::Geometry

namespace Interpolator3D { // namespace Osl::Geometry::Interpolator

/*! ********************************************************************
 * \brief Class to construct a piecewise Cubic Spline interpolator of
 *        a 3D trajectory.
 *
 * <h3>Principle</h3>
 *
 * Knowing position and velocity vectors at a given time \f$t\f$, this
 * class defines a physical interpolator of the trajectory based on
 * underlying Cubic Spline interpolators for each x, y and z coordinates.
 *
 * Let a set of temporal points \f$(t_k)_{k\in[\vert0;N\vert]}\f$
 * of size \f$N+1\f$ being in a strictly increasing order:
 *
 * \f[
 *     t_0<t_1<\cdots<t_{n-1}<t_n
 * \f]
 *
 * with their corresponding position \f$(x_k, y_k, z_k)_{k\in[\vert0;N\vert]}\f$
 * and velocity \f$(v_{x,k}, v_{y,k}, v_{z,k})_{k\in[\vert0;N\vert]}\f$ vectors.
 *
 * The piecewise Cubic Spline interpolation functions at index \f$k\f$
 * for coordinates x, y and z are defined by the third order polynomials:
 *
 * \f[
 *     \begin{split}
 *     f_{x,k}(t) & =a_{x,k}(t-t_k)^3+b_{x,k}(t-t_k)^2+c_{x,k}(t-t_k)+d_{x,k} \\
 *     f_{y,k}(t) & =a_{y,k}(t-t_k)^3+b_{y,k}(t-t_k)^2+c_{y,k}(t-t_k)+d_{y,k} \\
 *     f_{z,k}(t) & =a_{z,k}(t-t_k)^3+b_{z,k}(t-t_k)^2+c_{z,k}(t-t_k)+d_{z,k}
 *     \end{split}
 *     ,\quad\forall t\in[t_k; t_{k+1}[\quad ; \quad\forall k\in[\vert0;N-1\vert]
 * \f]
 *
 * providing a set of \f$3\times N\f$ interpolation functions with their
 * corresponding coefficients:
 *
 * \f[
 *     \begin{split}
 *     (f_{x,k})_{k\in[\vert0;N-1\vert]} & \mbox{ with }
 *     (a_{x,k}, b_{x,k}, c_{x,k}, d_{x,k})_{k\in[\vert0;N-1\vert]} \\
 *     (f_{y,k})_{k\in[\vert0;N-1\vert]} & \mbox{ with }
 *     (a_{y,k}, b_{y,k}, c_{y,k}, d_{y,k})_{k\in[\vert0;N-1\vert]} \\
 *     (f_{z,k})_{k\in[\vert0;N-1\vert]} & \mbox{ with }
 *     (a_{z,k}, b_{z,k}, c_{z,k}, d_{z,k})_{k\in[\vert0;N-1\vert]} \\
 *     \end{split}
 * \f]
 *
 * <h3>Computation of the interpolator coefficients</h3>
 *
 * Coefficients are determined by ensuring continuity of the
 * interpolation functions (position vectors) and their first derivative
 * (velocity vectors) at each interval nodes.
 *
 * Considering the case of the \f$x\f$ coordinate, the first derivative
 * with respect to variable \f$t\f$ of the piecewise cubic spline
 * is given by:
 *
 * \f[
 *     f'_{x,k}(x)=3a_{x,k}(t-t_k)^2+2b_{x,k}(t-t_k)+c_{x,k},\quad
 *     \forall t\in[t_k; t_{k+1}[\quad ;
 *     \quad\forall k\in[\vert0;N-1\vert]
 * \f]
 *
 * Continuity of the position and velocity vectors results in the sytem
 * of equations for the \f$x\f$ coordinate:
 *
 * \f[
 *     \begin{array}{rcl}
 *         f_{x,k}(t_k) & = & x_k\\
 *         f'_{x,k}(t_k) & = & v_{x,k} \\
 *         f_{x,k}(t_{k+1}) & = & x_{k+1}\\
 *         f'_{x,k}(t_{k+1}) & = & v_{x,k+1} \\
 *     \end{array}
 * \f]
 *
 * Solving this system results in the evaluation of the coefficients
 * for the piecewise cubic interpolation functions \f$f_{x,k}\f$:
 *
 * \f[
 *     \left\{\begin{array}{rcl}
 *     a_{x,k} & = & \dfrac{1}{(t_{k+1}-t_k)^2}\left(-2
 *                    \dfrac{x_{k+1}-x_k}
 *                     {t_{k+1}-t_k}+v_{x,k}+v_{x,k+1}\right) \\
 *     b_{x,k} & = & \dfrac{1}{t_{k+1}-t_k}\left(3
 *                    \dfrac{x_{k+1}-x_k}
 *                     {t_{k+1}-t_k}-2v_{x,k}-v_{x,k+1}\right) \\
 *     c_{x,k} & = & v_{x,k} \\
 *     d_{x,k} & = & x_k
 *     \end{array}\right.,
 *     \quad\forall k\in[\vert0;N-1\vert]
 * \f]
 *
 * The same procedure is applied for y and z coordinates.
 *
 * \sa Maths::Interpolator::CubicSplineInterpolator
 *********************************************************************/
class CubicSpline3D
{
public:
    //! Default Constructor.
    CubicSpline3D();

    //! Copy constructor
    CubicSpline3D(const CubicSpline3D &other);

    //! Initialization with set of points
    /*!
     * \brief CubicSplineInterpolator3D
     * \param t
     * \param pos
     * \param vel
     */
    CubicSpline3D(const vector &t, vector3d pos, vector3d vel);

    //! Default Destructor
    ~CubicSpline3D();

    // ============== CLASS METHODS ==============
    // *************** GETTER ***************
    /*! ********************************************************************
     * \brief Get minimum t value.
     * \returns The minimum t value of the constructed interpolator.
     *********************************************************************/
    double getTmin() const;

    /*! ********************************************************************
     * \brief Get maximum t value.
     * \returns The maximum t value of the constructed interpolator.
     *********************************************************************/
    double getTmax() const;

    /*! ********************************************************************
     * \brief Get the defining t axis values.
     * \returns A vector containing the defining t axis values (a copy of
     * the input t vector).
     *********************************************************************/
    vector getT() const;

    /*! ********************************************************************
     * \brief Get the interpolator coefficients for x coordinates.
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
    void getCoeffsX(vector &a, vector &b, vector &c, vector &d);

    /*! ********************************************************************
     * \brief Get the interpolator coefficients for y coordinates.
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
    void getCoeffsY(vector &a, vector &b, vector &c, vector &d);

    /*! ********************************************************************
     * \brief Get the interpolator coefficients for z coordinates.
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
    void getCoeffsZ(vector &a, vector &b, vector &c, vector &d);

    // *************** SETTER ***************
    /*! ********************************************************************
     * \brief Set the CubicSplineInterpolator3D points from \f$t\f$, \em pos
     *        and \em vel data.
     * \param [in] t the axis where the function is evaluated.
     * \param [in] pos the position vectors of the function evaluated at
     *             \f$t\f$.
     * \param [in] vel the velocity vectors of the function evaluated at
     *             \f$t\f$.
     * \note This setter method initializes a new CubicSplineInterpolator3D
     *       through its corresponding constructor
     *       CubicSplineInterpolator3D(const vector &t, vector3d pos, vector3d vel).
     *********************************************************************/
    void setPoints(const vector &t, vector3d pos, vector3d vel);

    // ============== OPERATORS ==============
    //! Assignement from another CubicSplineInterpolator3D
    CubicSpline3D operator=(const CubicSpline3D &other);

    /*! ********************************************************************
     * \brief Evaluate the position vector at a given point.
     * \param [in] t the value at which the function is evaluated.
     * \param [out] pos the interpolated position Vector3D.
     * \note This function call doesn't make bound checkings.
     *********************************************************************/
    void operator()(const double &t, Vector3D &pos);

    /*! ********************************************************************
     * \brief Evaluate the position and velocity vectors at a given point.
     * \param [in] t the value at which the function is evaluated.
     * \param [out] pos the interpolated position Vector3D.
     * \param [out] vel the interpolated velocity Vector3D.
     * \note This function call doesn't make bound checkings.
     *********************************************************************/
    void operator()(const double &t, Vector3D &pos, Vector3D &vel);

    /*! ********************************************************************
     * \brief Evaluate the position, velocity and acceleration vectors at a
     *        given point.
     * \param [in] t the value at which the function is evaluated.
     * \param [out] pos the interpolated position Vector3D.
     * \param [out] vel the interpolated velocity Vector3D.
     * \param [out] acc the interpolated acceleration Vector3D.
     * \note This function call doesn't make bound checkings.
     *********************************************************************/
    void operator()(const double &t, Vector3D &pos, Vector3D &vel, Vector3D &acc);

    /*! ********************************************************************
     * \brief Evaluate the position vector at a given point.
     *
     * This function call overload allows efficient call when interpolating
     * between two values of the provided data through the 'index' parameter.
     * (This avoid the search for index).
     *
     * \param [in] t the value at which the function is evaluated.
     * \param [in] index the index to which compute the interpolated values.
     * \param [out] pos the interpolated position Vector3D.
     *
     * \note 1. This function call doesn't make bound checkings.
     * \note 2. It is up to you to check or be sure that \em index and the value
     *          where the vectors are interpolated \em t coincides.
     *********************************************************************/
    void operator()(const double &t, const std::size_t &index,
                    Vector3D &pos);

    /*! ********************************************************************
     * \brief Evaluate the position and velocity vectors at a given point.
     *
     * This function call overload allows efficient call when interpolating
     * between two values of the provided data through the 'index' parameter.
     * (This avoid the search for index).
     *
     * \param [in] t the value at which the function is evaluated.
     * \param [in] index the index to which compute the interpolated values.
     * \param [out] pos the interpolated position Vector3D.
     * \param [out] vel the interpolated velocity Vector3D.
     *
     * \note 1. This function call doesn't make bound checkings.
     * \note 2. It is up to you to check or be sure that \em index and the value
     *          where the vectors are interpolated \em t coincides.
     *********************************************************************/
    void operator()(const double &t, const std::size_t &index,
                    Vector3D &pos, Vector3D &vel);

    /*! ********************************************************************
     * \brief Evaluate the position and velocity vectors at a given point.
     *
     * This function call overload allows efficient call when interpolating
     * between two values of the provided data through the 'index' parameter.
     * (This avoid the search for index).
     *
     * \param [in] t the value at which the function is evaluated.
     * \param [in] index the index to which compute the interpolated values.
     * \param [out] pos the interpolated position Vector3D.
     * \param [out] vel the interpolated velocity Vector3D.
     * \param [out] acc the interpolated acceleration Vector3D.
     *
     * \note 1. This function call doesn't make bound checkings.
     * \note 2. It is up to you to check or be sure that \em index and the value
     *          where the vectors are interpolated \em t coincides.
     *********************************************************************/
    void operator()(const double &t, const std::size_t &index,
                    Vector3D &pos, Vector3D &vel, Vector3D &acc);

    // =========== CUBIC SPLINE METHODS ===========
    /*! ********************************************************************
     * \brief Evaluate the position vector at a given point with bound checkings.
     * \param [in] t the value at which the function is evaluated.
     * \param [in] extrapolate whether to authorize extrapolation or not.
     *             Default to false.
     * \returns The interpolated position Vector3D.
     *********************************************************************/
    Vector3D positionAt(const double &t, bool extrapolate=false);

    /*! ********************************************************************
     * \brief Evaluate the velocity vector at a given point with bound checkings.
     * \param [in] t the value at which the function is evaluated.
     * \param [in] extrapolate whether to authorize extrapolation or not.
     *             Default to false.
     * \returns The interpolated velocity Vector3D.
     *********************************************************************/
    Vector3D velocityAt(const double &t, bool extrapolate=false);

    /*! ********************************************************************
     * \brief Evaluate the acceleration vector at a given point with bound checkings.
     * \param [in] t the value at which the function is evaluated.
     * \param [in] extrapolate whether to authorize extrapolation or not.
     *             Default to false.
     * \returns The interpolated acceleration Vector3D.
     *********************************************************************/
    Vector3D accelerationAt(const double &t, bool extrapolate=false);

private:
    double m_tmin, m_tmax;         // Min and max value of interpolation
    vector m_t;                    // Provided axis for interpolation
    vector m_ax, m_bx, m_cx, m_dx, // Interpolation coefficients of x axis
           m_ay, m_by, m_cy, m_dy, // y axis
           m_az, m_bz, m_cz, m_dz; // z axis
    std::size_t m_n;               // Size of coefficients container
};

} // namespace Osl::Geometry::Interpolator3D

} // namespace Osl::Geometry

} // namespace Osl

#endif // OSL_GEOMETRY_INTERPOLATOR3D_CUBICSPLINE3D_H
