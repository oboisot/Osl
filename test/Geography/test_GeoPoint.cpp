// ===== TESTS GeoPoint =====
#include "Osl.h"
#include <iostream>

int main()
{
    using namespace Osl::Geography;

    double lon(-1.23), lat(90), alt(-356.459);
    GeoPoint gp(WGS84, lon, lat, alt, GeoPointInit::fromGeodetic, true);

    Osl::Geometry::Vector3D vec(WGS84.getEquatorialRadius(), 1000, 0);
    GeoPoint gp2(WGS84, vec);

    Ellipsoid wgs84(gp.getEllipsoid());
    std::cout << "WGS84 == wgs84 ? " << ((WGS84 == wgs84) ? "true" : "false") << std::endl;

    std::cout << "(" << lon << "°, " << lat << "°, " << alt << " m) = "
              << "(" << gp.getLon() << "°, " << gp.getLat() << "°, " << gp.getAlt() << " m) = "
              << "(" << gp.getX() << "m, " << gp.getY() << "m, " << gp.getZ() << " m)"
              << std::endl;

    std::cout << "(" << vec.getX() << "m, " << vec.getY() << "m, " << vec.getZ() << " m) = "
              << "(" << gp2.getLon() << "°, " << gp2.getLat() << "°, " << gp2.getAlt() << " m) = "
              << "(" << gp2.getX() << "m, " << gp2.getY() << "m, " << gp2.getZ() << " m)"
              << std::endl;

    return 0;
}
