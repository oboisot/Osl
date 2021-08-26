/*! ********************************************************************
 * \file GeoPoint.cpp
 * \brief Source file of Osl::Geography::GeoPoint class.
 *********************************************************************/

#include "GeoPoint.h"

namespace Osl { // namespace Osl

namespace Geography { // namespace Osl::Geography

// ============== CONSTRUCTOR ==============
GeoPoint::GeoPoint() : m_elps(WGS84) {} // L'initialisation de m_elps doit être explicite (référence)

//!
GeoPoint::GeoPoint(Ellipsoid &elps, const Geometry::Vector3D &vec)
    : m_elps(elps), m_geocentric((vec)) // Note: reference member must be initialized in the initializer list
{
    // Compute the geodetic coordinates
    double x, y, z;
    m_geocentric.getCoordinates(x, y, z);
    // Get the lon, lat (in radians) and alt
    m_elps.geocentricToGeodetic(x, y, z, m_lon_rad, m_lat_rad, m_alt, false);
}

//!
GeoPoint::GeoPoint(Ellipsoid &elps,
                   const double &lon, const double &lat, const double &alt,
                   enum GeoPointInit init, bool degrees)
    : m_elps(elps)
{
    if (init == GeoPointInit::fromGeodetic)
    {
        if (degrees)
        {
            m_lon_rad = lon * Constants::m_degtorad;
            m_lat_rad = lat * Constants::m_degtorad;
        }
        else
        {
            m_lon_rad = lon;
            m_lat_rad = lat;
        }
        m_alt = alt;
        // Compute the geocentric coordinates
        double x, y, z;
        m_elps.geodeticToGeocentric(m_lon_rad, m_lat_rad, m_alt, x, y, z, false);
        m_geocentric.setCoordinates(x, y, z);
    }
    else if (init == GeoPointInit::fromGeocentric)
    {
        // lon -> x, lat -> y, alt -> z
        m_geocentric.setCoordinates(lon, lat, alt);
        // Compute the geodetic coordinates
            // Get the lon, lat (in radians) and alt
        m_elps.geocentricToGeodetic(lon, lat, alt, m_lon_rad, m_lat_rad, m_alt, false);
    }
}

// Copy constructor
GeoPoint::GeoPoint(const GeoPoint &other)
    : m_elps(other.m_elps),
      m_geocentric(other.m_geocentric),
      m_lon_rad(other.m_lon_rad), m_lat_rad(other.m_lat_rad),
      m_alt(other.m_alt) {}

// ============== DESTRUCTOR ==============
GeoPoint::~GeoPoint() {}

// ============== CLASS METHODS ==============
// ********** SETTER **********
void GeoPoint::setCoords(const Geometry::Vector3D &vec)
{
    m_geocentric = vec;
    // Compute the geodetic coordinates
    double x, y, z;
    m_geocentric.getCoordinates(x, y, z);
    // Get the lon, lat (in radians) and alt
    m_elps.geocentricToGeodetic(x, y, z, m_lon_rad, m_lat_rad, m_alt, false);
}

void GeoPoint::setCoords(const double &lon, const double &lat, const double &alt,
                         enum GeoPointInit init, bool degrees)
{
    if (init == GeoPointInit::fromGeodetic)
    {
        if (degrees)
        {
            m_lon_rad = lon * Constants::m_degtorad;
            m_lat_rad = lat * Constants::m_degtorad;
        }
        else
        {
            m_lon_rad = lon;
            m_lat_rad = lat;
        }
        m_alt = alt;
        // Compute the geocentric coordinates
        double x, y, z;
        m_elps.geodeticToGeocentric(m_lon_rad, m_lat_rad, m_alt, x, y, z, false);
        m_geocentric.setCoordinates(x, y, z);
    }
    else if (init == GeoPointInit::fromGeocentric)
    {
        // lon -> x, lat -> y, alt -> z
        m_geocentric.setCoordinates(lon, lat, alt);
        // Compute the geodetic coordinates
            // Get the lon, lat (in radians) and alt
        m_elps.geocentricToGeodetic(lon, lat, alt, m_lon_rad, m_lat_rad, m_alt, false);
    }
    else
        throw std::invalid_argument("");
}

// ********** GETTER **********
void GeoPoint::getGeodeticCoords(double &lon, double & lat, double &alt, bool degrees)
{
    lon = m_lon_rad;
    lat = m_lat_rad;
    alt = m_alt;
    if (degrees)
    {
        lon *= Constants::m_radtodeg;
        lat *= Constants::m_radtodeg;
    }
}
double GeoPoint::getLon(bool degrees) const { return degrees ? m_lon_rad * Constants::m_radtodeg : m_lon_rad; }
double GeoPoint::getLat(bool degrees) const { return degrees ? m_lat_rad * Constants::m_radtodeg : m_lat_rad; }
double GeoPoint::getAlt() const { return m_alt; }
void GeoPoint::getGeocentricCoords(double &x, double &y, double &z)
{
    m_geocentric.getCoordinates(x, y, z);
}
Geometry::Vector3D GeoPoint::getGeocentricCoords() const { return m_geocentric; }
double GeoPoint::getX() const { return m_geocentric.getX(); }
double GeoPoint::getY() const { return m_geocentric.getY(); }
double GeoPoint::getZ() const { return m_geocentric.getZ(); }
Ellipsoid GeoPoint::getEllipsoid() const { return m_elps; }

// ============== OPERATORS ==============
GeoPoint GeoPoint::operator=(const GeoPoint &other)
{
    m_elps = other.m_elps;
    m_geocentric = other.m_geocentric;
    m_lon_rad = other.m_lon_rad;
    m_lat_rad = other.m_lat_rad;
    m_alt = other.m_alt;
    return *this;
}

// Comparison operators
bool GeoPoint::operator==(const GeoPoint &other) const
{
    return (m_elps == other.m_elps) &&
           (m_geocentric == other.m_geocentric);
}

bool GeoPoint::operator!=(const GeoPoint &other) const
{
    return !(*this == other);
}

// ============== GEOPOINT FUNCTIONS ==============
GeoPoint GeoPoint::toEllipsoid(Ellipsoid &elps2,
                               const double &T12x, const double &T12y, const double &T12z,
                               const double &R12x, const double &R12y, const double &R12z,
                               const double &S12, bool degrees, bool R12exact)
{
    if (elps2 == m_elps)
        return *this;
    double rx = R12x, ry = R12y, rz = R12z;
    if (degrees)
    {
        rx *= Constants::m_degtorad;
        ry *= Constants::m_degtorad;
        rz *= Constants::m_degtorad;
    }
    // Translation
    Geometry::Vector3D T12(T12x, T12y, T12z);
    // Rotation
    Geometry::Rotation3D rot;
    if (R12exact)
    {
        rot.setRotation("xyz", rx, ry, rz, false); // rx * ry * rz
    }
    else
    {
        rot.setRotation(1.0, -rz, ry,
                        rz,  1.0, -rx,
                        -ry, rx,  1.0);
    }
    // 7 parameters similitude transform:
    return GeoPoint(elps2, T12 + (1.0 + S12) * (rot * m_geocentric));
}

} // namespace Osl::Geometry

} // namespace Osl
