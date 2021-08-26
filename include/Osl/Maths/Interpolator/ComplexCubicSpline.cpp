/*! ********************************************************************
 * \file ComplexCubicSpline.h
 * \brief Source file of Osl::Maths::Interpolator::ComplexCubicSpline
 *        class.
 *********************************************************************/

#include "ComplexCubicSpline.h"

namespace Osl { // Osl namespace

namespace Maths { // Osl::Maths namespace

namespace Interpolator { // Osl::Maths::Interpolator namespace

// ============== PIECEWISE CUBIC SPLINE INTERPOLATOR ==============
// ============== CONSTRUCTOR ==============
ComplexCubicSpline::ComplexCubicSpline(){}

// Copy constructor
ComplexCubicSpline::ComplexCubicSpline(const ComplexCubicSpline &other)
    : m_xmin(other.m_xmin), m_xmax(other.m_xmax),
      m_x(other.m_x),
      m_a(other.m_a), m_b(other.m_b), m_c(other.m_c), m_d(other.m_d),
      m_n(other.m_n) {}

// Initialization with set of points
ComplexCubicSpline::ComplexCubicSpline(const vector &x, const cvector&y,
                                       enum CubicSplineBoundary bc)
{
    // Assertions
        // Checking that at least 2 points are provided
    std::size_t xsize(x.size()), ysize(y.size());
    if (xsize < 3)
        throw std::invalid_argument("ComplexCubicSpline constructor:\n"
                                    "\t'x' and 'y' must be of size at least 3.");
    if (xsize != ysize)
        throw std::invalid_argument("ComplexCubicSpline constructor:\n"
                                    "\t'x' and 'y' must have same size.");
        // Checking that 'x' is in strictly increasing order.
    for (vector::const_iterator it = x.begin() ; it != x.end() - 1 ; ++it)
    {
        if (*it >= *(it+1))
            throw std::invalid_argument("ComplexCubicSpline constructor:\n"
                                        "\t'x' vector must be in strictly increasing order.");
    }

    // Getting min and max values of interpolator
    m_xmin = x.front();
    m_xmax = x.back();

    // Setting provided x axis
    m_x = x;

    // Setting size of x axis and coefficients vectors
    m_n = xsize - 1;

    // Initialization of coefficients vectors
    m_a.reserve(m_n);
    m_b.reserve(m_n);
    m_c.reserve(m_n);
    m_d.reserve(m_n);


