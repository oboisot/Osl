/*! ********************************************************************
 * \file Ellipsoid.cpp
 * \brief Source file of Osl::Geography::Ellipsoid class.
 *********************************************************************/

#include "Ellipsoid.h"

namespace Osl { // namespace Osl

namespace Geography { // namespace Osl::Geography

// ============== CONSTRUCTOR ==============
Ellipsoid::Ellipsoid() {}

Ellipsoid::Ellipsoid(const double &a, const double &f,
                     enum EllipsoidInit init)
    : m_a(a)                               // Equatorial radius [m]
{
    switch (init)
    {
    case EllipsoidInit::fromRadiusAndFlattening:
    {
        m_f = f;                           // first flattening parameter
        m_b = (1.0 - m_f) * m_a;
        break;
    }
    case EllipsoidInit::fromRadiusAndRadius:
    {
        m_b = f;                           // Polar radius [m]
        m_f = (m_a - m_b) / m_a;           // first flattening parameter
        break;
    }
    default:
        throw std::invalid_argument("Ellipsoid constructor:\n"
                                    "'init' is not a valid initialization enumeration.");
    }
    m_f2 = (m_a - m_b) / m_b;              // second flattening parameter
    m_n = m_f / (2.0 - m_f);               // third flattening parameter
    m_e2 = m_f * (2.0 - m_f);              // the excentricity squared
    m_e = std::sqrt(m_e2);                 // the ellipsoïd excentricity
    m_ep2 = m_e2 / (1.0 - m_e2);           // the second excentricity squared
    m_mp = m_a * std::comp_ellint_2(m_e);  // Length of a quarter meridian
    // Convenient value used multiple times
    m_1_e2 = 1.0 - m_e2;                   // 1 - m_e2
    m_a_1_e2 = m_a * m_1_e2;               // m_a * (1 - m_e2)
    m_1_f = 1.0 - m_f;                     // 1 - m_f
    // Initialization of series expansion of inverse latitude functions
    this->initInverseLattitudeCoeffs();
}

// Copy constructor
Ellipsoid::Ellipsoid(const Ellipsoid &other)
    :  m_a(other.m_a), m_f(other.m_f), m_b(other.m_b),
       m_f2(other.m_f2), m_n(other.m_n), m_e2(other.m_e2),
       m_e(other.m_e), m_ep2(other.m_ep2), m_mp(other.m_mp),
       m_1_e2(other.m_1_e2), m_a_1_e2(other.m_a_1_e2),
       m_1_f(other.m_1_f), m_phimu(other.m_phimu),
       m_phixi(other.m_phixi), m_phichi(other.m_phichi) {}

// ============== DESTRUCTOR ==============
Ellipsoid::~Ellipsoid() {}

// ============== CLASS METHODS ==============
// ********** SETTER **********

// ********** GETTER **********
double Ellipsoid::getEquatorialRadius() const { return m_a; }
double Ellipsoid::getPolarRadius() const { return m_b; }
double Ellipsoid::getFirstFlattening() const { return m_f; }
double Ellipsoid::getSecondFlattening() const { return m_f2; }
double Ellipsoid::getThirdFlattening() const { return m_n; }
double Ellipsoid::getEccentricity() const { return m_e; }
double Ellipsoid::getEccentricitySquared() const { return m_e2; }
double Ellipsoid::getQuarterMeridianDistance() const { return m_mp; }

// ============== OPERATORS ==============
// Assignement from another vector
Ellipsoid Ellipsoid::operator=(const Ellipsoid &other)
{
    m_a = other.m_a;    // Equatorial radius [m]
    m_f = other.m_f;    // first flattening parameter
    m_b = other.m_b;    // Polar radius [m]
    m_f2 = other.m_f2;   // second flattening parameter
    m_n = other.m_n;    // third flattening parameter
    m_e2 = other.m_e2;   // the excentricity squared
    m_e = other.m_e;    // the ellipsoïd excentricity
    m_ep2 = other.m_ep2;  // the second excentricity squared
    m_mp = other.m_mp;   // Length of a quarter meridian
    m_1_e2 = other.m_1_e2;    // 1 - m_e2
    m_a_1_e2 = other.m_a_1_e2;  // m_a * (1 - m_e2)
    m_1_f = other.m_1_f;     // 1 - m_f
    m_phimu = other.m_phimu,  // Coefficients of the inverse rectifying latitude
    m_phixi = other.m_phixi,  // Coefficients of the inverse authalic latitude
    m_phichi = other.m_phichi; // Coefficients of the inverse conformal latitude
    return *this;
}

// Comparison operators
bool Ellipsoid::operator==(const Ellipsoid &other) const
{
    return Maths::Comparison::almost_equal(m_a, other.m_a) &&
           Maths::Comparison::almost_equal(m_f, other.m_f);
}

bool Ellipsoid::operator!=(const Ellipsoid &other) const
{
    return !(*this == other);
}

// ============== ELLIPSOID FUNCTIONS ==============
// ********** CURVATURE RADIUS AND DISTANCE **********
double Ellipsoid::meridianDistance(const double &lat, bool degrees)
{
    double lat_rad = degrees ? lat * Constants::m_degtorad : lat;
    return m_a_1_e2 * std::ellint_3(m_e, m_e2, lat_rad);
}

double Ellipsoid::meridianCurvatureRadius(const double &lat, bool degrees)
{
    double slat = std::sin(degrees ? lat * Constants::m_degtorad : lat);
    double t = 1.0 - m_e2 * slat * slat;
    return m_a_1_e2 / (t * std::sqrt(t)); //^(3/2)
}

double Ellipsoid::primeVerticalCurvatureRadius(const double &lat, bool degrees)
{
    double slat = std::sin(degrees ? lat * Constants::m_degtorad : lat);
    return m_a / std::sqrt(1.0 - m_e2 * slat * slat);
}

double Ellipsoid::curvatureRadius(const double &lat, const double &alpha, bool degrees)
{
    double lat_rad, alpha_rad;
    degrees ? (lat_rad = lat * Constants::m_degtorad, alpha_rad = alpha * Constants::m_degtorad) :
              (lat_rad = lat, alpha_rad = alpha);
    double rho = this->meridianCurvatureRadius(lat_rad, false),
           nu = this->primeVerticalCurvatureRadius(lat_rad, false);
    double ca = std::cos(alpha),
           sa = std::sin(alpha);
    return 1.0 / (ca * ca / rho + sa * sa / nu);
}

// ********** LATITUDES **********
double Ellipsoid::geocentricLatitude(const double &lat, bool degrees)
{
    double theta = std::atan(m_1_e2 * std::tan(degrees ? lat * Constants::m_degtorad : lat));
    return degrees ? theta * Constants::m_radtodeg : theta;
}

double Ellipsoid::inverseGeocentricLatitude(const double &theta, bool degrees)
{
    double phi = std::atan(std::tan(degrees ? theta * Constants::m_degtorad : theta) / m_1_e2);
    return degrees ? phi * Constants::m_radtodeg : phi;
}

double Ellipsoid::parametricLatitude(const double &lat, bool degrees)
{
    double beta = std::atan(m_1_f * std::tan(degrees ? lat * Constants::m_degtorad : lat));
    return degrees ? beta * Constants::m_radtodeg : beta;
}

double Ellipsoid::inverseParametricLatitude(const double &beta, bool degrees)
{
    double phi = std::atan(std::tan(degrees ? beta * Constants::m_degtorad : beta) / m_1_f);
    return degrees ? phi * Constants::m_radtodeg : phi;
}

double Ellipsoid::rectifyingLatitude(const double &lat, bool degrees)
{
    double mu = Constants::m_pi_2 * this->meridianDistance(lat, degrees) / m_mp;
    return degrees ? mu * Constants::m_radtodeg : mu;
}

double Ellipsoid::inverseRectifyingLatitude(const double &mu, bool degrees)
{
    double mu_rad = degrees ? mu * Constants::m_degtorad : mu,
           phi = mu_rad;
    for (std::size_t i = 0 ; i < m_size_coeffs ; ++i)
    {
        phi += m_phimu[i] * std::sin(2.0 * (i + 1) * mu_rad);
    }
    return degrees ? phi * Constants::m_radtodeg : phi;
}

double Ellipsoid::authalicLatitude(const double &lat, bool degrees)
{
    double slat = std::sin(degrees ? lat * Constants::m_degtorad : lat),
           c = m_1_e2 / m_e;
    double q = m_1_e2 * slat / (1.0 - m_e2 * slat * slat) + c * std::atanh(m_e * slat),
           qp = 1.0 + c * std::atanh(m_e);
    double xi = std::asin(q / qp);
    return degrees ? xi * Constants::m_radtodeg : xi;
}

double Ellipsoid::inverseAuthalicLatitude(const double &xi, bool degrees)
{
    double xi_rad = degrees ? xi * Constants::m_degtorad : xi,
           phi = xi_rad;
    for (std::size_t i = 0 ; i < m_size_coeffs ; ++i)
    {
        phi += m_phixi[i] * std::sin(2.0 * (i + 1) * xi_rad);
    }
    return degrees ? phi * Constants::m_radtodeg : phi;
}

double Ellipsoid::conformalLatitude(const double &lat, bool degrees)
{
    double slat = std::sin(degrees ? lat * Constants::m_degtorad : lat);
    double chi = std::asin(std::tanh(std::atanh(slat) - m_e * std::atanh(m_e * slat)));
    return degrees ? chi * Constants::m_radtodeg : chi;
}

double Ellipsoid::inverseConformalLatitude(const double &chi, bool degrees)
{
    double chi_rad = degrees ? chi * Constants::m_degtorad : chi,
           phi = chi_rad;
    for (std::size_t i = 0 ; i < m_size_coeffs ; ++i)
    {
        phi += m_phichi[i] * std::sin(2.0 * (i + 1) * chi_rad);
    }
    return degrees ? phi * Constants::m_radtodeg : phi;
}

double Ellipsoid::isometricLatitude(const double &lat, bool degrees)
{
    double slat = std::sin(degrees ? lat * Constants::m_degtorad : lat);
    double psi = std::atanh(slat) - m_e * std::atanh(m_e * slat);
    return degrees ? psi * Constants::m_radtodeg : psi;
}

double Ellipsoid::inverseIsometricLatitude(const double &psi, bool degrees)
{
    double chi = std::asin(std::tanh(degrees ? psi * Constants::m_degtorad : psi)),
           phi = this->inverseConformalLatitude(chi, false);
    return degrees ? phi * Constants::m_radtodeg : phi;
}

// ********** Coordinates transform **********
void Ellipsoid::geodeticToGeocentric(const double &lon, const double &lat, const double &alt,
                                     double &x, double &y, double &z, bool degrees)
{
    double lon_rad, lat_rad;
    degrees ? (lon_rad = lon * Constants::m_degtorad, lat_rad = lat * Constants::m_degtorad) :
              (lon_rad = lon, lat_rad = lat);
    double nu = this->primeVerticalCurvatureRadius(lat_rad, false),
           nuhcosphi = (nu + alt) * std::cos(lat_rad);
    x = nuhcosphi * std::cos(lon_rad);
    y = nuhcosphi * std::sin(lon_rad);
    z = (m_1_e2 * nu + alt) * std::sin(lat_rad);
}

void Ellipsoid::geocentricToGeodetic(const double &x, const double &y, const double &z,
                                     double &lon, double &lat, double &alt,
                                     bool degrees, std::size_t maxiter)
{
    // Computing lambda
    lon = std::atan2(y, x);
    // Computing phi with approximated Bowring formula, 1985
    double ae2 = m_a * m_e2,
           Rxy = std::hypot(x, y),  // Distance from the Ellipsoid center in the equatorial plane
           invRxy = 1.0 / Rxy,
           u = std::atan(z * (m_1_f + ae2 / std::hypot(x, y, z)) * invRxy),
           su = std::sin(u),
           cu = std::cos(u),
           lat_n = std::atan((z * m_1_f + ae2 * su * su * su) /    // Bowring formula
                             (m_1_f * (Rxy - ae2 * cu * cu *cu)));
        // Fixed point iterations [Note: at least one iteration is made]
        // Initialization with first iteration
    double nu = this->primeVerticalCurvatureRadius(lat_n, false),
           lat_np1 = std::atan((z + m_e2 * std::sin(lat_n) * nu) * invRxy),
           err = std::abs(lat_np1 - lat_n);
    std::size_t it = 1; // Note: initialization count for 1 iteration
    while (err >= Constants::n_machine_eps && it < maxiter)
    {
        lat_n = lat_np1;
        nu = this->primeVerticalCurvatureRadius(lat_n, false);
        lat_np1 = std::atan((z + m_e2 * std::sin(lat_n) * nu) * invRxy);
        err = std::abs(lat_np1 - lat_n);
        ++it;
    }
    lat = lat_np1; // Resulting lambda
    // Computing altitude [Bowring formula, 1985]
    double slat = std::sin(lat);
    alt = Rxy * std::cos(lat) + z * slat - m_a * std::sqrt(1.0 - m_e2 * slat * slat);
    if (degrees)
    {
        lon *= Constants::m_radtodeg;
        lat *= Constants::m_radtodeg;
    }
}

// ============== PRIVATE CLASS METHODS ==============
void Ellipsoid::initInverseLattitudeCoeffs()
{
    // Power of third flattening factor
    double n2 = m_n * m_n, n3 = m_n * n2, n4 = n2 * n2, n5 = n2 * n3, n6 = n3 * n3,
           n7 = n2 * n5, n8 = n4 * n4, n9 = n4 * n5, n10 = n5 * n5;
    // Coefficients of the inverse rectifying latitude
    m_phimu.reserve(m_size_coeffs);
    m_phimu[0] = 3.0*m_n/2.0 - 27.0*n3/32.0 + 269.0*n5/512.0 - 6607.0*n7/24576.0 + 4094.0*n9/327680.0;              // b2
    m_phimu[1] = 21.0*n2/16.0 - 55.0*n4/32.0 + 6759.0*n6/4096.0 - 155113.0*n8/122880.0 + 39591143.0*n10/47185920.0; // b4
    m_phimu[2] = 151.0*n3/96.0 - 417.0*n5/128.0 + 87963.0*n7/20480.0 - 572057.0*n9/131072.0;                        // b6
    m_phimu[3] = 1097.0*n4/512.0 - 15543.0*n6/2560.0 + 2514467.0*n8/245760.0 - 33432797.0*n10/2580480.0;            // b8
    m_phimu[4] = 8011.0*n5/2560.0 - 69119.0*n7/6144.0 + 1515771.0*n9/65536.0;                                       // b10
    m_phimu[5] = 293393.0*n6/61440.0 - 5962461.0*n8/286720.0 + 463409979.0*n10/9175040.0;                           // b12
    m_phimu[6] = 6459601.0*n7/860160.0 - 1258281.0*n9/32768.0;                                                      // b14
    m_phimu[7] = 332287993.0*n8/27525120.0 - 8778422179.0*n10/123863040.0;                                          // b16
    m_phimu[8] = 116391263.0*n9/5898240.0;                                                                          // b18
    m_phimu[9] = 32385167569.0*n10/990904320.0;                                                                     // b20
    // Coefficients of the inverse
    m_phixi.reserve(m_size_coeffs);
    m_phixi[0] = 4.0*m_n/3.0 + 4.0*n2/45.0 - 16.0*n3/35.0 - 2582.0*n4/14175.0 + 60136.0*n5/467775.0  // c2
                 + 28112932.0*n6/212837625.0 + 22947844.0*n7/1915538625.0
                 - 1683291094.0*n8/37574026875.0 - 338504669588.0*n9/12993098493375.0
                 + 4371583262356.0*n10/1286316750844125.0;
    m_phixi[1] = 46.0*n2/45.0 + 152.0*n3/945.0 - 11966.0*n4/14175.0 - 21016.0*n5/51975.0             // c4
                 + 251310128.0*n6/638512875.0 + 1228352.0*n7/3007125.0
                 - 14351220203.0*n8/488462349375.0 - 59522305664.0*n9/265165275375.0
                 - 28128931336204.0*n10/306265893058125.0;
    m_phixi[2] = 3044.0*n3/2835.0 + 3802.0*n4/14175.0 - 94388.0*n5/66825.0                           // c6
                 - 8797648.0*n6/10945935.0 + 138128272.0*n7/147349125.0
                 + 505559334506.0*n8/488462349375.0 - 7651134508792.0*n9/38979295480125.0
                 - 2747215563967192.0*n10/3573102085678125.0;
    m_phixi[3] = 6059.0*n4/4725.0 + 41072.0*n5/93555.0 - 1472637812.0*n6/638512875.0                 // c8
                 - 45079184.0*n7/29469825.0 + 973080708361.0*n8/488462349375.0
                 + 30918739454896.0*n9/12993098493375.0
                 - 1405101318247556.0*n10/2143861251406875.0;
    m_phixi[4] = 768272.0*n5/467775.0 + 455935736.0*n6/638512875.0                                   // c10
                 - 550000184.0*n7/147349125.0 - 1385645336626.0*n8/488462349375.0
                 + 51535685606752.0*n9/12993098493375.0
                 + 276058103987059936.0*n10/53596531285171875.0;
    m_phixi[5] = 4210684958.0*n6/1915538625.0 + 443810768.0*n7/383107725.0                           // c12
                 - 2939205114427.0*n8/488462349375.0
                 - 604166407968208.0*n9/116937886440375.0
                 + 81173734025797618.0*n10/10719306257034375.0;
    m_phixi[6] = 387227992.0*n7/127702575.0 + 101885255158.0*n8/54273594375.0                        // c14
                 - 125789879410192.0*n9/12993098493375.0
                 - 99508459264029736.0*n10/10719306257034375.0;
    m_phixi[7] = 1392441148867.0*n8/325641566250.0 + 39504919358864.0*n9/12993098493375.0            // c16
                 - 500374928896539392.0*n10/32157918771103125.0;
    m_phixi[8] = 2151110306499536.0*n9/350813659321125.0                                             // c18
                 + 31664196627408368.0*n10/6431583754220625.0;
    m_phixi[9] = 68217869975393752.0*n10/7656647326453125.0;                                         // c20
    // Coefficients of the inverse conformal latitude
    m_phichi.reserve(m_size_coeffs);
    m_phichi[0] = 2.0*m_n - 2.0*n2/3.0 - 2.0*n3 + 116.0*n4/45.0 + 26.0*n5/45.0 - 2854.0*n6/675.0    // d2
                  + 16822.0*n7/4725.0 + 189416.0*n8/99225.0 - 1113026.0*n9/165375.0
                  + 22150106.0*n10/4465125.0;
    m_phichi[1] = 7.0*n2/3.0 - 8.0*n3/5.0 - 227.0*n4/45.0 + 2704.0*n5/315.0 + 2323.0*n6/945.0       // d4
                 - 31256.0*n7/1575.0 + 141514.0*n8/8505.0 + 10453448.0*n9/606375.0
                 - 66355687.0*n10/1403325.0;
    m_phichi[2] = 56.0*n3/15.0 - 136.0*n4/35.0 - 1262.0*n5/105.0 + 73814.0*n6/2835.0                // d6
                  + 98738.0*n7/14175.0 - 2363828.0*n8/31185.0 + 53146406.0*n9/779625.0
                  + 1674405706.0*n10/18243225.0;
    m_phichi[3] = 4279.0*n4/630.0 - 332.0*n5/35.0 - 399572.0*n6/14175.0 + 11763988.0*n7/155925.0    // d8
                 + 14416399.0*n8/935550.0 - 2647902052.0*n9/10135125.0
                  + 23834033824.0*n10/91216125.0;
    m_phichi[4] = 4174.0*n5/315.0 - 144838.0*n6/6237.0 - 2046082.0*n7/31185.0                       // d10
                  + 258316372.0*n8/1216215.0 + 67926842.0*n9/2837835.0
                  - 76998787574.0*n10/91216125.0;
    m_phichi[5] = 601676.0*n6/22275.0 - 115444544.0*n7/2027025.0 - 2155215124.0*n8/14189175.0       // d12
                  + 41561762048.0*n9/70945875.0 + 625821359.0*n10/638512875.0;
    m_phichi[6] = 38341552.0*n7/675675.0 - 170079376.0*n8/1216215.0                                 // d14
                  - 1182085822.0*n9/3378375.0 + 493459023622.0*n10/310134825.0;
    m_phichi[7] = 1383243703.0*n8/11351340.0 - 138163416988.0*n9/402026625.0                        // d16
                  - 1740830660174.0*n10/2170943775.0;
    m_phichi[8] = 106974149462.0*n9/402026625.0 - 24899113566814.0*n10/29462808375.0;               // d18
    m_phichi[9] = 175201343549.0*n10/297604125.0;                                                   // d20
}

} // namespace Osl::Geometry

} // namespace Osl
