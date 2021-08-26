/*! ********************************************************************
 * \file Ellipsoid3D.cpp
 * \brief Header file of Osl::Geometry::Shape3D::Ellipsoid3D class.
 *********************************************************************/

#include "Ellipsoid3D.h"

namespace Osl {

namespace Geometry {

namespace Shape3D {

// ============== CONSTRUCTOR ==============
Ellipsoid3D::Ellipsoid3D(){}

Ellipsoid3D::Ellipsoid3D(const Vector3D &center,
                         const double &xradius, const double &yradius, const double &zradius)
    : m_center(center), m_xradius(xradius), m_yradius(yradius), m_zradius(zradius) {}

Ellipsoid3D::Ellipsoid3D(const Vector3D &center,
                         const double &xradius, const double &yradius, const double &zradius,
                         const Vector3D &u, const Vector3D &v, const Vector3D &w)
    : m_center(center),
      m_xradius(xradius), m_yradius(yradius), m_zradius(zradius),
      m_u(u), m_v(v), m_w(w)
{
    // (       )       (r00, r01, r02)
    // (u, v, w) = R = (r10, r11, r12)
    // (       )       (r20, r21, r22)
    m_u.normalize();
    m_v.normalize();
    m_w.normalize();
    double r00, r01, r02,
           r10, r11, r12,
           r20, r21, r22;
    m_u.getCoordinates(r00, r10, r20);
    m_v.getCoordinates(r01, r11, r21);
    m_w.getCoordinates(r02, r12, r22);
    m_rotation.setRotation(r00, r01, r02,
                           r10, r11, r12,
                           r20, r21, r22);
}

Ellipsoid3D::Ellipsoid3D(const Vector3D &center,
                         const double &xradius, const double &yradius, const double &zradius,
                         const Rotation3D &rotation)
    : m_center(center),
      m_xradius(xradius), m_yradius(yradius), m_zradius(zradius),
      m_rotation(rotation)
{
    // (       )       (r00, r01, r02)
    // (u, v, w) = R = (r10, r11, r12)
    // (       )       (r20, r21, r22)
    m_u.setCoordinates(m_rotation.getCoeff(0, 0),
                       m_rotation.getCoeff(1, 0),
                       m_rotation.getCoeff(2, 0));
    m_v.setCoordinates(m_rotation.getCoeff(0, 1),
                       m_rotation.getCoeff(1, 1),
                       m_rotation.getCoeff(2, 1));
    m_w.setCoordinates(m_rotation.getCoeff(0, 2),
                       m_rotation.getCoeff(1, 2),
                       m_rotation.getCoeff(2, 2));
}

// Copy constructor
Ellipsoid3D::Ellipsoid3D(const Ellipsoid3D &other)
    : m_center(other.m_center),
      m_xradius(other.m_xradius), m_yradius(other.m_yradius), m_zradius(other.m_zradius),
      m_rotation(other.m_rotation),
      m_u(other.m_u), m_v(other.m_v), m_w(other.m_w){}

// ============== DESTRUCTOR ==============
Ellipsoid3D::~Ellipsoid3D(){}

// ============== CLASS METHODS ==============
    // Setter
void Ellipsoid3D::setCenter(const Vector3D &center) { m_center = center; }
void Ellipsoid3D::setCenter(const double &xc, const double &yc, const double &zc)
{
    m_center.setX(xc);
    m_center.setY(yc);
    m_center.setZ(zc);
}
void Ellipsoid3D::setRadii(const double &xradius, const double &yradius, const double &zradius)
{
    if ((xradius > 0) && (yradius > 0) && (zradius > 0))
    {
        m_xradius = xradius;
        m_yradius = yradius;
        m_zradius = zradius;
    }
}
void Ellipsoid3D::setXradius(const double &xradius) { if (xradius > 0) m_xradius = xradius; }
void Ellipsoid3D::setYradius(const double &yradius) { if (yradius > 0) m_yradius = yradius; }
void Ellipsoid3D::setZradius(const double &zradius) { if (zradius > 0) m_zradius = zradius; }
void Ellipsoid3D::setRotation(const Rotation3D &rotation) { m_rotation = rotation; }