    switch (bc)
    {
    case CubicSplineBoundary::natural:
    {
        // Cubic interpolator coefficients using algorithm
        cvector dx(m_n),    // Stock the differential x values dx[i]=x[i+1]-x[i]
                dydx(m_n); // Stock the differential dy/dx values dydx[i]=(y[i+1]-y[i])/(x[i+1]-x[i])
        // STEP 0 - 1
        for (std::size_t i = 0 ; i < m_n ; ++i)
        {
            m_d[i] = y[i];                    // Fill in d coefficient
            dx[i] = x[i+1] - x[i];             // Compute differential x values
            dydx[i] = (y[i+1] - y[i]) / dx[i]; // Compute differential dy/dx values
        }
        // STEP 2 - 3 - 4 - 5 | m_xsize -> n
        complex inv_li;
        cvector u(m_n, complex(0.0, 0.0)),  // Initialization for u[0] = 0
                z(m_n, complex(0.0, 0.0));  // Initialization for z[0] = 0
        for (std::size_t i = 1 ; i < m_n ; ++i)
        {
            inv_li = 1.0 / (2.0 * (x[i+1] - x[i-1]) - dx[i-1] * u[i-1]);
            u[i] = dx[i] * inv_li;
            z[i] = (3.0 * (dydx[i] - dydx[i-1]) - dx[i-1] * z[i-1]) * inv_li;
        }
        // STEP 6
            // First index of the loop
        std::size_t i = m_n - 1;
        m_b[i] = z[i];
        m_c[i] = dydx[i] - Constants::m_2_3 * dx[i] * m_b[i];
        m_a[i] = -Constants::m_1_3 * m_b[i] / dx[i];
        for (std::size_t j = i ; j-- > 0 ;) // loop
        {
            m_b[j] = z[j] - u[j] * m_b[j+1];
            m_c[j] = dydx[j] - Constants::m_1_3 * dx[j] * (m_b[j+1] + 2.0 * m_b[j]);
            m_a[j] = Constants::m_1_3 * (m_b[j+1] - m_b[j]) / dx[j];
        }
        break;
    }
    case CubicSplineBoundary::quadratic:
    {
        // Cubic interpolator coefficients using algorithm
        cvector dx(m_n),    // Stock the differential x values dx[i]=x[i+1]-x[i]
                dydx(m_n); // Stock the differential dy/dx values dydx[i]=(y[i+1]-y[i])/(x[i+1]-x[i])
        // STEP 0 - 1
        for (std::size_t i = 0 ; i < m_n ; ++i)
        {
            m_d[i] = y[i];                    // Fill in d coefficient
            dx[i] = x[i+1] - x[i];             // Compute differential x values
            dydx[i] = (y[i+1] - y[i]) / dx[i]; // Compute differential dy/dx values
        }
        // STEP 2 - 3 - 4 - 5 | m_xsize -> n
        complex inv_li;
        cvector u(m_n, complex(-1.0, 0.0)),  // Initialization for u[0] = 0
                z(m_n, complex(0.0, 0.0));  // Initialization for z[0] = 0
        for (std::size_t i = 1 ; i < m_n ; ++i)
        {
            inv_li = 1.0 / (2.0 * (x[i+1] - x[i-1]) - dx[i-1] * u[i-1]);
            u[i] = dx[i] * inv_li;
            z[i] = (3.0 * (dydx[i] - dydx[i-1]) - dx[i-1] * z[i-1]) * inv_li;
        }
        // STEP 6
            // First index of the loop
        std::size_t i = m_n - 1;
        m_b[i] = z[i] / (1.0 + u[i]); // b(n-1)=b(n)
        m_c[i] = dydx[i] - dx[i] * m_b[i];
        m_a[i] = 0.0;
        for (std::size_t j = i ; j-- > 0 ;) // loop
        {
            m_b[j] = z[j] - u[j] * m_b[j+1];
            m_c[j] = dydx[j] - Constants::m_1_3 * dx[j] * (m_b[j+1] + 2.0 * m_b[j]);
            m_a[j] = Constants::m_1_3 * (m_b[j+1] - m_b[j]) / dx[j];
        }
        break;
    }
    case CubicSplineBoundary::notAKnot:
    {
        // TO DO
        break;
    }
    default:
        throw std::invalid_argument("ComplexCubicSpline constructor:\n"
                                    "\t'bc' is not a valid enumeration.");
    }
}

// Initialization with set of points and first derivatives
ComplexCubicSpline::ComplexCubicSpline(const vector &x, const cvector &y, const cvector &yp)
{
    // Assertions
        // Checking that at least 2 points are provided
    std::size_t xsize(x.size()), ysize(y.size()), ypsize(yp.size());
    if (xsize < 2)
        throw std::invalid_argument("ComplexCubicSpline constructor:\n"
                                    "\t'x', 'y' and 'yp' must be of size at least 2.");
    if ((xsize != ysize) || (xsize != ypsize))
        throw std::invalid_argument("ComplexCubicSpline constructor:\n"
                                    "\t'x', 'y' and 'yp' must have same size.");
        // Checking that 'x' is in strictly increasing order.
    for (vector::const_iterator it = x.begin() ; it != x.end() - 1 ; ++it)
    {
        if (*it >= *(it+1))
            throw std::invalid_argument("ComplexCubicSpline constructor:\n"
                                        "\t'x' vector must be in strictly increasing order.");
    }

    // Getting min and max values of interpolator
    m_xmin = x.front();
    m_xmax = x.back();

    // Setting provided x axis
    m_x = x;

    // Setting size of x axis and coefficients vectors
    m_n = xsize - 1;

    // Initialization of coefficients vectors
    m_a.reserve(m_n);
    m_b.reserve(m_n);
    m_c.reserve(m_n);
    m_d.reserve(m_n);

    // Cubic interpolator coefficients
    complex inv_dx, dydx,
            yi, ypi, yip1, ypip1;
    // First values
    yi = y.front();
    ypi = yp.front();
    for (std::size_t i = 0 ; i < m_n ; ++i)
    {
        inv_dx = 1.0 / (x[i+1] - x[i]); // Get x variation between i and i+1
        yip1 = y[i+1];                  // Get y value at index i+1
        ypip1 = yp[i+1];                // Get yp value at index i+1

        // Compute the Cubic Spline Interpolator coefficients
        dydx = (yip1 - yi) * inv_dx;
        m_a[i] = (-2.0 * dydx + ypi + ypip1) * inv_dx * inv_dx;
        m_b[i] = (3.0 * dydx - 2.0 * ypi - ypip1) * inv_dx;
        m_c[i] = ypi;
        m_d[i] = yi;

        // Update y and yp values for next index
        yi = yip1;
        ypi = ypip1;
    }
}

// ============== DESTRUCTOR ==============
ComplexCubicSpline::~ComplexCubicSpline(){}

// ============== CLASS METHODS ==============
// *************** GETTER ***************
double ComplexCubicSpline::getXmin() const { return m_xmin; }
double ComplexCubicSpline::getXmax() const { return m_xmax; }
vector ComplexCubicSpline::getX() const { return m_x; }
void ComplexCubicSpline::getCoeffs(cvector &a, cvector &b, cvector &c, cvector &d)
{
    a.resize(m_n);
    b.resize(m_n);
    c.resize(m_n);
    d.resize(m_n);
    for (std::size_t i = 0 ; i < m_n ; ++i)
    {
        a[i] = m_a[i];
        b[i] = m_b[i];
        c[i] = m_c[i];
        d[i] = m_d[i];
    }
}

// *************** SETTER ***************
void ComplexCubicSpline::setPoints(const vector &x, const cvector &y,
                                   enum CubicSplineBoundary bc)
{
    *this = ComplexCubicSpline(x, y, bc);
}

void ComplexCubicSpline::setPoints(const vector &x, const cvector &y, const cvector &yp)
{
    *this = ComplexCubicSpline(x, y, yp);
}

// ============== OPERATORS ==============
// Assignement from another vector
ComplexCubicSpline ComplexCubicSpline::operator=(const ComplexCubicSpline &other)
{
    m_xmin = other.m_xmin;
    m_xmax = other.m_xmax;
    m_x = other.m_x;
    m_a = other.m_a;
    m_b = other.m_b;
    m_c = other.m_c;
    m_d = other.m_d;
    m_n = other.m_n;
    return *this;
}

// Function call
void ComplexCubicSpline::operator()(const double &x, complex &y)
{
    // Search index of coefficients for interpolation
    std::size_t index = this->search_index_for_interpolation(x);
    // Compute the interpolated value
    complex dx = x - m_x[index],
            dx2 = dx * dx;
    y = m_a[index] * dx2 * dx + m_b[index] * dx2 + m_c[index] * dx + m_d[index];
}

void ComplexCubicSpline::operator()(const double &x, complex &y, complex &yp)
{
    // Search index of coefficients for interpolation
    std::size_t index = this->search_index_for_interpolation(x);
    // Compute the interpolated value
    complex dx = x - m_x[index],
            dx2 = dx * dx;
    complex a = m_a[index], b = m_b[index], c = m_c[index], d = m_d[index];
    y = a * dx2 * dx + b * dx2 + c * dx + d;
    yp = 3.0 * a * dx2 + 2.0 * b * dx + c;
}

void ComplexCubicSpline::operator()(const double &x, complex &y, complex &yp, complex &ypp)
{
    // Search index of coefficients for interpolation
    std::size_t index = this->search_index_for_interpolation(x);
    // Compute the interpolated value
    complex dx = x - m_x[index],
            dx2 = dx * dx;
    complex a = m_a[index], b = m_b[index], c = m_c[index], d = m_d[index];
    y = a * dx2 * dx + b * dx2 + c * dx + d;
    yp = 3.0 * a * dx2 + 2.0 * b * dx + c;
    ypp = 6.0 * a * dx + 2.0 * b;
}

void ComplexCubicSpline::operator()(const double &x, const std::size_t &index,
                                    complex &y)
{
    // Compute the interpolated value
    complex dx = x - m_x[index],
            dx2 = dx * dx;
    y = m_a[index] * dx2 * dx + m_b[index] * dx2 + m_c[index] * dx + m_d[index];
}

void ComplexCubicSpline::operator()(const double &x, const std::size_t &index,
                                    complex &y, complex &yp)
{
    // Compute the interpolated value
    complex dx = x - m_x[index],
            dx2 = dx * dx;
    complex a = m_a[index], b = m_b[index], c = m_c[index], d = m_d[index];
    y = a * dx2 * dx + b * dx2 + c * dx + d;
    yp = 3.0 * a * dx2 + 2.0 * b * dx + c;
}

void ComplexCubicSpline::operator()(const double &x, const std::size_t &index,
                                    complex &y, complex &yp, complex &ypp)
{
    // Compute the interpolated value
    complex dx = x - m_x[index],
            dx2 = dx * dx;
    complex a = m_a[index], b = m_b[index], c = m_c[index], d = m_d[index];
    y = a * dx2 * dx + b * dx2 + c * dx + d;
    yp = 3.0 * a * dx2 + 2.0 * b * dx + c;
    ypp = 6.0 * a * dx + 2.0 * b;
}

// =========== CUBIC SPLINE METHODS ===========
complex ComplexCubicSpline::at(const double &x, bool extrapolate)
{
    if (!extrapolate && ((x < m_xmin) || (x > m_xmax)))
        throw std::invalid_argument("ComplexCubicSpline.at()\n"
                                    "Extrapolation is not authorized. To enable"
                                    "extrapolation, set argument 'extrapolate'"
                                    "to 'true'.");
    // Search index of coefficients for interpolation
    std::size_t index = this->search_index_for_interpolation(x);
    // Compute the interpolated value
    complex dx = x - m_x[index],
            dx2 = dx * dx;
    return m_a[index] * dx2 * dx +
           m_b[index] * dx2 +
           m_c[index] * dx +
           m_d[index];
}

complex ComplexCubicSpline::prime(const double &x, bool extrapolate)
{
    if (!extrapolate && ((x < m_xmin) || (x > m_xmax)))
        throw std::invalid_argument("ComplexCubicSpline.prime()\n"
                                    "Extrapolation is not authorized. To enable"
                                    "extrapolation, set argument 'extrapolate'"
                                    "to 'true'.");
    // Search index of coefficients for interpolation
    std::size_t index = this->search_index_for_interpolation(x);
    // Compute the interpolated value
    complex dx = x - m_x[index];
    return 3.0 * m_a[index] * dx * dx +
           2.0 * m_b[index] * dx +
           m_c[index];
}

complex ComplexCubicSpline::primeprime(const double &x, bool extrapolate)
{
    if (!extrapolate && ((x < m_xmin) || (x > m_xmax)))
        throw std::invalid_argument("ComplexCubicSpline.primeprime()\n"
                                    "Extrapolation is not authorized. To enable"
                                    "extrapolation, set argument 'extrapolate'"
                                    "to 'true'.");
    // Search index of coefficients for interpolation
    std::size_t index = this->search_index_for_interpolation(x);
    // Compute the interpolated value
    return 6.0 * m_a[index] * (x - m_x[index]) + 2.0 * m_b[index];
}

std::size_t ComplexCubicSpline::search_index_for_interpolation(const double &xeval)
{
    if (xeval >= m_xmax)
        return m_n - 1;
    if (xeval <= m_xmin)
        return 0;
    std::size_t left=0, right=m_n, mid;
    while (right - left > 1)
    {
        mid = (left + right) / 2;
        if (xeval >= m_x[mid])
            left = mid;
        else
            right = mid;
    }
    return left; // We want the value <= x0
}

} // namespace Osl::Maths::Interpolator

} // namespace Osl::Maths

} // namespace Osl


