#include "Vector3D.h"

namespace Osl {

namespace Geometry {

// ============== CONSTRUCTOR ==============
Vector3D::Vector3D(){}

Vector3D::Vector3D(const double &x, const double &y, const double &z)
    : m_x(x), m_y(y), m_z(z){}

// Copy constructor
Vector3D::Vector3D(const Vector3D &other)
    : m_x(other.m_x), m_y(other.m_y), m_z(other.m_z) {}

// ============== DESTRUCTOR ==============
Vector3D::~Vector3D(){}

// ============== CLASS METHODS ==============
// ********** SETTER **********
void Vector3D::setX(const double &x){ m_x = x; }
void Vector3D::setY(const double &y){ m_y = y; }
void Vector3D::setZ(const double &z){ m_z = z; }
void Vector3D::setCoordinates(const double &x, const double &y, const double &z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}
// ********** GETTER **********
double Vector3D::getX() const { return m_x; }
double Vector3D::getY() const { return m_y; }
double Vector3D::getZ() const { return m_z; }
void Vector3D::getCoordinates(double &x, double &y, double &z)
{
    x = m_x;
    y = m_y;
    z = m_z;
}

// ============== OPERATORS ==============
// Unary operators
Vector3D Vector3D::operator-()
{
    return Vector3D(-m_x, -m_y, -m_z);
}

    // Operations between vectors
// Assignement from another vector
Vector3D Vector3D::operator=(const Vector3D &other)
{
    m_x = other.m_x;
    m_y = other.m_y;
    m_z = other.m_z;
    return *this;
}

// Summation between vectors
Vector3D Vector3D::operator+(const Vector3D &other)
{
    return Vector3D(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
}

Vector3D &Vector3D::operator+=(const Vector3D &other)
{
    m_x += other.m_x;
    m_y += other.m_y;
    m_z += other.m_z;
    return *this;
}

// Differenciation between vectors
Vector3D Vector3D::operator-(const Vector3D &other)
{
    return Vector3D(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
}

Vector3D &Vector3D::operator-=(const Vector3D &other)
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    m_z -= other.m_z;
    return *this;
}

    // Scalar operations
// Multiplication
Vector3D Vector3D::operator*(const double &rhs)
{
    return Vector3D(m_x * rhs, m_y * rhs, m_z * rhs);
}

Vector3D &Vector3D::operator*=(const double &rhs)
{
    m_x *= rhs;
    m_y *= rhs;
    m_z *= rhs;
    return *this;
}

// Division
Vector3D Vector3D::operator/(const double &rhs)
{
    return Vector3D(m_x / rhs, m_y / rhs, m_z / rhs);
}

Vector3D &Vector3D::operator/=(const double &rhs)
{
    m_x /= rhs;
    m_y /= rhs;
    m_z /= rhs;
    return *this;
}

    // Comparison operators
bool Vector3D::operator==(const Vector3D &other) const
{
    return Maths::Comparison::almost_equal(m_x, other.m_x) &&
           Maths::Comparison::almost_equal(m_y, other.m_y) &&
           Maths::Comparison::almost_equal(m_z, other.m_z);
}

bool Vector3D::operator!=(const Vector3D &other) const
{
    return !(*this == other);
}

// ============== VECTOR OPERATIONS ==============
double Vector3D::norm2() const
{
    return m_x * m_x + m_y * m_y + m_z * m_z;
}

double Vector3D::norm() const
{
    return std::hypot(m_x, m_y, m_z);
}

double Vector3D::sum() const
{
    return m_x + m_y + m_z;
}

bool Vector3D::isNull() const
{
    return *this == NULL_VEC;
}

void Vector3D::normalize()
{
    double norm = this->norm();
    if (norm > 0.0 && !Maths::Comparison::almost_one(norm))
    {
        m_x /= norm;
        m_y /= norm;
        m_z /= norm;
    }
}

Vector3D Vector3D::normalized()
{
    double norm = this->norm();
    if (norm > 0.0)
    {
        return Vector3D(m_x / norm, m_y / norm, m_z / norm);
    }
    return NULL_VEC;
}

// Vector / Vector operations
double Vector3D::dotProduct(const Vector3D &other)
{
    return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
}

Vector3D Vector3D::crossProduct(const Vector3D &other)
{
    double x, y, z;
    x = m_y * other.m_z - m_z * other.m_y;
    y = m_z * other.m_x - m_x * other.m_z;
    z = m_x * other.m_y - m_y * other.m_x;
    return Vector3D(x, y, z);
}

Vector3D Vector3D::projectOn(const Vector3D &other)
{
    double norm2 = other.norm2();
    if (norm2 > 0)
    {
        double f = this->dotProduct(other) / norm2;
        return Vector3D(f * other.m_x, f * other.m_y, f * other.m_z);
    }
    return NULL_VEC;
}

Vector3D Vector3D::rejectFrom(const Vector3D &other)
{
    return *this - this->projectOn(other);
}

bool Vector3D::isColinear(const Vector3D &other)
{
    return this->crossProduct(other) == NULL_VEC;
}

bool Vector3D::isPerpendicular(const Vector3D &other)
{
    return Maths::Comparison::almost_zero(this->dotProduct(other));
}

} // namespace Osl::Geometry

} // namespace Osl
