/*! ********************************************************************
 * \file ComplexLinearSpline.cpp
 * \brief Source file of Osl::Maths::Interpolator::ComplexLinearSpline
 *        class.
 *********************************************************************/

#include "ComplexLinearSpline.h"

namespace Osl { // Osl namespace

namespace Maths { // Osl::Maths namespace

namespace Interpolator { // Osl::Maths::Interpolator

// ============== PIECEWISE LINEAR INTERPOLATOR ==============
// ============== CONSTRUCTOR ==============
ComplexLinearSpline::ComplexLinearSpline(){}

ComplexLinearSpline::ComplexLinearSpline(const vector &x, const cvector &y)
{
    // Assertions
        // Checking that at least 2 points are provided
    std::size_t xsize(x.size()), ysize(y.size());
    if (xsize < 2)
        throw std::invalid_argument("ComplexLinearSpline constructor:\n"
                                    "\t'x' and 'y' must be of size at least 2.");
    if (xsize != ysize)
        throw std::invalid_argument("ComplexLinearSpline constructor:\n"
                                    "\t'x' and 'y' must have same size.");
        // Checking that 'x' is in strictly increasing order.
    for (vector::const_iterator it = x.begin() ; it != x.end() - 1 ; ++it)
    {
        if (*it >= *(it+1))
            throw std::invalid_argument("ComplexLinearSpline constructor:\n"
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

    // Linear interpolator coefficients
    for (std::size_t i = 0 ; i < m_n ; ++i)
    {
        m_a[i] = (y[i+1] - y[i]) / (x[i+1] - x[i]);
        m_b[i] = y[i];
    }
}

// Copy constructor
ComplexLinearSpline::ComplexLinearSpline(const ComplexLinearSpline &other)
    : m_xmin(other.m_xmin), m_xmax(other.m_xmax),
      m_x(other.m_x),
      m_a(other.m_a), m_b(other.m_b),
      m_n(other.m_n) {}

// ============== DESTRUCTOR ==============
ComplexLinearSpline::~ComplexLinearSpline(){}

// ============== CLASS METHODS ==============
// *************** GETTER ***************
double ComplexLinearSpline::getXmin() const { return m_xmin; }
double ComplexLinearSpline::getXmax() const { return m_xmax; }
vector ComplexLinearSpline::getX() const { return m_x; }
void ComplexLinearSpline::getCoeffs(cvector &a, cvector &b)
{
    a.resize(m_n);
    b.resize(m_n);
    for (std::size_t i = 0 ; i < m_n ; ++i)
    {
        a[i] = m_a[i];
        b[i] = m_b[i];
    }
}

// *************** SETTER ***************
void ComplexLinearSpline::setPoints(const vector &x, const cvector &y)
{
    *this = ComplexLinearSpline(x, y);
}

// ============== OPERATORS ==============
// Assignement from another LinearInterpolator
ComplexLinearSpline ComplexLinearSpline::operator=(const ComplexLinearSpline &other)
{
    m_xmin = other.m_xmin;
    m_xmax = other.m_xmax;
    m_x = other.m_x;
    m_a = other.m_a;
    m_b = other.m_b;
    m_n = other.m_n;
    return *this;
}

// Function call
void ComplexLinearSpline::operator()(const double &x, complex &y)
{
    // Search index of coefficients for interpolation
    std::size_t index = this->search_index_for_interpolation(x);
    y = m_a[index] * (x - m_x[index]) + m_b[index];
}

void ComplexLinearSpline::operator()(const double &x, const std::size_t &index, complex &y)
{
    y = m_a[index] * (x - m_x[index]) + m_b[index];
}

// =========== LINEAR SPLINE METHODS ===========
complex ComplexLinearSpline::at(const double &x, bool extrapolate)
{
    if (!extrapolate && ((x < m_xmin) || (x > m_xmax)))
        throw std::invalid_argument("ComplexLinearSpline.at()\n"
                                    "Extrapolation is not authorized. To enable"
                                    "extrapolation, set argument 'extrapolate'"
                                    "to 'true'.");
    // Search index of coefficients for interpolation
    std::size_t index = this->search_index_for_interpolation(x);
    return m_a[index] * (x - m_x[index]) + m_b[index];
}

std::size_t ComplexLinearSpline::search_index_for_interpolation(const double &xeval)
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
