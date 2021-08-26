/*! ********************************************************************
 * \file Line3D.cpp
 * \brief Source file of Osl::Geometry::Shape3D::Line3D class.
 *********************************************************************/

#include "Line3D.h"

namespace Osl {

namespace Geometry {

namespace Shape3D {

// ============== CONSTRUCTOR ==============
Line3D::Line3D(){}

Line3D::Line3D(const Vector3D &point, const Vector3D &direction)
    : m_point(point), m_direction(direction) {}

// Copy constructor
Line3D::Line3D(const Line3D &other)
    : m_point(other.m_point), m_direction(other.m_direction) {}

// ============== DESTRUCTOR ==============
Line3D::~Line3D(){}

// ============== CLASS METHODS ==============
    // Setter
void Line3D::setPoint(const Vector3D &point)
{
    m_point = point;
}

void Line3D::setPoint(const double &px, const double &py, const double &pz)
{
    m_point.setCoordinates(px, py, pz);
}

void Line3D::setDirection(const Vector3D &direction)
{
    m_direction = direction;
}

void Line3D::setDirection(const double &dx, const double &dy, const double &dz)
{
    m_direction.setCoordinates(dx, dy, dz);
}

    // Getter
Vector3D Line3D::getPoint() const { return m_point; }
Vector3D Line3D::getDirection() const { return m_direction; }

// ============== OPERATORS ==============
// Operations between vectors
Line3D Line3D::operator=(const Line3D &other)
{
    m_point = other.m_point;
    m_direction = other.m_direction;
    return *this;
}

bool Line3D::operator==(const Line3D &other) const
{
    return (m_point == other.m_point) && (m_direction == other.m_direction);
}

bool Line3D::operator!=(const Line3D &other) const
{
    return !(*this == other);
}

// Function call
/* Calculate a point belonging to this line using the line parametric representation.
 * vec(x) = vec(x0) + t * vec(d)
*/
Vector3D Line3D::operator()(const double &t)
{
    return m_point + m_direction * t;
}

} // namespace Osl::Geometry::Shape3D

} // namespace Osl::Geometry

} // namespace Osl

