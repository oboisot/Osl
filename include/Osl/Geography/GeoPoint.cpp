/*! ********************************************************************
 * \file GeoPoint.cpp
 * \brief Source file of Osl::Geography::GeoPoint class.
 *********************************************************************/

#include "GeoPoint.h"

namespace Osl { // namespace Osl

namespace Geography { // namespace Osl::Geography

// ============== CONSTRUCTOR ==============
GeoPoint::GeoPoint(){} // L'initialisation de m_elps doit être explicite (référence)

//!
GeoPoint::GeoPoint(Ellipsoid* elps,
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
        m_elps->geodeticToGeocentric(m_lon_rad, m_lat_rad, m_alt, m_x, m_y, m_z, false);
    }
    else if (init == GeoPointInit::fromGeocentric)
    {
        // lon -> x, lat -> y, alt -> z
        m_x = lon;
        m_y = lat;
        m_z = alt;
        // Compute the geodetic coordinates
            // Get the lon, lat (in radians) and alt
        m_elps->geocentricToGeodetic(m_x, m_y, m_z, m_lon_rad, m_lat_rad, m_alt, false);
    }
}

// Copy constructor
GeoPoint::GeoPoint(const GeoPoint &other)
    : m_elps(other.m_elps),
      m_x(other.m_x), m_y(other.m_y), m_z(other.m_z),
      m_lon_rad(other.m_lon_rad), m_lat_rad(other.m_lat_rad),
      m_alt(other.m_alt) {}

// ============== DESTRUCTOR ==============
GeoPoint::~GeoPoint() {}

// ============== CLASS METHODS ==============
// ********** SETTER **********
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
        m_elps->geodeticToGeocentric(m_lon_rad, m_lat_rad, m_alt, m_x, m_y, m_z, false);
    }
    else if (init == GeoPointInit::fromGeocentric)
    {
        // lon -> x, lat -> y, alt -> z
        m_x = lon;
        m_y = lat;
        m_z = alt;
        // Compute the geodetic coordinates
            // Get the lon, lat (in radians) and alt
        m_elps->geocentricToGeodetic(m_x, m_y, m_z, m_lon_rad, m_lat_rad, m_alt, false);
    }
    else
        throw std::invalid_argument("");
}

void GeoPoint::setGeocentricCoords(const double &x, const double &y, const double &z)
{
    m_x = x;
    m_y = y;
    m_z = z;
    m_elps->geocentricToGeodetic(m_x, m_y, m_z, m_lon_rad, m_lat_rad, m_alt, false);
}

void GeoPoint::setGeodeticCoords(const double &lon_rad, const double &lat_rad, const double &alt)
{
    m_lon_rad = lon_rad;
    m_lat_rad = lat_rad;
    m_alt     = alt;
    m_elps->geodeticToGeocentric(m_lon_rad, m_lat_rad, m_alt, m_x, m_y, m_z, false);
}


// ********** GETTER **********
void GeoPoint::getGeodeticCoords(double &lon, double &lat, double &alt, bool degrees)
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
    x = m_x;
    y = m_y;
    z = m_z;
}
double GeoPoint::getX() const { return m_x; }
double GeoPoint::getY() const { return m_y; }
double GeoPoint::getZ() const { return m_z; }
Ellipsoid* GeoPoint::getEllipsoidPtr() const { return m_elps; }

// ============== OPERATORS ==============
GeoPoint GeoPoint::operator=(const GeoPoint &other)
{
    m_elps = other.m_elps;
    m_x = other.m_x;
    m_y = other.m_y;
    m_z = other.m_z;
    m_lon_rad = other.m_lon_rad;
    m_lat_rad = other.m_lat_rad;
    m_alt = other.m_alt;
    return *this;
}

// Comparison operators
bool GeoPoint::operator==(const GeoPoint &other) const
{
    return (m_elps == other.m_elps) &&
           (Maths::Comparison::almost_equal(m_x, other.m_x)) &&
           (Maths::Comparison::almost_equal(m_y, other.m_y)) &&
           (Maths::Comparison::almost_equal(m_z, other.m_z));
}

bool GeoPoint::operator!=(const GeoPoint &other) const
{
    return !(*this == other);
}

// ============== GEOPOINT FUNCTIONS ==============
GeoPoint GeoPoint::toEllipsoid(Ellipsoid* elps2,
                               const double &T12x, const double &T12y, const double &T12z,
                               const double &R12x, const double &R12y, const double &R12z,
                               const double &S12, bool degrees)
{
    if (*elps2 == *m_elps)
        return *this;
    double rx = R12x, ry = R12y, rz = R12z;
    if (degrees)
    {
        rx *= Constants::m_degtorad;
        ry *= Constants::m_degtorad;
        rz *= Constants::m_degtorad;
    }
    double scale = 1.0 + S12, x, y, z;
    // Small angles rotation matrix :
    // rot = |1.0, -rz, ry |
    //       |rz,  1.0, -rx|
    //       |-ry, rx,  1.0|
    x = T12x + scale * (m_x - rz * m_y + ry * m_z);
    y = T12y + scale * (rz * m_x + m_y - rx * m_z);
    z = T12z + scale * (-ry * m_x + rx * m_y + m_z);
    return GeoPoint(elps2, x, y, z, GeoPointInit::fromGeocentric);
}

void GeoPoint::toEllipsoidInplace(Ellipsoid* elps2,
                                  const double &Tx, const double &Ty, const double &Tz,
                                  const double &Rx=0.0, const double &Ry=0.0, const double &Rz=0.0,
                                  const double &scale=0.0)
    m_elps = elps2;
    double sscale = 1.0 + scale;
    // Small angles rotation matrix :
    // rot = |1.0, -rz, ry |
    //       |rz,  1.0, -rx|
    //       |-ry, rx,  1.0|
    this->setGeocentricCoords(Tx + sscale * (m_x - Rz * m_y + Ry * m_z),
                              Ty + sscale * (Rz * m_x + m_y - Rx * m_z),
                              Tz + sscale * (-Ry * m_x + Rx * m_y + m_z));
}

} // namespace Osl::Geometry

} // namespace Osl
