#include "vector3.h"

namespace Osl {

namespace Geometry {

// ============== CONSTRUCTOR ==============
Vector3::Vector3(){}

Vector3::Vector3(const double &x, const double &y, const double &z)
    : m_x(x), m_y(y), m_z(z){}

// Copy constructor
Vector3::Vector3(const Vector3 &other)
    : m_x(other.m_x), m_y(other.m_y), m_z(other.m_z) {}

// ============== DESTRUCTOR ==============
Vector3::~Vector3(){}

// ============== CLASS METHODS ==============
// ********** SETTER **********
void Vector3::setX(const double &x){ m_x = x; }
void Vector3::setY(const double &y){ m_y = y; }
void Vector3::setZ(const double &z){ m_z = z; }
void Vector3::setCoordinates(const double &x, const double &y, const double &z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}
// ********** GETTER **********
double Vector3::getX() const { return m_x; }
double Vector3::getY() const { return m_y; }
double Vector3::getZ() const { return m_z; }
void Vector3::getCoordinates(double &x, double &y, double &z)
{
    x = m_x;
    y = m_y;
    z = m_z;
}

// ============== OPERATORS ==============
// Unary operators
void Vector3::operator-()
{
    m_x = -m_x;
    m_y = -m_y;
    m_z = -m_z;
}

    // Operations between vectors
// Assignement from another vector
Vector3 Vector3::operator=(const Vector3 &other)
{
    m_x = other.m_x;
    m_y = other.m_y;
    m_z = other.m_z;
    return *this;
}

// Summation between vectors
Vector3 Vector3::operator+(const Vector3 &other)
{
    return Vector3(m_x + other.m_x,
                   m_y + other.m_y,
                   m_z + other.m_z);
}

void Vector3::operator+=(const Vector3 &other)
{
    m_x += other.m_x;
    m_y += other.m_y;
    m_z += other.m_z;
}

// Differenciation between vectors
Vector3 Vector3::operator-(const Vector3 &other)
{
    return Vector3(m_x - other.m_x,
                   m_y - other.m_y,
                   m_z - other.m_z);
}

void Vector3::operator-=(const Vector3 &other)
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    m_z -= other.m_z;
}

    // Scalar operations
// Multiplication
Vector3 Vector3::operator*(const double &rhs)
{
    return Vector3(m_x * rhs,
                   m_y * rhs,
                   m_z * rhs);
}

void Vector3::operator*=(const double &rhs)
{
    m_x *= rhs;
    m_y *= rhs;
    m_z *= rhs;
}

// Division
Vector3 Vector3::operator/(const double &rhs)
{
    return Vector3(m_x / rhs,
                   m_y / rhs,
                   m_z / rhs);
}

void Vector3::operator/=(const double &rhs)
{
    m_x /= rhs;
    m_y /= rhs;
    m_z /= rhs;
}

    // Comparison operators
bool Vector3::operator==(const Vector3 &other) const
{
    return Maths::Comparison::almost_equal(m_x, other.m_x) &&
           Maths::Comparison::almost_equal(m_y, other.m_y) &&
           Maths::Comparison::almost_equal(m_z, other.m_z);
}

bool Vector3::operator!=(const Vector3 &other) const
{
    return !(*this == other);
}

// ============== VECTOR COPY ==============
Vector3 Vector3::clone()
{
    return Vector3(m_x, m_y, m_z);
}

// ============== VECTOR OPERATIONS ==============
double Vector3::norm2() const
{
    return m_x * m_x + m_y * m_y + m_z * m_z;
}

double Vector3::norm() const
{
    return std::hypot(m_x, m_y, m_z);
}

double Vector3::sum() const
{
    return m_x + m_y + m_z;
}

bool Vector3::isNull() const
{
    return *this == NULL_VEC;
}

void Vector3::normalize()
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
double Vector3::dotProduct(const Vector3 &other)
{
    return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
}

void Vector3::crossProduct(const Vector3 &other)
{
    double x, y, z;
    x = m_y * other.m_z - m_z * other.m_y;
    y = m_z * other.m_x - m_x * other.m_z;
    z = m_x * other.m_y - m_y * other.m_x;
    m_x = x;
    m_y = y;
    m_z = z;
}

void Vector3::projectOn(const Vector3 &other)
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

void Vector3::rejectFrom(const Vector3 &other)
{
    double x = m_x, y = m_y, z = m_z; // We keep old coordinates
    this->projectOn(other);
    m_x = x - m_x;
    m_y = y - m_y;
    m_z = z - m_z;
}

bool Vector3::isColinear(const Vector3 &other)
{
    // Vector3 tmp = this->clone();
    // tmp.crossProduct(other);
    // return  tmp == NULL_VEC;
    return this->clone().crossProduct(other) == NULL_VEC;
}

bool Vector3::isPerpendicular(const Vector3 &other)
{
    return Maths::Comparison::almost_zero(this->dotProduct(other));
}

} // namespace Osl::Geometry

} // namespace Osl
