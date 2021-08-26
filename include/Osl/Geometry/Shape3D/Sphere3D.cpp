/*! ********************************************************************
 * \file Sphere3D.cpp
 * \brief Source file of Osl::Geometry::Shape3D::Sphere3D class.
 *********************************************************************/

#include "Sphere3D.h"

namespace Osl {

namespace Geometry {

namespace Shape3D {

// ============== CONSTRUCTOR ==============
Sphere3D::Sphere3D(){}

Sphere3D::Sphere3D(const Vector3D &center, const double &radius)
    : m_center(center), m_radius((radius > 0) ? radius : 0.0){}

// Definition of a sphere with its reference frame rotated
Sphere3D::Sphere3D(const Vector3D &center, const double &radius, const Rotation3D &rotation)
    : m_center(center), m_radius((radius > 0) ? radius : 0.0),
      m_rotation(rotation) {}

// Copy constructor
Sphere3D::Sphere3D(const Sphere3D &sphere)
    : m_center(sphere.m_center), m_radius(sphere.m_radius),
      m_rotation(sphere.m_rotation) {}

// ============== DESTRUCTOR ==============
Sphere3D::~Sphere3D(){}

// ============== CLASS METHODS ==============
    // Setter
void Sphere3D::setCenter(const Vector3D &center) { m_center = center; }
void Sphere3D::setCenter(const double &xc, const double &yc, const double &zc)
{
    m_center.setX(xc);
    m_center.setY(yc);
    m_center.setZ(zc);
}
void Sphere3D::setRadius(const double &radius) { if (radius > 0) m_radius = radius; }
void Sphere3D::setRotation(const Rotation3D &rotation) { m_rotation = rotation; }
    // Getter
Vector3D Sphere3D::getCenter() const { return m_center; }
double Sphere3D::getRadius() const { return m_radius; }
Rotation3D Sphere3D::getRotation() const { return m_rotation ; }
        // Get the Sphere referential (useful if it has been rotated)
void Sphere3D::getSphereReferential(Vector3D &xaxis, Vector3D &yaxis, Vector3D &zaxis)
{
    // rotation = (xaxis, yaxis, zaxis)
    xaxis = Vector3D(m_rotation.getCoeff(0, 0),
                     m_rotation.getCoeff(1, 0),
                     m_rotation.getCoeff(2, 0));
    yaxis = Vector3D(m_rotation.getCoeff(0, 1),
                     m_rotation.getCoeff(1, 1),
                     m_rotation.getCoeff(2, 1));
    zaxis = Vector3D(m_rotation.getCoeff(0, 2),
                     m_rotation.getCoeff(1, 2),
                     m_rotation.getCoeff(2, 2));
}

// ============== OPERATORS ==============
// Operations between vectors
Sphere3D Sphere3D::operator=(const Sphere3D &other)
{
    m_center = other.m_center;
    m_radius = other.m_radius;
    m_rotation = other.m_rotation;
    return *this;
}

// Comparison operators
bool Sphere3D::operator==(const Sphere3D &other) const
{
    return m_center == other.m_center &&
           Maths::Comparison::almost_equal(m_radius, other.m_radius) &&
           m_rotation == other.m_rotation;
}

bool Sphere3D::operator!=(const Sphere3D &other) const
{
    return !(*this == other);
}

// Function call
// Compute a point belonging to the sphere from its center using the parametric form:
// x(lambda, phi) = radius*cos(phi)*cos(lambda)
// y(lambda, phi) = radius*cos(phi)*sin(lambda)
// z(lambda, phi) = radius*sin(phi)
// where: -pi < lambda <= pi and -pi/2 <= phi <= pi/2 (radians)
//        -180 < lambda <= 180 and -90 <= phi <= 90   (degrees)
Vector3D Sphere3D::operator()(const double &lambda, const double &phi, bool degrees)
{
    double l = lambda, p = phi;
    if (degrees)
    {
        l *= Constants::m_degtorad;
        p *= Constants::m_degtorad;
    }
    double cp = std::cos(p), sp = std::sin(p);
    double cl = std::cos(l), sl = std::sin(l);
    Vector3D point(m_radius * cp * cl,
                   m_radius * cp * sl,
                   m_radius * sp);
    if (m_rotation.isIdentity())
        return point + m_center;
    return m_rotation * point + m_center;
}

// ============== SPHERE3D METHODS ==============
void Sphere3D::scale(const double &scale)
{
    if (scale > 0)
        m_radius *= scale;
    else
        throw std::invalid_argument("'scale' factor must be strictly positive.");
}

Sphere3D Sphere3D::scaled(const double &scale)
{
    if (scale > 0)
        return Sphere3D(m_center, m_radius * scale, m_rotation);
    throw std::invalid_argument("'scale' factor must be strictly positive.");
}

} // namespace Osl::Geometry::Shape

} // namespace Osl::Geometry

} // namespace Osl
