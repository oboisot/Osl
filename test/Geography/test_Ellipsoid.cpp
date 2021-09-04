// ===== TESTS Ellipsoid =====
#include "Osl.h"
#include <chrono>
#include <iomanip>

int main()
{
   using namespace Osl;
   using Geography::WGS84,
         Geography::GRS80,
         Geography::Clk80IGN;

   std::cout << "WGS84 == WGS84 ? " << ((WGS84 == WGS84) ? "true" : "false") << std::endl;
   std::cout << "WGS84 == GRS80 ? " << ((WGS84 == GRS80) ? "true" : "false") << std::endl;
   std::cout << "WGS84 == Clk80IGN ? " << ((WGS84 == Clk80IGN) ? "true" : "false") << std::endl;

   double a = WGS84.getEquatorialRadius(),
          b = WGS84.getPolarRadius(),
          f = WGS84.getFirstFlattening(),
          f2 = WGS84.getSecondFlattening(),
          n = WGS84.getThirdFlattening(),
          e = WGS84.getEccentricity();

   std::cout << std::setprecision(14);
   std::cout << "a = " << a << std::endl
             << "b = " << b << std::endl
             << "f = " << f << std::endl
             << "f2 = " << f2 << std::endl
             << "n = " << n << std::endl
             << "e = " << e << std::endl << std::endl;


   vector lat{-90, -80, -60, -45, -30, -20, -10, 0, 10, 20, 30, 45, 60, 80, 90};
   // Test geocentric latitude
   std::cout << "Test geocentric latitude:" << std::endl;
   for (auto it = lat.begin() ; it != lat.end() ; ++it)
   {
       std::cout << "lat(" << *it << ") = "
                 << WGS84.inverseGeocentricLatitude(WGS84.geocentricLatitude(*it))
                 << "°" << std::endl;
   }
   std::cout << std::endl;

   // Test parametric latitude
   std::cout << "Test parametric latitude:" << std::endl;
   for (auto it = lat.begin() ; it != lat.end() ; ++it)
   {
       std::cout << "lat(" << *it << ") = "
                 << WGS84.inverseParametricLatitude(WGS84.parametricLatitude(*it))
                 << "°" << std::endl;
   }
   std::cout << std::endl;

   // Test rectifying latitude
   std::cout << "Test rectifying latitude:" << std::endl;
   for (auto it = lat.begin() ; it != lat.end() ; ++it)
   {
       std::cout << "lat(" << *it << ") = "
                 << WGS84.inverseRectifyingLatitude(WGS84.rectifyingLatitude(*it))
                 << "°" << std::endl;
   }
   std::cout << std::endl;

   // Test authalic latitude
   std::cout << "Test authalic latitude:" << std::endl;
   for (auto it = lat.begin() ; it != lat.end() ; ++it)
   {
       std::cout << "lat(" << *it << ") = "
                 << WGS84.inverseAuthalicLatitude(WGS84.authalicLatitude(*it))
                 << "°" << std::endl;
   }
   std::cout << std::endl;

   // Test conformal latitude
   std::cout << "Test conformal latitude:" << std::endl;
   for (auto it = lat.begin() ; it != lat.end() ; ++it)
   {
       std::cout << "lat(" << *it << ") = "
                 << WGS84.inverseConformalLatitude(WGS84.conformalLatitude(*it))
                 << "°" << std::endl;
   }
   std::cout << std::endl;

   // Test isometric latitude
   std::cout << "Test isometric latitude:" << std::endl;
   for (auto it = lat.begin() ; it != lat.end() ; ++it)
   {
       std::cout << "lat(" << *it << ") = "
                 << WGS84.inverseIsometricLatitude(WGS84.isometricLatitude(*it))
                 << "°" << std::endl;
   }
   std::cout << std::endl;

   // Test geodetic to geocentric and vice-versa
   double alt = 0.0;
   vector lon{-180, -135, -100, -90, -45, -30, -20, -10, 0, 10, 20, 30, 45, 90, 100, 135, 180};
   std::cout << "Test geodetic to geocentric and vice-versa:" << std::endl;
   double x, y, z, lo, la, h;
   for (auto ilo = lon.begin() ; ilo != lon.end() ; ++ilo)
   {
       for (auto ila = lat.begin() ; ila != lat.end() ; ++ila)
       {
           WGS84.geodeticToGeocentric(*ilo, *ila, alt, x, y, z);
           WGS84.geocentricToGeodetic(x, y, z, lo, la, h);
           std::cout << "(lon, lat, alt) = ("
                     << *ilo << "°, " << *ila << "°, " << alt << ") = ("
                     << lo << "°, " << la << "°, " << h << " m)"
                     << "°" << std::endl;
       }
   }
   std::cout << std::endl;

   return 0;
}
