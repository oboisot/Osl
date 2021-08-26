/*! ********************************************************************
 * \file CubicSpline3D.cpp
 * \brief Source file of Osl::Geometry::Interpolator::CubicSpline3D
 *        class.
 *********************************************************************/

#include "CubicSpline3D.h"

namespace Osl { // namespace Osl

namespace Geometry { // namespace Osl::Geometry

namespace Interpolator3D { // namespace Osl::Geometry::Interpolator

// ============== CONSTRUCTOR ==============
CubicSpline3D::CubicSpline3D(){}

CubicSpline3D::CubicSpline3D(const vector &t, vector3d pos, vector3d vel)
{
    // Assertions
        // Checking that at least 2 points are provided
    std::size_t tsize(t.size()), possize(pos.size()), velsize(vel.size());
    if (tsize < 2)
        throw std::invalid_argument("CubicSpline3D constructor:\n"
                                    "\t't', 'pos' and 'vel' must be of size at least 2.");
    if ((tsize != possize) || (tsize != velsize))
        throw std::invalid_argument("CubicSpline3D constructor:\n"
                                    "\t't', 'pos' and 'vel' must have same size.");
        // Checking that 't' is in strictly increasing order.
    for (vector::const_iterator it = t.begin() ; it != t.end() - 1 ; ++it)
    {
        if (*it >= *(it+1))
            throw std::invalid_argument("CubicSpline3D constructor:\n"
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
    m_cx.reserve(m_n);
    m_dx.reserve(m_n);
        // y axis
    m_ay.reserve(m_n);
    m_by.reserve(m_n);
    m_cy.reserve(m_n);
    m_dy.reserve(m_n);
        // z axis
    m_az.reserve(m_n);
    m_bz.reserve(m_n);
    m_cz.reserve(m_n);
    m_dz.reserve(m_n);

    // Linear interpolator coefficients
    double inv_dt, inv_dt2, dxdt, dydt, dzdt;
    double xi, yi, zi, xip1, yip1, zip1,
           vxi, vyi, vzi, vxip1, vyip1, vzip1;
    // First coordinates and velocities
    pos.front().getCoordinates(xi, yi, zi);
    vel.front().getCoordinates(vxi, vyi, vzi);
    for (std::size_t i = 0 ; i < m_n ; ++i)
    {
        inv_dt = 1.0 / (t[i+1] - t[i]);              // Get time variation between i and i+1
        inv_dt2 = inv_dt * inv_dt;
        pos[i+1].getCoordinates(xip1, yip1, zip1);   // Get coordinates at index i+1
        vel[i+1].getCoordinates(vxip1, vyip1, vzip1);// Get velocities at index i+1

        // Cubic Spline interpolator coefficients
        // x and vx axes
        dxdt = (xip1 - xi) * inv_dt;
        m_ax[i] = (-2.0 * dxdt + vxi + vxip1) * inv_dt2;
        m_bx[i] = (3.0 * dxdt - 2.0 * vxi - vxip1) * inv_dt;
        m_cx[i] = vxi;
        m_dx[i] = xi;
        // y and vy axes
        dydt = (yip1 - yi) * inv_dt;
        m_ay[i] = (-2.0 * dydt + vyi + vyip1) * inv_dt2;
        m_by[i] = (3.0 * dydt - 2.0 * vyi - vyip1) * inv_dt;
        m_cy[i] = vyi;
        m_dy[i] = yi;
        // z and vz axes
        dzdt = (zip1 - zi) * inv_dt;
        m_az[i] = (-2.0 * dzdt + vzi + vzip1) * inv_dt2;
        m_bz[i] = (3.0 * dzdt - 2.0 * vzi - vzip1) * inv_dt;
        m_cz[i] = vzi;
        m_dz[i] = zi;

        // Update coordinates and velocitues values for next index (avoid a new call to getCoordinates)
        xi = xip1;
        yi = yip1;
        zi = zip1;
        vxi = vxip1;
        vyi = vyip1;
        vzi = vzip1;
    }
}

// Copy constructor
CubicSpline3D::CubicSpline3D(const CubicSpline3D &other)
    : m_tmin(other.m_tmin), m_tmax(other.m_tmax),
      m_t(other.m_t),
      m_ax(other.m_ax), m_bx(other.m_bx), m_cx(other.m_cx), m_dx(other.m_dx),
      m_ay(other.m_ay), m_by(other.m_by), m_cy(other.m_cy), m_dy(other.m_dy),
      m_az(other.m_az), m_bz(other.m_bz), m_cz(other.m_cz), m_dz(other.m_dz),
      m_n(other.m_n) {}

// ============== DESTRUCTOR ==============
CubicSpline3D::~CubicSpline3D(){}

// ============== CLASS METHODS ==============
// *************** GETTER ***************
double CubicSpline3D::getTmin() const { return m_tmin; }
double CubicSpline3D::getTmax() const { return m_tmax; }
vector CubicSpline3D::getT() const { return m_t; }
void CubicSpline3D::getCoeffsX(vector &a, vector &b, vector &c, vector &d)
{
    a.resize(m_n);
    b.resize(m_n);
    c.resize(m_n);
    d.resize(m_n);
    for (std::size_t i = 0 ; i < m_n ; ++i)
    {
        a[i] = m_ax[i];
        b[i] = m_bx[i];
        c[i] = m_cx[i];
        d[i] = m_dx[i];
    }
}
void CubicSpline3D::getCoeffsY(vector &a, vector &b, vector &c, vector &d)
{
    a.resize(m_n);
    b.resize(m_n);
    c.resize(m_n);
    d.resize(m_n);
    for (std::size_t i = 0 ; i < m_n ; ++i)
    {
        a[i] = m_ay[i];
        b[i] = m_by[i];
        c[i] = m_cy[i];
        d[i] = m_dy[i];
    }
}
void CubicSpline3D::getCoeffsZ(vector &a, vector &b, vector &c, vector &d)
{
    a.resize(m_n);
    b.resize(m_n);
    c.resize(m_n);
    d.resize(m_n);
    for (std::size_t i = 0 ; i < m_n ; ++i)
    {
        a[i] = m_az[i];
        b[i] = m_bz[i];
        c[i] = m_cz[i];
        d[i] = m_dz[i];
    }
}

// *************** SETTER ***************
void CubicSpline3D::setPoints(const vector &t, vector3d pos, vector3d vel)
{
    *this = CubicSpline3D(t, pos, vel);
}

// ============== OPERATORS ==============
// Assignement from another LinearInterpolator3D
CubicSpline3D CubicSpline3D::operator=(const CubicSpline3D &other)
{
    m_tmin = other.m_tmin;
    m_tmax = other.m_tmax;
    m_t = other.m_t;
    m_ax = other.m_ax, m_bx = other.m_bx, m_cx = other.m_cx, m_dx = other.m_dx;
    m_ay = other.m_ay, m_by = other.m_by, m_cy = other.m_cy, m_dy = other.m_dy;
    m_az = other.m_az, m_bz = other.m_bz, m_cz = other.m_cz, m_dz = other.m_dz;
    m_n = other.m_n;
    return *this;
}

void CubicSpline3D::operator()(const double &t, Vector3D &pos)
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
    double dt = t - m_t[index],
           dt2 = dt * dt,
           dt3 = dt2 * dt;
    pos.setCoordinates(m_ax[index] * dt3 + m_bx[index] * dt2 + m_cx[index] * dt + m_dx[index],
                       m_ay[index] * dt3 + m_by[index] * dt2 + m_cy[index] * dt + m_dy[index],
                       m_az[index] * dt3 + m_bz[index] * dt2 + m_cz[index] * dt + m_dz[index]);
}

void CubicSpline3D::operator()(const double &t, Vector3D &pos, Vector3D &vel)
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
    double dt = t - m_t[index],
           dt2 = dt * dt,
           dt3 = dt2 * dt;
    double ax = m_ax[index], bx = m_bx[index], cx = m_cx[index], dx = m_dx[index],
           ay = m_ay[index], by = m_by[index], cy = m_cy[index], dy = m_dy[index],
           az = m_az[index], bz = m_bz[index], cz = m_cz[index], dz = m_dz[index];
    pos.setCoordinates(ax * dt3 + bx * dt2 + cx * dt + dx,
                       ay * dt3 + by * dt2 + cy * dt + dy,
                       az * dt3 + bz * dt2 + cz * dt + dz);
    vel.setCoordinates(3.0 * ax * dt2 + 2.0 * bx * dt + cx,
                       3.0 * ay * dt2 + 2.0 * by * dt + cy,
                       3.0 * az * dt2 + 2.0 * bz * dt + cz);
}

void CubicSpline3D::operator()(const double &t, Vector3D &pos, Vector3D &vel, Vector3D &acc)
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
    double dt = t - m_t[index],
           dt2 = dt * dt,
           dt3 = dt2 * dt;
    double ax = m_ax[index], bx = m_bx[index], cx = m_cx[index], dx = m_dx[index],
           ay = m_ay[index], by = m_by[index], cy = m_cy[index], dy = m_dy[index],
           az = m_az[index], bz = m_bz[index], cz = m_cz[index], dz = m_dz[index];
    pos.setCoordinates(ax * dt3 + bx * dt2 + cx * dt + dx,
                       ay * dt3 + by * dt2 + cy * dt + dy,
                       az * dt3 + bz * dt2 + cz * dt + dz);
    vel.setCoordinates(3.0 * ax * dt2 + 2.0 * bx * dt + cx,
                       3.0 * ay * dt2 + 2.0 * by * dt + cy,
                       3.0 * az * dt2 + 2.0 * bz * dt + cz);
    acc.setCoordinates(6.0 * ax * dt + 2.0 * bx,
                       6.0 * ay * dt + 2.0 * by,
                       6.0 * az * dt + 2.0 * bz);
}

void CubicSpline3D::operator()(const double &t, const std::size_t &index,
                               Vector3D &pos)
{
    // Compute the interpolated values
    double dt = t - m_t[index],
           dt2 = dt * dt,
           dt3 = dt2 * dt;
    pos.setCoordinates(m_ax[index] * dt3 + m_bx[index] * dt2 + m_cx[index] * dt + m_dx[index],
                       m_ay[index] * dt3 + m_by[index] * dt2 + m_cy[index] * dt + m_dy[index],
                       m_az[index] * dt3 + m_bz[index] * dt2 + m_cz[index] * dt + m_dz[index]);
}

void CubicSpline3D::operator()(const double &t, const std::size_t &index,
                               Vector3D &pos, Vector3D &vel)
{
    // Compute the interpolated values
    double dt = t - m_t[index],
           dt2 = dt * dt,
           dt3 = dt2 * dt;
    double ax = m_ax[index], bx = m_bx[index], cx = m_cx[index], dx = m_dx[index],
           ay = m_ay[index], by = m_by[index], cy = m_cy[index], dy = m_dy[index],
           az = m_az[index], bz = m_bz[index], cz = m_cz[index], dz = m_dz[index];
    pos.setCoordinates(ax * dt3 + bx * dt2 + cx * dt + dx,
                       ay * dt3 + by * dt2 + cy * dt + dy,
                       az * dt3 + bz * dt2 + cz * dt + dz);
    vel.setCoordinates(3.0 * ax * dt2 + 2.0 * bx * dt + cx,
                       3.0 * ay * dt2 + 2.0 * by * dt + cy,
                       3.0 * az * dt2 + 2.0 * bz * dt + cz);
}

void CubicSpline3D::operator()(const double &t, const std::size_t &index,
                               Vector3D &pos, Vector3D &vel, Vector3D &acc)
{
    // Compute the interpolated values
    double dt = t - m_t[index],
           dt2 = dt * dt,
           dt3 = dt2 * dt;
    double ax = m_ax[index], bx = m_bx[index], cx = m_cx[index], dx = m_dx[index],
           ay = m_ay[index], by = m_by[index], cy = m_cy[index], dy = m_dy[index],
           az = m_az[index], bz = m_bz[index], cz = m_cz[index], dz = m_dz[index];
    pos.setCoordinates(ax * dt3 + bx * dt2 + cx * dt + dx,
                       ay * dt3 + by * dt2 + cy * dt + dy,
                       az * dt3 + bz * dt2 + cz * dt + dz);
    vel.setCoordinates(3.0 * ax * dt2 + 2.0 * bx * dt + cx,
                       3.0 * ay * dt2 + 2.0 * by * dt + cy,
                       3.0 * az * dt2 + 2.0 * bz * dt + cz);
    acc.setCoordinates(6.0 * ax * dt + 2.0 * bx,
                       6.0 * ay * dt + 2.0 * by,
                       6.0 * az * dt + 2.0 * bz);
}

// =========== CUBIC SPLINE METHODS ===========
// Position Vectors
Vector3D CubicSpline3D::positionAt(const double &t, bool extrapolate)
{
    if (!extrapolate && ((t < m_tmin) || (t > m_tmax)))
        throw std::invalid_argument("CubicSpline3D::positionAt\n"
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
    double dt = t - m_t[index],
           dt2 = dt * dt,
           dt3 = dt2 * dt;
    return Vector3D(m_ax[index] * dt3 + m_bx[index] * dt2 + m_cx[index] * dt + m_dx[index],
                    m_ay[index] * dt3 + m_by[index] * dt2 + m_cy[index] * dt + m_dy[index],
                    m_az[index] * dt3 + m_bz[index] * dt2 + m_cz[index] * dt + m_dz[index]);
}

// Veclocity Vectors
Vector3D CubicSpline3D::velocityAt(const double &t, bool extrapolate)
{
    if (!extrapolate && ((t < m_tmin) || (t > m_tmax)))
        throw std::invalid_argument("CubicSpline3D::positionAt\n"
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
    double dt = t - m_t[index],
           dt2 = dt * dt;
    return Vector3D(3.0 * m_ax[index] * dt2 + 2.0 * m_bx[index] * dt + m_cx[index],
                    3.0 * m_ay[index] * dt2 + 2.0 * m_by[index] * dt + m_cy[index],
                    3.0 * m_az[index] * dt2 + 2.0 * m_bz[index] * dt + m_cz[index]);
}

// Acceleration Vectors
Vector3D CubicSpline3D::accelerationAt(const double &t, bool extrapolate)
{
    if (!extrapolate && ((t < m_tmin) || (t > m_tmax)))
        throw std::invalid_argument("CubicSpline3D::positionAt\n"
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
    return Vector3D(6.0 * m_ax[index] * dt + 2.0 * m_bx[index],
                    6.0 * m_ay[index] * dt + 2.0 * m_by[index],
                    6.0 * m_az[index] * dt + 2.0 * m_bz[index]);
}

} // namespace Osl::Geometry::Interpolator3D

} // namespace Osl::Geometry

} // namespace Osl
