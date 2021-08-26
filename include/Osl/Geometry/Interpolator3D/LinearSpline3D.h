/*! ********************************************************************
 * \file LinearSpline3D.h
 * \brief Header file of Osl::Geometry::Interpolator3D::LinearSpline3D
 *        class.
 *********************************************************************/

#ifndef OSL_GEOMETRY_INTERPOLATOR3D_LINEARSPLINE3D_H
#define OSL_GEOMETRY_INTERPOLATOR3D_LINEARSPLINE3D_H

#include <algorithm>
#include "Osl/Geometry/Vector3D.h"

namespace Osl { // namespace Osl

namespace Geometry { // namespace Osl::Geometry

namespace Interpolator3D { // namespace Osl::Geometry::Interpolator

/*! ********************************************************************
 * \brief Class to construct a piecewise Linear Spline interpolator of
 *        a 3D vector.
 *
 * <h3>Principle</h3>
 *
 * Knowing vectors coordinates at a given time \f$t\f$, this
 * class defines a Linear Spline interpolator for each x, y and z
 * coordinates of the vectors.
 *
 * Let a set of temporal points \f$(t_k)_{k\in[\vert0;N\vert]}\f$
 * of size \f$N+1\f$ being in a strictly increasing order:
 *
 * \f[
 *     t_0<t_1<\cdots<t_{n-1}<t_n
 * \f]
 *
 * with their corresponding coordinates
 * \f$(x_k, y_k, z_k)_{k\in[\vert0;N\vert]}\f$.
 *
 * The piecewise Linear Spline interpolation functions at index \f$k\f$
 * for coordinates x, y and z are defined by the first order polynomials:
 *
 * \f[
 *     \begin{split}
 *     f_{x,k}(t) & =a_{x,k}(t-t_k)+b_{x,k} \\
 *     f_{y,k}(t) & =a_{y,k}(t-t_k)+b_{y,k} \\
 *     f_{z,k}(t) & =a_{z,k}(t-t_k)+b_{z,k}
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
 *     (a_{x,k}, b_{x,k})_{k\in[\vert0;N-1\vert]} \\
 *     (f_{y,k})_{k\in[\vert0;N-1\vert]} & \mbox{ with }
 *     (a_{y,k}, b_{y,k})_{k\in[\vert0;N-1\vert]} \\
 *     (f_{z,k})_{k\in[\vert0;N-1\vert]} & \mbox{ with }
 *     (a_{z,k}, b_{z,k})_{k\in[\vert0;N-1\vert]} \\
 *     \end{split}
 * \f]
 *
 * <h3>Computation of the interpolator coefficients</h3>
 *
 * Coefficients are determined by ensuring continuity of the
 * interpolation functions (coordinates) at each interval nodes,
 * resulting in the sytem of equations for the \f$x\f$ coordinate:
 *
 * \f[
 *     \begin{array}{rcl}
 *         f_{x,k}(t_k) & = & x_k\\
 *         f_{x,k}(t_{k+1}) & = & x_{k+1}\\
 *     \end{array}
 * \f]
 *
 * Solving this system results in the evaluation of the coefficients
 * for the piecewise cubic interpolation functions \f$f_{x,k}\f$:
 *
 * \f[
 *     \left\{\begin{array}{rcl}
 *     a_{x,k} & = & \dfrac{x_{k+1}-x_{k}}{t_{k+1}-t_k} \\
 *     b_{x,k} & = & x_k
 *     \end{array}\right.,
 *     \quad\forall k\in[\vert0;N-1\vert]
 * \f]
 *
 * The same procedure is applied for y and z coordinates.
 *
 * \sa Maths::Interpolator::LinearSplineInterpolator
 *********************************************************************/
class LinearSpline3D
{
public:
    //! Default Constructor.
    LinearSpline3D();

    //! Copy constructor
    LinearSpline3D(const LinearSpline3D &other);

