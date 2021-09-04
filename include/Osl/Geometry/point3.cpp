#include "point3.h"

namespace Osl {

namespace Geometry {

// ============== CONSTRUCTOR ==============
Point3::Point3(){}

Point3::Point3(const double &x, const double &y, const double &z)
    : m_x(x), m_y(y), m_z(z){}

// Copy constructor
Point3::Point3(const Point3 &other)
    : m_x(other.m_x), m_y(other.m_y), m_z(other.m_z) {}

// ============== DESTRUCTOR ==============
Point3::~Point3(){}

// ============== CLASS METHODS ==============
// ********** SETTER **********
void Point3::setX(const double &x){ m_x = x; }
void Point3::setY(const double &y){ m_y = y; }
void Point3::setZ(const double &z){ m_z = z; }
void Point3::setCoordinates(const double &x, const double &y, const double &z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}
// ********** GETTER **********
double Point3::getX() const { return m_x; }
double Point3::getY() const { return m_y; }
double Point3::getZ() const { return m_z; }
void Point3::getCoordinates(double &x, double &y, double &z)
{
    x = m_x;
    y = m_y;
    z = m_z;
}

// ============== OPERATORS ==============
// Unary operators
void Point3::operator-()
{
    m_x = -m_x;
    m_y = -m_y;
    m_z = -m_z;
}

    // Operations between vectors
// Assignement from another vector
Point3 Point3::operator=(const Point3 &other)
{
    m_x = other.m_x;
    m_y = other.m_y;
    m_z = other.m_z;
    return *this;
}

// Summation between vectors
Point3 Point3::operator+(const Point3 &other)
{
    return Point3(m_x + other.m_x,
                  m_y + other.m_y,
                  m_z + other.m_z);
}

void Point3::operator+=(const Point3 &other)
{
    m_x += other.m_x;
    m_y += other.m_y;
    m_z += other.m_z;
}

// Differenciation between vectors
Point3 Point3::operator-(const Point3 &other)
{
    return Point3(m_x - other.m_x,
                  m_y - other.m_y,
                  m_z - other.m_z);
}

void Point3::operator-=(const Point3 &other)
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    m_z -= other.m_z;
}

    // Scalar operations
// Multiplication
Point3 Point3::operator*(const double &rhs)
{
    return Point3(m_x * rhs,
                   m_y * rhs,
                   m_z * rhs);
}

void Point3::operator*=(const double &rhs)
{
    m_x *= rhs;
    m_y *= rhs;
    m_z *= rhs;
}

// Division
Point3 Point3::operator/(const double &rhs)
{
    return Point3(m_x / rhs,
                   m_y / rhs,
                   m_z / rhs);
}

void Point3::operator/=(const double &rhs)
{
    m_x /= rhs;
    m_y /= rhs;
    m_z /= rhs;
}

    // Comparison operators
bool Point3::operator==(const Point3 &other) const
{
    return Maths::Comparison::almost_equal(m_x, other.m_x) &&
           Maths::Comparison::almost_equal(m_y, other.m_y) &&
           Maths::Comparison::almost_equal(m_z, other.m_z);
}

bool Point3::operator!=(const Point3 &other) const
{
    return !(*this == other);
}

// ============== VECTOR COPY ==============
Point3 Point3::clone()
{
    return Point3(m_x, m_y, m_z);
}

// ============== VECTOR OPERATIONS ==============
double Point3::norm2() const
{
    return m_x * m_x + m_y * m_y + m_z * m_z;
}

double Point3::norm() const
{
    return std::hypot(m_x, m_y, m_z);
}

double Point3::sum() const
{
    return m_x + m_y + m_z;
}

bool Point3::isNull() const
{
    return *this == NULL_VEC;
}

void Point3::normalize()
{
    double norm = this->norm();
    if (norm > 0.0)
    {
        m_x /= norm;
        m_y /= norm;
        m_z /= norm;
    }
}

// Vector / Vector operations
double Point3::dotProduct(const Point3 &other)
{
    return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
}

void Point3::crossProduct(const Point3 &other)
{
    double x, y, z;
    x = m_y * other.m_z - m_z * other.m_y;
    y = m_z * other.m_x - m_x * other.m_z;
    z = m_x * other.m_y - m_y * other.m_x;
    m_x = x;
    m_y = y;
    m_z = z;
}

void Point3::projectOn(const Point3 &other)
{
    double norm2 = other.norm2();
    if (norm2 > 0.0)
    {
        double f = this->dotProduct(other) / norm2;
        m_x = f * other.m_x;
        m_y = f * other.m_y;
        m_z = f * other.m_z;
    }
}

void Point3::rejectFrom(const Point3 &other)
{
    double x = m_x, y = m_y, z = m_z; // We keep old coordinates
    this->projectOn(other);
    m_x = x - m_x;
    m_y = y - m_y;
    m_z = z - m_z;
}

bool Point3::isColinear(const Point3 &other)
{
    Point3 tmp = this->clone();
    tmp.crossProduct(other);
    return  tmp == NULL_VEC;
}

bool Point3::isPerpendicular(const Point3 &other)
{
    return Maths::Comparison::almost_zero(this->dotProduct(other));
}

} // namespace Osl::Geometry

} // namespace Osl
