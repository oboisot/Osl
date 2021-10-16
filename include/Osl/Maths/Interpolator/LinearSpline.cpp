/*! ********************************************************************
 * \file LinearSpline.cpp
 * \brief Source file of Osl::Maths::Interpolator::LinearSpline class.
 *********************************************************************/

#include "LinearSpline.h"

namespace Osl { // Osl namespace

namespace Maths { // Osl::Maths namespace

namespace Interpolator { // Osl::Maths::Interpolator

// ============== PIECEWISE LINEAR INTERPOLATOR ==============
// ============== CONSTRUCTOR ==============
LinearSpline::LinearSpline(){}

LinearSpline::LinearSpline(const vector &x, const vector &y)
{
    // Assertions
        // Checking that at least 2 points are provided
    std::size_t xsize(x.size()), ysize(y.size());
    if (xsize < 2)
        throw std::invalid_argument("LinearSpline constructor:\n"
                                    "\t'x' and 'y' must be of size at least 2.");
    if (xsize != ysize)
        throw std::invalid_argument("LinearSpline constructor:\n"
                                    "\t'x' and 'y' must have same size.");
        // Checking that 'x' is in strictly increasing order.
    for (vector::const_iterator it = x.begin() ; it != x.end() - 1 ; ++it)
    {
        if (*it >= *(it+1))
            throw std::invalid_argument("LinearSpline constructor:\n"
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
LinearSpline::LinearSpline(const LinearSpline &other)
    : m_xmin(other.m_xmin), m_xmax(other.m_xmax),
      m_x(other.m_x),
      m_a(other.m_a), m_b(other.m_b),
      m_n(other.m_n) {}

// ============== DESTRUCTOR ==============
LinearSpline::~LinearSpline(){}

// ============== CLASS METHODS ==============
// *************** GETTER ***************
double LinearSpline::getXmin() const { return m_xmin; }
double LinearSpline::getXmax() const { return m_xmax; }
vector LinearSpline::getX() const { return m_x; }
void LinearSpline::getCoeffs(vector &a, vector &b)
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
void LinearSpline::setPoints(const vector &x, const vector &y)
{
    *this = LinearSpline(x, y);
}

// ============== OPERATORS ==============
// Assignement from another LinearInterpolator
LinearSpline LinearSpline::operator=(const LinearSpline &other)
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
void LinearSpline::operator()(const double &x, double &y)
{
    // Search index of coefficients for interpolation
    std::size_t index = this->search_index_for_interpolation(x);
    y = m_a[index] * (x - m_x[index]) + m_b[index];
}

void LinearSpline::operator()(const double &x, const std::size_t &index, double &y)
{
    y = m_a[index] * (x - m_x[index]) + m_b[index];
}

// =========== LINEAR SPLINE METHODS ===========
double LinearSpline::at(const double &x, bool extrapolate)
{
    if (!extrapolate && ((x < m_xmin) || (x > m_xmax)))
        throw std::invalid_argument("LinearSpline.at()\n"
                                    "Extrapolation is not authorized. To enable"
                                    "extrapolation, set argument 'extrapolate'"
                                    "to 'true'.");
    // Search index of coefficients for interpolation
    std::size_t index = this->search_index_for_interpolation(x);
    return m_a[index] * (x - m_x[index]) + m_b[index];
}

std::size_t LinearSpline::search_index_for_interpolation(const double &xeval)
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


double linear_interpolation(const vector &x, const vector &y, const double &xeval)
{
    // Search index
    std::size_t size = x.size() - 1,
                index;
    if (xeval >= x.back())
    {
        index = size - 1;
    }
    else if (xeval <= x.front())
    {
        index = 0;
    }
    else
    {
        std::size_t left = 0, right = size, mid;
        while (right - left > 1)
        {
            mid = (left + right) / 2;
            if (xeval >= x[mid])
                left = mid;
            else
                right = mid;
        }
        index = left; // We want the value <= x0
    }
    double x0 = x[index], y0 = y[index];
    return y0 + (y[index+1] - y0) / (x[index+1] - x0) * (xeval - x0);
}

void linear_interpolation(const vector &x, const vector&y, const double &xeval,
                          double &yinterp)
{
    // Search index
    std::size_t size = x.size() - 1,
                index;
    if (xeval >= x.back())
    {
        index = size - 1;
    }
    else if (xeval <= x.front())
    {
        index = 0;
    }
    else
    {
        std::size_t left = 0, right = size, mid;
        while (right - left > 1)
        {
            mid = (left + right) / 2;
            if (xeval >= x[mid])
                left = mid;
            else
                right = mid;
        }
        index = left; // We want the value <= x0
    }
    double x0 = x[index], y0 = y[index];
    yinterp = y0 + (y[index+1] - y0) / (x[index+1] - x0) * (xeval - x0);
}

double linear_interpolation_reg(const vector &x, const vector&y, const double &xeval)
{
    double xmin = x.front(),
           xmax = x.back(),
           inv_dx = 1.0 / (x[1] - x[0]);
    // Search index
    std::size_t index;
    if (xeval >= xmax)
    {
        index = x.size() - 2;
    }
    else if (xeval <= xmin)
    {
        index = 0;
    }
    else
    {
        index = static_cast<std::size_t>((xeval - xmin) * inv_dx);
    }
    double y0 = y[index];
    return y0 + (y[index+1] - y0) * inv_dx * (xeval - x[index]);
}

void linear_interpolation_reg(const vector &x, const vector&y, const double &xeval,
                              double &yinterp)
{
    double xmin = x.front(),
           xmax = x.back(),
           inv_dx = 1.0 / (x[1] - x[0]);
    // Search index
    std::size_t index;
    if (xeval >= xmax)
    {
        index = x.size() - 2;
    }
    else if (xeval <= xmin)
    {
        index = 0;
    }
    else
    {
        index = static_cast<std::size_t>((xeval - xmin) * inv_dx);
    }
    yinterp = y[index];
    yinterp += (y[index+1] - yinterp) * inv_dx * (xeval - x[index]);
}

void linear_interpolation_reg_nochecks(const double *x, const double *y,
                                       const double &xeval, const double &dx,
                                       double &yinterp)
{
    double inv_dx = 1.0 / dx;
    std::size_t index = static_cast<std::size_t>((xeval - x[0]) * inv_dx);
    yinterp = y[index];
    yinterp += (y[index+1] - yinterp) * inv_dx * (xeval - x[index]);
}

} // namespace Osl::Maths::Interpolator

} // namespace Osl::Maths

} // namespace Osl

