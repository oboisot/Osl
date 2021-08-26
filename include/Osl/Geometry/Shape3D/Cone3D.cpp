/*! ********************************************************************
 * \file Cone3D.cpp
 * \brief Source file of Osl::Geometry::Shape3D::Cone3D class.
 *********************************************************************/

#include "Cone3D.h"

namespace Osl {

namespace Geometry {

namespace Shape3D {

// ============== CONSTRUCTOR ==============
Cone3D::Cone3D(){}

Cone3D::Cone3D(const Vector3D &vertex, const double &xangle, const double &yangle,
               bool degrees)
{
    if (degrees)
    {
        this->setXangleDegrees(xangle);
        this->setYangleDegrees(yangle);
    }
    else
    {
        this->setXangleRadians(xangle);
        this->setYangleRadians(yangle);
    }
    m_vertex = vertex;
}

Cone3D::Cone3D(const Vector3D &vertex, const double &xangle, const double &yangle,
               const Rotation3D &rotation, bool degrees)
{
    if (degrees)
    {
        this->setXangleDegrees(xangle);
        this->setYangleDegrees(yangle);
    }
    else
    {
        this->setXangleRadians(xangle);
        this->setYangleRadians(yangle);
    }
    m_rotation = rotation;
    m_vertex = vertex;
}

// Copy constructor
Cone3D::Cone3D(const Cone3D &cone)
    : m_vertex(cone.m_vertex),
      m_xangle(cone.m_xangle), m_yangle(cone.m_yangle),
      m_rotation(cone.m_rotation) {}

// ============== DESTRUCTOR ==============
Cone3D::~Cone3D(){}

// ============== CLASS METHODS ==============
    // Setter
void Cone3D::setVertex(const Vector3D &vertex){ m_vertex = vertex; }
void Cone3D::setVertex(const double &xc, const double &yc, const double &zc)
{
    m_vertex.setCoordinates(xc, yc, zc);
}
void Cone3D::setOpeningAngles(const double &xangle, const double &yangle, bool degrees)
{
    if (degrees)
    {
        this->setXangleDegrees(xangle);
        this->setYangleDegrees(yangle);
    }
    else
    {
        this->setXangleRadians(xangle);
        this->setYangleRadians(yangle);
    }
}

void Cone3D::setOpeningXangle(const double &xangle, bool degrees)
{
    degrees ? this->setXangleDegrees(xangle) : this->setXangleRadians(xangle);
}

void Cone3D::setOpeningYangle(const double &yangle, bool degrees)
{
    degrees ? this->setYangleDegrees(yangle) : this->setYangleRadians(yangle);
}

void Cone3D::setRotation(const Rotation3D &rotation) { m_rotation = rotation; }

    // Getter
Vector3D Cone3D::getVertex() const { return m_vertex; }

double Cone3D::getOpeningXangle(bool degrees) const
{
    if (degrees)
        return m_xangle * Constants::m_radtodeg;
    return m_xangle;
}

double Cone3D::getOpeningYangle(bool degrees) const
{
    if (degrees)
        return m_yangle * Constants::m_radtodeg;
    return m_yangle;
}

Rotation3D Cone3D::getRotation() const { return m_rotation; }

void Cone3D::getOpeningAngles(double &xangle, double &yangle, bool degrees)
{
    if (degrees)
    {
        xangle = m_xangle * Constants::m_radtodeg;
        yangle = m_yangle * Constants::m_radtodeg;
    }
    else
    {
        xangle = m_xangle;
        yangle = m_yangle;
    }
}

void Cone3D::getEllipticConeReferential(Vector3D &xaxis, Vector3D &yaxis, Vector3D &zaxis)
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
Cone3D Cone3D::operator=(const Cone3D &other)
{
    m_vertex = other.m_vertex;
    m_xangle = other.m_xangle;
    m_yangle = other.m_yangle;
    m_rotation = other.m_rotation;
    return *this;
}
    // Comparison operators
bool Cone3D::operator==(const Cone3D &other) const
{
    return m_vertex == other.m_vertex &&
           Maths::Comparison::almost_equal(m_xangle, other.m_xangle) &&
           Maths::Comparison::almost_equal(m_yangle, other.m_yangle) &&
           m_rotation == other.m_rotation;
}

// Function call
Vector3D Cone3D::operator()(const double &f, const double &theta, bool degrees)
{
    double tet_rad = degrees ? theta * Constants::m_degtorad : theta;
    Vector3D point(std::tan(m_xangle) * std::cos(tet_rad) * f,
                   std::tan(m_yangle) * std::sin(tet_rad) * f,
                   f);
    if (m_rotation.isIdentity())
        return point + m_vertex;
    return m_rotation * point + m_vertex;
}


// ============== PRIVATE METHODS ==============
void Cone3D::setXangleDegrees(const double &xangle)
{
    if (xangle > 0.0 && xangle < 90.0)
        m_xangle = xangle * Constants::m_degtorad;
    else
        throw "Opening angle 'xangle' must belong to ]0;90[° interval.";
}

void Cone3D::setYangleDegrees(const double &yangle)
{
    if (yangle > 0.0 && yangle < 90.0)
        m_yangle = yangle * Constants::m_degtorad;
    else
        throw "Opening angle 'yangle' must belong to ]0;90[° interval.";
}

void Cone3D::setXangleRadians(const double &xangle)
{
    if (xangle > 0.0 && xangle < Constants::m_pi_2)
        m_xangle = xangle;
    else
        throw "Opening angle 'xangle' must belong to ]0;pi/2[ rad interval.";
}

void Cone3D::setYangleRadians(const double &yangle)
{
    if (yangle > 0.0 && yangle < Constants::m_pi_2)
        m_yangle = yangle;
    else
        throw "Opening angle 'yangle' must belong to ]0;pi/2[ rad interval.";
}

} // namespace Osl::Geometry::Shape

} // namespace Osl::Geometry

} // namespace Osl
