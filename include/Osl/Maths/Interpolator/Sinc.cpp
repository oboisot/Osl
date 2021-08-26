/*! ********************************************************************
 * \file Sinc.cpp
 * \brief Source file of Osl::Maths::Interpolator::Sinc class.
 *********************************************************************/

#include "Sinc.h"

namespace Osl { // Osl namespace

namespace Maths { // Osl::Maths namespace

namespace Interpolator { // Osl::Maths::Interpolator namespace

// ============== SINC INTERPOLATOR ==============
// ============== CONSTRUCTOR ==============
Sinc::Sinc(){}

// Copy constructor
Sinc::Sinc(const Sinc &other)
    : m_xmin(other.m_xmin), m_xmax(other.m_xmax),
      m_x(other.m_x), m_y(other.m_y),
      m_inv_dx(other.m_inv_dx),
      m_n(other.m_n){}

//
Sinc::Sinc(const vector &x, const vector &y)
{
    // Assertions
        // Checking that at least 3 points are provided
    std::size_t xsize(x.size()), ysize(y.size());
    if (xsize < 3)
        throw std::invalid_argument("Sinc constructor:\n"
                                    "\t'x' and 'y' must be of size at least 3.");
    if (xsize != ysize)
        throw std::invalid_argument("Sinc constructor:\n"
                                    "\t'x' and 'y' must have same size.");
        // Checking that 'x' is in strictly increasing order.
    for (vector::const_iterator it = x.begin() ; it != x.end() - 1 ; ++it)
    {
        if (*it >= *(it+1))
            throw std::invalid_argument("Sinc constructor:\n"
                                        "\t'x' vector must be in strictly increasing order.");
    }

    // Getting min and max values of interpolator
    m_xmin = x.front();
    m_xmax = x.back();

    // Setting provided x axis and y values
    m_x = x;
    m_y = y;

    // inverse of xaxis variation
    m_inv_dx = 1.0 / (x[1] - x[0]);
    //
    m_n = xsize;
}

// ============== DESTRUCTOR ==============
Sinc::~Sinc(){}

// ============== CLASS METHODS ==============
// *************** GETTER ***************
double Sinc::getXmin() const { return m_xmin; }
double Sinc::getXmax() const { return m_xmax; }
vector Sinc::getX() const { return m_x; }

// *************** SETTER ***************
void Sinc::setPoints(const vector &x, const vector &y)
{
    *this = Sinc(x, y);
}

// ============== OPERATORS ==============
// Assignement from another vector
Sinc Sinc::operator=(const Sinc &other)
{
    m_xmin = other.m_xmin;
    m_xmax = other.m_xmax;
    m_x = other.m_x;
    m_y = other.m_y;
    m_inv_dx = other.m_inv_dx;
    m_n = other.m_n;
    return *this;
}

// Function call
void Sinc::operator()(const double &x, double &y)
{
    double pi_inv_dx = Constants::m_pi * m_inv_dx;
    y = std::transform_reduce(m_x.begin(), m_x.end(),
                              m_y.begin(),
                              0.0,
                              std::plus<>(),
                              [&x, &pi_inv_dx](double xx, double yy) // Apply sinc kernel
                                  {
                                      double arg = pi_inv_dx * (x - xx);
                                      if (Comparison::almost_zero(arg))
                                          return yy;
                                      return std::sin(arg) / arg * yy;
                                  });
}

} // namespace Osl::Maths::Interpolator

} // namespace Osl::Maths

} // namespace Osl