    // Getter
Vector3D Ellipsoid3D::getCenter() const { return m_center; }
double Ellipsoid3D::getXradius() const { return m_xradius; }
double Ellipsoid3D::getYradius() const { return m_yradius; }
double Ellipsoid3D::getZradius() const { return m_zradius; }
Rotation3D Ellipsoid3D::getRotation() const { return m_rotation; }
void Ellipsoid3D::getRadii(double &xradius, double &yradius, double &zradius)
{
    xradius = m_xradius;
    yradius = m_yradius;
    zradius = m_zradius;
}
void Ellipsoid3D::getEllipsoidReferential(Vector3D &xaxis, Vector3D &yaxis, Vector3D &zaxis)
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

// ============== OPERATORS ==============    // Operations between vectors
Ellipsoid3D Ellipsoid3D::operator=(const Ellipsoid3D &other)
{
    m_center = other.m_center;
    m_xradius = other.m_xradius;
    m_yradius = other.m_yradius;
    m_zradius = other.m_zradius;
    m_rotation = other.m_rotation;
    return *this;
}

Ellipsoid3D Ellipsoid3D::operator=(const Sphere3D &other)
{
    m_center = other.getCenter();
    double radius = other.getRadius();
    m_xradius = radius;
    m_yradius = radius;
    m_zradius = radius;
    m_rotation = other.getRotation();
    return *this;
}

// Comparison operators
bool Ellipsoid3D::operator==(const Ellipsoid3D &other) const
{
    return m_center == other.m_center &&
           Maths::Comparison::almost_equal(m_xradius, other.m_xradius) &&
           Maths::Comparison::almost_equal(m_yradius, other.m_yradius) &&
           Maths::Comparison::almost_equal(m_zradius, other.m_zradius) &&
           m_rotation == other.m_rotation;
}

bool Ellipsoid3D::operator!=(const Ellipsoid3D &other) const
{
    return !(*this == other);
}

// Function call
// Compute a point belonging to the ellipsoid from its center using the parametric form:
// x(lambda, phi) = xradius*cos(phi)*cos(lambda)
// y(lambda, phi) = yradius*cos(phi)*sin(lambda)
// z(lambda, phi) = zradius*sin(phi)
// where: -pi < lambda <= pi and -pi/2 <= phi <= pi/2 (radians)
//        -180 < lambda <= 180 and -90 <= phi <= 90   (degrees)
Vector3D Ellipsoid3D::operator()(const double &lambda, const double &phi, bool degrees)
{
    double l = lambda, p = phi;
    if (degrees)
    {
        l *= Constants::m_degtorad;
        p *= Constants::m_degtorad;
    }
    double cp = std::cos(p), sp = std::sin(p);
    double cl = std::cos(l), sl = std::sin(l);
    //
    Vector3D point(m_xradius * cp * cl,
                   m_yradius * cp * sl,
                   m_zradius * sp);
    if (m_rotation.isIdentity())
        return point + m_center;
    return m_rotation * point + m_center;
}

// ============== ELLIPSOID3D METHODS ==============
void Ellipsoid3D::scale(const double &scale)
{
    if (scale > 0.0)
    {
        m_xradius *= scale;
        m_yradius *= scale;
        m_zradius *= scale;
    }
    else
        throw std::invalid_argument("Osl::Geometry::Shape::Ellipsoid3D.scale() error: "
                                    "'scale' factor must be strictly positive.");
}

Ellipsoid3D Ellipsoid3D::scaled(const double &scale)
{
    if (scale > 0.0)
        return Ellipsoid3D(m_center,
                           m_xradius * scale,
                           m_yradius * scale,
                           m_zradius * scale,
                           m_rotation);
    throw std::invalid_argument("Osl::Geometry::Shape::Ellipsoid3D.scaled() error: "
                                "'scale' factor must be strictly positive.");
}

void Ellipsoid3D::xScale(const double &xscale)
{
    if (xscale > 0.0)
        m_xradius *= xscale;
    else
        throw std::invalid_argument("Osl::Geometry::Shape::Ellipsoid3D.xScale() error: "
                                    "'xscale' factor must be strictly positive.");
}

Ellipsoid3D Ellipsoid3D::xScaled(const double &xscale)
{
    if (xscale > 0.0)
        return Ellipsoid3D(m_center,
                           m_xradius * xscale,
                           m_yradius,
                           m_zradius,
                           m_rotation);
    throw std::invalid_argument("Osl::Geometry::Shape::Ellipsoid3D.xScaled() error: "
                                "'xscale' factor must be strictly positive.");
}

void Ellipsoid3D::yScale(const double &yscale)
{
    if (yscale > 0.0)
        m_yradius *= yscale;
    else
        throw std::invalid_argument("Osl::Geometry::Shape::Ellipsoid3D.yScale() error: "
                                    "'yscale' factor must be strictly positive.");
}

Ellipsoid3D Ellipsoid3D::yScaled(const double &yscale)
{
    if (yscale > 0.0)
        return Ellipsoid3D(m_center,
                           m_xradius,
                           m_yradius * yscale,
                           m_zradius,
                           m_rotation);
    throw std::invalid_argument("Osl::Geometry::Shape::Ellipsoid3D.yScaled() error: "
                                "'yscale' factor must be strictly positive.");
}

void Ellipsoid3D::zScale(const double &zscale)
{
    if (zscale > 0.0)
        m_zradius *= zscale;
    else
        throw std::invalid_argument("Osl::Geometry::Shape::Ellipsoid3D.zScale() error: "
                                    "'zscale' factor must be strictly positive.");
}

Ellipsoid3D Ellipsoid3D::zScaled(const double &zscale)
{
    if (zscale > 0.0)
        return Ellipsoid3D(m_center,
                           m_xradius,
                           m_yradius,
                           m_zradius * zscale,
                           m_rotation);
    throw std::invalid_argument("Osl::Geometry::Shape::Ellipsoid3D.zScaled() error: "
                                "'zscale' factor must be strictly positive.");
}

//// Compute a point belonging to the ellipsoid from its center using the parametric form:
//// x(lambda, phi) = xradius*cos(phi)*cos(lambda)
//// y(lambda, phi) = yradius*cos(phi)*sin(lambda)
//// z(lambda, phi) = zradius*sin(phi)
//// where: -pi < lambda <= pi and -pi/2 <= phi <= pi/2 (radians)
////        -180 < lambda <= 180 and -90 <= phi <= 90   (degrees)
//Vector3D Ellipsoid3D::pointAt(const double &lambda, const double &phi, bool degrees)
//{
//    double l = lambda, p = phi;
//    if (degrees)
//    {
//        l *= Constants::m_degtorad;
//        p *= Constants::m_degtorad;
//    }
//    double cp = std::cos(p), sp = std::sin(p);
//    double cl = std::cos(l), sl = std::sin(l);
//    //
//    Vector3D point(m_xradius * cp * cl,
//                   m_yradius * cp * sl,
//                   m_zradius * sp);
//    if (m_rotation.isIdentity())
//        return point + m_center;
//    return m_rotation * point + m_center;
//}

} // namespace Osl::Geometry::Shape

} // namespace Osl::Geometry

} // namespace Osl
