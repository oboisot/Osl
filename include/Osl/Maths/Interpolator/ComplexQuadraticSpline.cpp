/*! ********************************************************************
 * \file ComplexQuadraticSpline.cpp
 * \brief Header file of Osl::Maths::Interpolator::ComplexQuadraticSpline
 *        class.
 *********************************************************************/

#include "ComplexQuadraticSpline.h"

namespace Osl { // Osl namespace

namespace Maths { // Osl::Maths namespace

namespace Interpolator { // Osl::Maths::Interpolator namespace

// ============== PIECEWISE QUADRATIC SPLINE INTERPOLATOR ==============
// ============== CONSTRUCTOR ==============
ComplexQuadraticSpline::ComplexQuadraticSpline(){}

// Copy constructor
ComplexQuadraticSpline::ComplexQuadraticSpline(const ComplexQuadraticSpline &other)
    : m_xmin(other.m_xmin), m_xmax(other.m_xmax),
      m_x(other.m_x),
      m_a(other.m_a), m_b(other.m_b), m_c(other.m_c),
      m_n(other.m_n) {}

// Initialization with set of points
ComplexQuadraticSpline::ComplexQuadraticSpline(const vector &x, const cvector &y,
                                               QuadraticSplineBoundary bc)
{
    // Assertions
        // Checking that at least 2 points are provided
    std::size_t xsize(x.size()), ysize(y.size());
    if (xsize < 3)
        throw std::invalid_argument("ComplexQuadraticSpline constructor:\n"
                                    "\t'x' and 'y' must be of size at least 3.");
    if (xsize != ysize)
        throw std::invalid_argument("ComplexQuadraticSpline constructor:\n"
                                    "\t'x' and 'y' must have same size.");
        // Checking that 'x' is in strictly increasing order.
    for (vector::const_iterator it = x.begin() ; it != x.end() - 1 ; ++it)
    {
        if (*it >= *(it+1))
            throw std::invalid_argument("ComplexQuadraticSpline constructor:\n"
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

    switch (bc)
    {
    case QuadraticSplineBoundary::linearFirst:
    {
        // Initialization with a[0] = 0
        m_c[0] = y[0];
        m_b[0] = (y[1] - y[0]) / (x[1] - x[0]);
        m_a[0] = 0.0;
        double inv_dx;
        for (std::size_t i = 1 ; i < m_n ; ++i)
        {
            m_c[i] = y[i];
            m_b[i] = m_b[i-1] + 2.0 * m_a[i-1] * (x[i] - x[i-1]);
            inv_dx = 1.0 / (x[i+1] - x[i]);
            m_a[i] = ((y[i+1] - y[i]) * inv_dx - m_b[i]) * inv_dx;
        }
        break;
    }
    case QuadraticSplineBoundary::linearLast:
    {
        // Initialization with a[n-1] = 0
        std::size_t i = m_n - 1;
        m_c[i] = y[i];
        m_b[i] = (y[i+1] - y[i]) / (x[i+1] - x[i]);
        m_a[i] = 0.0;
        double inv_dx;
        for (std::size_t j = i ; j-- > 0 ;)
        {
            m_c[j] = y[j];
            inv_dx = 1.0 / (x[j+1] - x[j]);
            m_a[j] = (m_b[j+1] - (y[j+1] - y[j]) * inv_dx) * inv_dx;
            m_b[j] = m_b[j+1] - 2.0 * m_a[j] / inv_dx;
        }
        break;
    }
    default:
        throw std::invalid_argument("ComplexQuadraticSpline constructor:\n"
                                    "\t'bc' is not a valid enumeration.");
    }
}

// ============== DESTRUCTOR ==============
ComplexQuadraticSpline::~ComplexQuadraticSpline(){}

// ============== CLASS METHODS ==============
// *************** GETTER ***************
double ComplexQuadraticSpline::getXmin() const { return m_xmin; }
double ComplexQuadraticSpline::getXmax() const { return m_xmax; }
vector ComplexQuadraticSpline::getX() const { return m_x; }
void ComplexQuadraticSpline::getCoeffs(cvector &a, cvector &b, cvector &c)
{
    a.resize(m_n);
    b.resize(m_n);
    c.resize(m_n);
    for (std::size_t i = 0 ; i < m_n ; ++i)
    {
        a[i] = m_a[i];
        b[i] = m_b[i];
        c[i] = m_c[i];
    }
}

// *************** SETTER ***************
void ComplexQuadraticSpline::setPoints(const vector &x, const cvector &y,
                                       enum QuadraticSplineBoundary bc)
{
    *this = ComplexQuadraticSpline(x, y, bc);
}

// ============== OPERATORS ==============
// Assignement from another LinearInterpolator
ComplexQuadraticSpline ComplexQuadraticSpline::operator=(const ComplexQuadraticSpline &other)
{
    m_xmin = other.m_xmin;
    m_xmax = other.m_xmax;
    m_x = other.m_x;
    m_a = other.m_a;
    m_b = other.m_b;
    m_c = other.m_c;
    m_n = other.m_n;
    return *this;
}

// Function call
void ComplexQuadraticSpline::operator()(const double &x, complex &y)
{
    // Search index of coefficients for interpolation
    std::size_t index = this->search_index_for_interpolation(x);
    double dx = x - m_x[index];
    y = m_a[index] * dx * dx + m_b[index] * dx + m_c[index];
}

void ComplexQuadraticSpline::operator()(const double &x, complex &y, complex &yp)
{
    // Search index of coefficients for interpolation
    std::size_t index = this->search_index_for_interpolation(x);
    double dx = x - m_x[index];
    complex a = m_a[index], b = m_b[index];
    y = a * dx * dx + b * dx + m_c[index];
    yp = 2.0 * a * dx + b;
}

void ComplexQuadraticSpline::operator()(const double &x, const std::size_t &index,
                                        complex &y)
{
    double dx = x - m_x[index];
    y = m_a[index] * dx * dx + m_b[index] * dx + m_c[index];
}

void ComplexQuadraticSpline::operator()(const double &x, const std::size_t &index,
                                        complex &y, complex &yp)
{
    double dx = x - m_x[index];
    complex a = m_a[index], b = m_b[index];
    y = a * dx * dx + b * dx + m_c[index];
    yp = 2.0 * a * dx + b;
}

// =========== QUADRATIC SPLINE METHODS ===========
complex ComplexQuadraticSpline::at(const double &x, bool extrapolate)
{
    if (!extrapolate && ((x < m_xmin) || (x > m_xmax)))
        throw std::invalid_argument("ComplexQuadraticSpline.at()\n"
                                    "Extrapolation is not authorized. To enable"
                                    "extrapolation, set argument 'extrapolate'"
                                    "to 'true'.");
    // Search index of coefficients for interpolation
    std::size_t index = this->search_index_for_interpolation(x);
    // Compute the interpolated value
    double dx = x - m_x[index];
    return m_a[index] * dx * dx + m_b[index] * dx + m_c[index];
}

complex ComplexQuadraticSpline::prime(const double &x, bool extrapolate)
{
    if (!extrapolate && ((x < m_xmin) || (x > m_xmax)))
        throw std::invalid_argument("ComplexQuadraticSpline.prime()\n"
                                    "Extrapolation is not authorized. To enable"
                                    "extrapolation, set argument 'extrapolate'"
                                    "to 'true'.");
    // Search index of coefficients for interpolation
    std::size_t index = this->search_index_for_interpolation(x);
    // Compute the interpolated value
    return 2.0 * m_a[index] * (x - m_x[index]) + m_b[index];
}

std::size_t ComplexQuadraticSpline::search_index_for_interpolation(const double &xeval)
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
