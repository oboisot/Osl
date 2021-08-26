#include "vector3.h"

namespace Osl {

namespace Geometry {

// ============== CONSTRUCTOR ==============
Vector3::Vector3(){}

Vector3::Vector3(const double &x, const double &y, const double &z)
    : x(x), y(y), z(z) {}

// Copy constructor
Vector3::Vector3(const Vector3 &other)
    : x(other.x), y(other.y), z(other.z) {}

// ============== DESTRUCTOR ==============
Vector3::~Vector3(){}

// ============== CLASS METHODS ==============
// ********** SETTER **********
void Vector3::setX(const double &xn){ x = xn; }
void Vector3::setY(const double &yn){ y = yn; }
void Vector3::setZ(const double &zn){ z = zn; }
void Vector3::setCoordinates(const double &xn, const double &yn, const double &zn)
{
    x = xn;
    y = yn;
    z = zn;
}
// ********** GETTER **********
double Vector3::getX() const { return x; }
double Vector3::getY() const { return y; }
double Vector3::getZ() const { return z; }
void Vector3::getCoordinates(double &xn, double &yn, double &zn)
{
    xn = x;
    yn = y;
    zn = z;
}

// ============== OPERATORS ==============
// Unary operators
Vector3 Vector3::operator-()
{
    return Vector3(-x, -y, -z);
}

// Operations between vectors
// Assignement from another vector
Vector3 Vector3::operator=(const Vector3 &other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

// Summation between vectors
Vector3 Vector3::operator+(const Vector3 &other)
{
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 &Vector3::operator+=(const Vector3 &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

// Differenciation between vectors
Vector3 Vector3::operator-(const Vector3 &other)
{
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 &Vector3::operator-=(const Vector3 &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

// Scalar operations
// Multiplication
Vector3 Vector3::operator*(const double &rhs)
{
    return Vector3(x * rhs, y * rhs, z * rhs);
}

Vector3 &Vector3::operator*=(const double &rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

// Division
Vector3 Vector3::operator/(const double &rhs)
{
    return Vector3(x / rhs, y / rhs, z / rhs);
}

Vector3 &Vector3::operator/=(const double &rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
}

// Comparison operators
bool Vector3::operator==(const Vector3 &other) const
{
    return Maths::Comparison::almost_equal(x, other.x) &&
           Maths::Comparison::almost_equal(y, other.y) &&
           Maths::Comparison::almost_equal(z, other.z);
}

bool Vector3::operator!=(const Vector3 &other) const
{
    return !(*this == other);
}

// ============== VECTOR OPERATIONS ==============
double Vector3::norm2() const
{
    return x * x + y * y + z * z;
}

double Vector3::norm() const
{
    return std::hypot(x, y, z);
}

double Vector3::sum() const
{
    return x + y + z;
}

void Vector3::normalize()
{
    double norm = this->norm();
    if (norm > 0.0 && !Maths::Comparison::almost_one(norm))
    {
        x /= norm;
        y /= norm;
        z /= norm;
    }
}

Vector3 Vector3::normalized()
{
    double norm = this->norm();
    if (norm > 0.0)
    {
        if (!Maths::Comparison::almost_one(norm))
            return Vector3(x / norm, y / norm, z / norm);
        return *this;
    }
    return NULL_VECTOR;
}

// Vector / Vector operations
double Vector3::dotProduct(const Vector3 &other)
{
    return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::crossProduct(const Vector3 &other)
{
    double xn, yn, zn;
    xn = y * other.z - z * other.y;
    yn = z * other.x - x * other.z;
    zn = x * other.y - y * other.x;
    return Vector3(xn, yn, zn);
}

Vector3 Vector3::projectOn(const Vector3 &other)
{
    double norm2 = other.norm2();
    if (norm2 > 0.0)
    {
        double f = this->dotProduct(other) / norm2;
        return Vector3(f * other.x, f * other.y, f * other.z);
    }
    return NULL_VECTOR;
}

Vector3 Vector3::rejectFrom(const Vector3 &other)
{
    return *this - this->projectOn(other);
}

bool Vector3::isNull() const
{
    return *this == NULL_VECTOR;
}

bool Vector3::isColinear(const Vector3 &other)
{
    return this->crossProduct(other) == NULL_VECTOR;
}

bool Vector3::isPerpendicular(const Vector3 &other)
{
    return Maths::Comparison::almost_zero(this->dotProduct(other));
}

} // namespace Osl::Geometry

} // namespace Osl