    /*!
     * \param t, the set of time variables
     * \param vec, the set of Vector3D corresponding to t
     */
    LinearSpline3D(const vector &t, vector3d vec);

    //! Default Destructor
    ~LinearSpline3D();

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
     * \note The size of these vectors are the size of the input data minus 1.
     *********************************************************************/
    void getCoeffsX(vector &a, vector &b);

    /*! ********************************************************************
     * \brief Get the interpolator coefficients for y coordinates.
     * \param [out] a A vector containing the \f$a_k\f$ coefficients of the
     *        interpolator.
     * \param [out] b A vector containing the \f$b_k\f$ coefficients of the
     *        interpolator.
     * \note The size of these vectors are the size of the input data minus 1.
     *********************************************************************/
    void getCoeffsY(vector &a, vector &b);

    /*! ********************************************************************
     * \brief Get the interpolator coefficients for z coordinates.
     * \param [out] a A vector containing the \f$a_k\f$ coefficients of the
     *        interpolator.
     * \param [out] b A vector containing the \f$b_k\f$ coefficients of the
     *        interpolator.
     * \note The size of these vectors are the size of the input data minus 1.
     *********************************************************************/
    void getCoeffsZ(vector &a, vector &b);

    // *************** SETTER ***************
    /*! ********************************************************************
     * \brief Set the LinearSplineInterpolator3D points from \f$t\f$ and
     *        \em vec data.
     * \param [in] t the axis where the function is evaluated.
     * \param [in] vec the vectors of the function evaluated at \f$t\f$.
     * \note This setter method initializes a new LinearSplineInterpolator3D
     *       through its corresponding constructor
     *       LinearSplineInterpolator3D(const vector &t, vector3d vec).
     *********************************************************************/
    void setPoints(const vector &t, vector3d vec);

    // ============== OPERATORS ==============
    //! Assignement from another LinearSplineInterpolator3D
    LinearSpline3D operator=(const LinearSpline3D &other);

    /*! ********************************************************************
     * \brief Evaluate the vector at a given point.
     * \param [in] t the value at which the function is evaluated.
     * \param [out] vec the interpolated Vector3D.
     * \note This function call doesn't make bound checkings.
     *********************************************************************/
    void operator()(const double &t, Vector3D &vec);

    /*! ********************************************************************
     * \brief Evaluate the vector at a given point.
     *
     * This function call overload allows efficient call when interpolating
     * between two values of the provided data through the 'index' parameter.
     * (This avoid the search for index).
     *
     * \param [in] t the value at which the function is evaluated.
     * \param [in] index the index to which compute the interpolated values.
     * \param [out] vec the interpolated Vector3D.
     *
     * \note 1. This function call doesn't make bound checkings.
     * \note 2. It is up to you to check or be sure that \em index and the value
     *          where the vector is interpolated \em t coincides.
     *********************************************************************/
    void operator()(const double &t, const std::size_t &index, Vector3D &vec);

    // =========== LINEAR SPLINE METHODS ===========
    /*! ********************************************************************
     * \brief Evaluate the vector at a given point with bound checkings.
     * \param [in] t the value at which the function is evaluated.
     * \param [in] extrapolate whether to authorize extrapolation or not.
     *             Default to false.
     * \returns The interpolated Vector3D.
     *********************************************************************/
    Vector3D vectorAt(const double &t, bool extrapolate=false);

private:
    double m_tmin, m_tmax;  // Min and max value of interpolation
    vector m_t;             // Provided axis for interpolation
    vector m_ax, m_bx,      // Interpolation coefficients of x axis
           m_ay, m_by,      // y axis
           m_az, m_bz;      // z axis
    std::size_t m_n;        // Size of coefficients container
};

} // namespace Osl::Geometry::Interpolator3D

} // namespace Osl::Geometry

} // namespace Osl

#endif // OSL_GEOMETRY_INTERPOLATOR3D_LINEARSPLINE3D_H
