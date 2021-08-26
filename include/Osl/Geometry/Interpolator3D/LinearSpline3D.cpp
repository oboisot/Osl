/*! ********************************************************************
 * \file LinearSpline3D.cpp
 * \brief Source file of Osl::Geometry::Interpolator3D::LinearSpline3D
 *        class.
 *********************************************************************/


#include "LinearSpline3D.h"

namespace Osl { // namespace Osl

namespace Geometry { // namespace Osl::Geometry

namespace Interpolator3D { // namespace Osl::Geometry::Interpolator

// ============== CONSTRUCTOR ==============
LinearSpline3D::LinearSpline3D(){}

LinearSpline3D::LinearSpline3D(const vector &t, vector3d vec)
{
    // Assertions
        // Checking that at least 2 points are provided
    std::size_t tsize(t.size()), vecsize(vec.size());
    if (tsize < 2)
        throw std::invalid_argument("LinearSpline3D constructor:\n"
                                    "\t't' and 'vec' must be of size at least 2.");
    if (tsize != vecsize)
        throw std::invalid_argument("LinearSpline3D constructor:\n"
                                    "\t't' and 'vec' must have same size.");
        // Checking that 't' is in strictly increasing order.
    for (vector::const_iterator it = t.begin() ; it != t.end() - 1 ; ++it)
    {
        if (*it >= *(it+1))
            throw std::invalid_argument("LinearSpline3D constructor:\n"
                                        "\t't' vector must be in strictly increasing order.");
    }

    // Getting min and max values of interpolator
    m_tmin = t.front();
    m_tmax = t.back();

    // Setting provided time axis
    m_t = t;

    // Setting size of x axis and coefficients vectors
    m_n = tsize - 1;

    // Initialization of coefficients vectors
        // x axis
    m_ax.reserve(m_n);
    m_bx.reserve(m_n);
        // y axis
    m_ay.reserve(m_n);
    m_by.reserve(m_n);
        // z axis
    m_az.reserve(m_n);
    m_bz.reserve(m_n);

    // Linear interpolator coefficients
    double inv_dt;
    double xi, yi, zi, xip1, yip1, zip1;
    // First coordinates
    vec.front().getCoordinates(xi, yi, zi);
    for (std::size_t i = 0 ; i < m_n ; ++i)
    {
        inv_dt = 1.0 / (t[i+1] - t[i]);  // Get time variation between i and i+1
        vec[i+1].getCoordinates(xip1, yip1, zip1); // Get coordinates at index i+1

        // x axis
        m_ax[i] = (xip1 - xi) * inv_dt;
        m_bx[i] = xi;
        // y axis
        m_ay[i] = (yip1 - yi) * inv_dt;
        m_by[i] = yi;
        // z axis
        m_az[i] = (zip1 - zi) * inv_dt;
        m_bz[i] = zi;

        // update x, y, and z values for next index (avoid a new call to getCoordinates)
        xi = xip1;
        yi = yip1;
        zi = zip1;
    }
}

// Copy constructor
LinearSpline3D::LinearSpline3D(const LinearSpline3D &other)
    : m_tmin(other.m_tmin), m_tmax(other.m_tmax),
      m_t(other.m_t),
      m_ax(other.m_ax), m_bx(other.m_bx),
      m_ay(other.m_ay), m_by(other.m_by),
      m_az(other.m_az), m_bz(other.m_bz),
      m_n(other.m_n) {}

// ============== DESTRUCTOR ==============
LinearSpline3D::~LinearSpline3D(){}

// ============== CLASS METHODS ==============
// *************** GETTER ***************
double LinearSpline3D::getTmin() const { return m_tmin; }
double LinearSpline3D::getTmax() const { return m_tmax; }
vector LinearSpline3D::getT() const { return m_t; }
void LinearSpline3D::getCoeffsX(vector &a, vector &b)
{
    a.resize(m_n);
    b.resize(m_n);
    for (std::size_t i = 0 ; i < m_n ; ++i)
    {
        a[i] = m_ax[i];
        b[i] = m_bx[i];
    }
}
void LinearSpline3D::getCoeffsY(vector &a, vector &b)
{
    a.resize(m_n);
    b.resize(m_n);
    for (std::size_t i = 0 ; i < m_n ; ++i)
    {
        a[i] = m_ay[i];
        b[i] = m_by[i];
    }
}
void LinearSpline3D::getCoeffsZ(vector &a, vector &b)
{
    a.resize(m_n);
    b.resize(m_n);
    for (std::size_t i = 0 ; i < m_n ; ++i)
    {
        a[i] = m_az[i];
        b[i] = m_bz[i];
    }
}

// *************** SETTER ***************
void LinearSpline3D::setPoints(const vector &t, vector3d vec)
{
    *this = LinearSpline3D(t, vec);
}

// ============== OPERATORS ==============
// Assignement from another LinearInterpolator3D
LinearSpline3D LinearSpline3D::operator=(const LinearSpline3D &other)
{
    m_tmin = other.m_tmin;
    m_tmax = other.m_tmax;
    m_t = other.m_t;
    m_ax = other.m_ax, m_bx = other.m_bx;
    m_ay = other.m_ay, m_by = other.m_by;
    m_az = other.m_az, m_bz = other.m_bz;
    m_n = other.m_n;
    return *this;
}

void LinearSpline3D::operator()(const double &t, Vector3D &vec)
{
    // Search index of coefficients for interpolation
    std::size_t index;
    if (t >= m_tmax)
    {
        index = m_n - 1;
    }
    else if (t <= m_tmin)
    {
        index = 0;
    }
    else
    {
        // Search index of coefficients for interpolation
        index = m_t.rend() -
                std::find_if(m_t.rbegin(), m_t.rend(),
                             [&t](double tt){return tt <= t;}) - 1;
    }
    // Compute the interpolated values
    double dt = t - m_t[index];
    vec.setCoordinates(m_ax[index] * dt + m_bx[index],
                       m_ay[index] * dt + m_by[index],
                       m_az[index] * dt + m_bz[index]);
}

void LinearSpline3D::operator()(const double &t, const std::size_t &index,
                                Vector3D &vec)
{
    // Compute the interpolated values
    double dt = t - m_t[index];
    vec.setCoordinates(m_ax[index] * dt + m_bx[index],
                       m_ay[index] * dt + m_by[index],
                       m_az[index] * dt + m_bz[index]);
}

// =========== LINEAR SPLINE METHODS ===========
Vector3D LinearSpline3D::vectorAt(const double &t, bool extrapolate)
{

    if (!extrapolate && ((t < m_tmin) || (t > m_tmax)))
        throw std::invalid_argument("LinearSpline3D::vectorAt\n"
                                    "Extrapolation is not authorized. To enable"
                                    "extrapolation, provide argument 'extrapolate'"
                                    "to 'true'.");
    // Search index of coefficients for interpolation
    std::size_t index;
    if (t >= m_tmax)
    {
        index = m_n - 1;
    }
    else if (t <= m_tmin)
    {
        index = 0;
    }
    else
    {
        // Search index of coefficients for interpolation
        index = m_t.rend() -
                std::find_if(m_t.rbegin(), m_t.rend(),
                             [&t](double tt){return tt <= t;}) - 1;
    }
    // Compute the interpolated values
    double dt = t - m_t[index];
    return Vector3D(m_ax[index] * dt + m_bx[index],
                    m_ay[index] * dt + m_by[index],
                    m_az[index] * dt + m_bz[index]);
}

} // namespace Osl::Geometry::Interpolator

} // namespace Osl::Geometry

} // namespace Osl
