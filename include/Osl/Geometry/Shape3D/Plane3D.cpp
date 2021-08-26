/*! ********************************************************************
 * \file Plane3D.cpp
 * \brief Source file of Osl::Geometry::Shape3D::Plane3D class.
 *********************************************************************/

#include "Plane3D.h"

namespace Osl {

namespace Geometry {

namespace Shape3D {

// ============== CONSTRUCTOR ==============
Plane3D::Plane3D(){}

// Definition from normal and a point. (normal must not be zero!)
// The plane is registered in its Hessian normal form (see : https://mathworld.wolfram.com/HessianNormalForm.html)
Plane3D::Plane3D(const Vector3D &normal, const Vector3D &point)
    : m_normal(normal), m_point(point)
{
    if (m_normal == NULL_VEC)
    {
        throw std::invalid_argument("Osl::Geometry::Shape3D::Plane3D constructor: "
                                    "'normal' vector can't be null.");
    }
    else
    {
        m_normal.normalize();           // Normalized normal
        this->setPlaneVectors();
    }
}

// Definition from two NON COLINEAR vectors of the plane and a point.
// The plane is registered in its Hessian normal form (see : https://mathworld.wolfram.com/HessianNormalForm.html)
Plane3D::Plane3D(const Vector3D &u, const Vector3D &v, const Vector3D &point)
{
    Vector3D uu = u;
    if (!uu.isColinear(v))
    {
        m_point = point;
        m_normal = uu.crossProduct(v); m_normal.normalize();
        this->setPlaneVectors();
    }
    else
        throw std::invalid_argument("Osl::Geometry::Shape3D::Plane3D constructor: "
                                    "'u' and 'v' can't be colinear.");
}

// plane : ax + by + cz + d = 0
Plane3D::Plane3D(const Vector3D &normal, const double &d)
{
    double norm = normal.norm();
    if (norm > 0.0)
    {
        double inv_norm = 1.0 / norm;
        m_normal = normal; m_normal *= inv_norm;
        double md = d * inv_norm;
        if (m_normal.getZ() != 0)
        {
            m_point = Vector3D(0, 0, -md / m_normal.getZ());
        }
        else if (m_normal.getY() != 0)
        {
            m_point = Vector3D(0, -md / m_normal.getY(), 0);
        }
        else if (m_normal.getX() != 0)
        {
            m_point = Vector3D(-md / m_normal.getX(), 0, 0);
        }
        this->setPlaneVectors();
    }
    else
        throw std::invalid_argument("Osl::Geometry::Shape3D::Plane3D constructor: "
                                    "'normal' vector can't be null.");
}

// Copy constructor
Plane3D::Plane3D(const Plane3D &other)
    : m_normal(other.m_normal), m_point(other.m_point),
      m_u(other.m_u), m_v(other.m_v) {}

// ============== DESTRUCTOR ==============
Plane3D::~Plane3D(){}

// ============== CLASS METHODS ==============
    // Setter
void Plane3D::setPoint(const Vector3D &point)
{
    m_point = point;
}

void Plane3D::setPoint(const double &px, const double &py, const double &pz)
{
    m_point.setCoordinates(px, py, pz);
}

void Plane3D::setNormal(const Vector3D &normal)
{
    m_normal = normal;
    m_normal.normalize();
    this->setPlaneVectors();
}

void Plane3D::setNormal(const double &nx, const double &ny, const double &nz)
{
    m_normal.setCoordinates(nx, ny, nz);
    m_normal.normalize();
    this->setPlaneVectors();
}

    // Getter
Vector3D Plane3D::getPoint() const { return m_point; }
Vector3D Plane3D::getNormal() const { return m_normal; }
void Plane3D::getPlaneVectors(Vector3D &u, Vector3D &v)
{
    u = m_u;
    v = m_v;
}

// ============== OPERATORS ==============
// Operations between vectors
Plane3D Plane3D::operator=(const Plane3D &other)
{
    m_point = other.m_point;
    m_normal = other.m_normal;
    m_u = other.m_u;
    m_v = other.m_v;
    return *this;
}

bool Plane3D::operator==(const Plane3D &other) const
{
    return (m_point == other.m_point) && (m_normal == other.m_normal);
}

bool Plane3D::operator!=(const Plane3D &other) const
{
    return !(*this == other);
}

// Function call
// Compute a point belonging to this plane using its parametric form:
// vec(x)(t, s) = t * vec(u) + s * vec(v) + vec(P)
Vector3D Plane3D::operator()(const double &t, const double &s)
{
    return m_point + m_u * t + m_v * s;
}

// ============== PLANE FUNCTIONS ==============
double Plane3D::distanceToOrigin()
{
    return -m_normal.dotProduct(m_point);
}

// Algebraic distance from plane to point.
// (>0 point is in the half-space defined by the plane normal,
//  <0 point is in the opposite half-space defined by the plane normal).
double Plane3D::distanceToPoint(const Vector3D &point)
{
    return m_normal.dotProduct(point) + this->distanceToOrigin();
}

// ============== PRIVATE FUNCTIONS ==============
// Compute two non colinear vectors of the plane
void Plane3D::setPlaneVectors()
{
    if (m_normal.getZ() != 0)
    {
        double z = m_normal.getZ();
        // vec1 = (1, 0, -x/z)
        m_u.setCoordinates(1.0, 0.0, -m_normal.getX() / z);
        m_u.normalize();
        // vec2 = (0, 1, -x/z)
        m_v.setCoordinates(0.0, 1.0, -m_normal.getY() / z);
        m_v.normalize();
    }
    else if (m_normal.getY() != 0)
    {
        double y = m_normal.getY();
        // vec1 = (1, -x/y, 0)
        m_u.setCoordinates(1.0, -m_normal.getX() / y, 0.0);
        m_u.normalize();
        // vec2 = (0, -z/y, 1)
        m_v.setCoordinates(0.0, -m_normal.getZ() / y, 1.0);
        m_v.normalize();
    }
    else if (m_normal.getX() != 0)
    {
        double x = m_normal.getX();
        // vec1 = (-y/x, 1, 0)
        m_u.setCoordinates(-m_normal.getY() / x, 1.0, 0.0);
        m_u.normalize();
        // vec2 = (-z/x, 0, 1)
        m_v.setCoordinates(-m_normal.getZ() / x, 0.0, 1.0);
        m_v.normalize();
    }
}

} // namespace Osl::Geometry::Shape

} // namespace Osl::Geometry

} // namespace Osl
