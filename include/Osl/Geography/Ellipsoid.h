/*! ********************************************************************
 * \file Ellipsoid.h
 * \brief Header file of Osl::Geography::Ellipsoid class.
 *********************************************************************/

#ifndef OSL_GEOGRAPHY_ELLIPSOID_H
#define OSL_GEOGRAPHY_ELLIPSOID_H

#include "Osl/Constants.h"
#include "Osl/Maths/Comparison/almost_equal.h"

namespace Osl { // namespace Osl

namespace Geography { // namespace Osl::Geography

/*! ********************************************************************
 * \enum EllipsoidInit
 * \brief Enumeration for the initialization of the Ellipsoid class.
 *********************************************************************/
enum class EllipsoidInit
{
    /*! Ellipsoid initialization from equatorial radius and flattening.*/
    fromRadiusAndFlattening,
    /*! Ellipsoid initialization from equatorial and polar radius.*/
    fromRadiusAndRadius
};

/*! ********************************************************************
 * \brief Class to manage Ellipsoid of revolution for geographic
 * applications.
 *
 *
 * This class defines the reference Ellipsoid of revolution (also called
 * Spheroid) to be used for geographic applications.
 * The Ellipsoid is generally defined from one of the two following couples:
 *
 * * \f$(a,f)\f$ \f$\rightarrow\f$ (equatorial radius and flattening)
 * * \f$(a,b)\f$ \f$\rightarrow\f$ (equatorial radius and polar radius)
 *
 * \cite Osborne_13
 *
 *********************************************************************/
class Ellipsoid
{
public:
    //! Default Constructor.
    Ellipsoid();

    //! Copy constructor
    Ellipsoid(const Ellipsoid &other);

    /*! ********************************************************************
     * \brief Ellipsoid
     * \param [in] a The equatorial radius of the ellipsoid in meters.
     * \param [in] f if init=EllipsoidInit::fromRadiusAndFlattening use the
     *        flattening of the ellispoid,
     * if init=EllipsoidInit::fromRadiusAndRadius use the polar radius
     * of the ellipsoid in meters.
     * \param [in] init
     *********************************************************************/
    Ellipsoid(const double &a, const double &f,
              enum EllipsoidInit init=EllipsoidInit::fromRadiusAndFlattening);

    // ============== DESTRUCTOR ==============
    //! Default destructor
    ~Ellipsoid();

    // ============== CLASS METHODS ==============
    // ********** SETTER **********

    // ********** GETTER **********
    /*! ********************************************************************
     * \brief Get the equatorial radius of the ellipsoid \f$a\f$ in meters.
     *********************************************************************/
    double getEquatorialRadius() const;

    /*! ********************************************************************
     * \brief Get the polar radius of the ellipsoid \f$b\f$ in meters.
     *
     * The Polar radius is related to the first flattening parameter
     * \f$f\f$ or the eccentricity \f$e\f$ through the relationships:
     *
     * \f[
     *     b=a(1-f)=a\sqrt{1-e^2}
     * \f]
     *
     *********************************************************************/
    double getPolarRadius() const;

    /*! ********************************************************************
     * \brief Get the first flattening parameter \f$f\f$ of the ellipsoid.
     *
     * The first flattening parameter \f$f\f$ is related to the ellipsoid
     * of revolution radii through the relationship:
     *
     * \f[
     *     f=\dfrac{a-b}{a}
     * \f]
     *
     * If \f$f<0\f$ the ellipsoid is called \em oblate (as for the
     * terrestrial ellipsoids), if \f$f>0\f$ it is called \em prolate and,
     * in the case where \f$f=0\f$ the ellipsoid becomes a sphere.
     *
     *********************************************************************/
    double getFirstFlattening() const;

    /*! ********************************************************************
     * \brief Get the second flattening parameter \f$f_2\f$ of the
     *        ellipsoid.
     *
     * The second flattening parameter \f$f_2\f$ is related to the
     * ellipsoid of revolution radii through the relationship:
     *
     * \f[
     *     f_2=\dfrac{a-b}{b}
     * \f]
     *
    * ********************************************************************/
    double getSecondFlattening() const;

    /*! ********************************************************************
     * \brief Get the third flattening parameter \f$n\f$ of the ellipsoid.
     *
     * The third flattening parameter \f$n\f$ is related to the
     * ellipsoid of revolution radii or the first flattening
     * parameter through the relationships:
     *
     * \f[
     *     n=\dfrac{a-b}{a+b}=\dfrac{f}{2-f}
     * \f]
     *
    * ********************************************************************/
    double getThirdFlattening() const;

    /*! ********************************************************************
     * \brief Get the eccentriciy \f$e\f$ of the ellipsoid.
     *
     * The eccentricity \f$e\f$ is related to the first flattening
     * parameter \f$f\f$ through the relationship:
     *
     * \f[
     *     e=\sqrt{f(2-f)}
     * \f]
     *
     * \sa getEccentricitySquared
     *
    * ********************************************************************/
    double getEccentricity() const;

    /*! ********************************************************************
     * \brief Get the eccentriciy squared\f$e^2\f$ of the ellipsoid.
     *
     * \sa getEccentricity
     *
    * ********************************************************************/
    double getEccentricitySquared() const;

    /*! ********************************************************************
     * \brief Get the quarter meridian distance \f$m_p\f$ of the ellipsoid.
     *
     * The quarter meridian distance is defined as the distance from the
     * equator to the pole. It is thus defined as the meridian distance
     * (see Ellipsoid::meridianDistance) evaluated for a latitude of
     * \f$\pi/2\f$:
     *
     * \f[
     *     m_p=m(\dfrac{\pi}{2})=aE(e)
     * \f]
     *
     * and can be expressed as function of the Legendre's complete elliptic
     * integral of second kind <a href="https://dlmf.nist.gov/19.2#ii"
     * target="_blank">[DLMF]</a>:
     *
     * \f[
     *     E(k)=\int\limits_0^{\pi/2}
     *             \sqrt{1-k^2\sin^2\theta}d\theta
     * \f]
     *
     * \sa meridianDistance
     *
    * ********************************************************************/
    double getQuarterMeridianDistance() const;

    // ============== OPERATORS ==============
    // Assignement from another Ellipsoid.
    Ellipsoid operator=(const Ellipsoid &other);
    // Comparison operators
    bool operator==(const Ellipsoid &other) const;
    bool operator!=(const Ellipsoid &other) const;

    // ============== ELLIPSOID FUNCTIONS ==============
    // ********** CURVATURE RADIUS AND DISTANCE **********

    /*! ********************************************************************
     * \brief Compute the meridian distance.
     *
     * The meridian distance is the distance measured along a meridian from
     * equator to a geodetic latitude \f$\phi\f$ and is expressed as:
     *
     * \f[
     *     m(\phi)=\int\limits_0^{\phi}
     *         \dfrac{a(1-e^2)}{(1-e^2\sin^2(t))^{3/2}}dt
     * \f]
     *
     * This expression can be written as function of the Legendre's incomplete
     * elliptic integral of the third kind \f$\Pi(\phi,\nu,k)\f$:
     *
     * \f[
     *     m(\phi)=a(1-e^2)\Pi(\phi,e^2,e)
     * \f]
     *
     * with the Legendre's incomplete elliptic integral being defined by
     * <a href="https://dlmf.nist.gov/19.2#ii" target="_blank">[DLMF]</a>:
     *
     * \f[
     *     \Pi(\phi,\alpha^2,k)=\int\limits_0^{\phi}\dfrac{dt}
     *         {(1-\alpha^2\sin^2(t))\sqrt{1-k^2\sin^2(t)}}
     * \f]
     *
     * \param [in] lat The geodetic latitude.
     * \param [in] degrees The unit of the given latitude. If true (default)
     *        the latitude is provided in degrees, if false it is
     * \return The meridian distance from equator to the given latitude
     *         in meters.
     * \sa rectifyingLatitude, meridianDistance
     * \see <a href="https://en.wikipedia.org/wiki/
     *               Latitude#Length_of_a_degree_of_latitude"
     *         target="_blank">[Wikipedia]</a>
     * ********************************************************************/
    double meridianDistance(const double &lat, bool degrees=true);

    //! Meridian curvature radius
    /*! Compute the meridian curvature radius at a given latitude \f$\phi\f$:
     *
     * \f[
     *     \rho(\phi)=\dfrac{a(1-e^2)}{(1-e^2\sin^2\phi)^{3/2}}
     * \f]
     *
     * \brief meridianCurvatureRadius
     * \param [in] lat
     * \param [in] degrees
     * \return
     */
    double meridianCurvatureRadius(const double &lat, bool degrees=true);

    //! Prime Vertical Curvature Radius
    /*! Compute the prime vertical curvature radius at a given latitude \f$\phi\f$:
     *
     * \f[
     *      \nu(\phi)=\dfrac{a}{\sqrt{1-e^2\sin^2\phi}}
     * \f]
     *
     * \brief primeVerticalCurvatureRadius
     * \param [in] lat
     * \param [in] degrees
     * \return
     */
    double primeVerticalCurvatureRadius(const double &lat, bool degrees=true);

    //! Curvature Radius
    /*! Compute the curvature radius of a point on the ellispoid at a
     * given geodetic latitude \f$\phi\f$ orientated following a given
     * azimut \f$\alpha\f$:
     *
     * \f[
     *     \dfrac{1}{R(\phi,\alpha)}=
     *         \dfrac{\cos^2(\alpha)}{\rho(\phi)}+\dfrac{\sin^2(\alpha)}{\nu(\phi)}
     * \f]
     *
     * where \f$\rho(\phi)\f$ and \f$\nu(\phi)\f$ are the meridian curvature
     * radius and the prime vertical curvature radius of the ellipsoid at latitude
     * \f$\phi\f$, respectively.
     *
     * \brief curvatureRadius
     * \param [in] lat
     * \param [in] degrees
     * \return
     * \sa meridianCurvatureRadius, primeVerticalCurvatureRadius
     */
    double curvatureRadius(const double &lat, const double &alpha, bool degrees=true);

    // ********** LATITUDES **********
    //! Geocentric Latitude
    /*! Compute the geocentric latitude \f$\theta\f$ as function of the
     * geodetic latitude \f$\phi\f$:
     *
     * \f[
     *     \theta(\phi)=\arctan\left((1-e^2)\tan(\phi)\right)
     * \f]
     *
     * \brief geocentricLatitude
     * \param [in] lat
     * \param [in] degrees
     * \return
     * \see <a href="https://en.wikipedia.org/wiki/Latitude#Auxiliary_latitudes">WIKI</a>
     * \sa inverseGeocentricLatitude
     */
    double geocentricLatitude(const double &lat, bool degrees=true);

    //! Inverse Geocentric Latitude
    /*! Compute the geodetic latitude \f$\phi\f$ as function of the geocentric
     * latitude \f$\theta\f$:
     *
     * \f[
     *     \phi(\theta)=\arctan\left(\dfrac{\tan(\theta)}{1-e^2}\right)
     * \f]
     *
    * \brief inverseGeocentricLatitude
    * \param [in] theta
    * \param [in] degrees
    * \return
    * \sa geocentricLatitude
    */
    double inverseGeocentricLatitude(const double &theta, bool degrees=true);

    //! Parametric (reduced) Latitude
    /*! Compute the parametric (reduced) latitude \f$\beta\f$ as function of the
    * geodetic latitude \f$\phi\f$:
    *
    * \f[
    *     \beta(\phi)=\arctan\left((1-f)\tan(\phi)\right)
    * \f]
    *
    * \brief parametricLatitude
    * \param [in] lat
    * \param [in] degrees
    * \return
    * \see <a href="https://en.wikipedia.org/wiki/Latitude#Auxiliary_latitudes">WIKI</a>
    * \sa inverseParametricLatitude
    */
    double parametricLatitude(const double &lat, bool degrees=true);

    //! Inverse parametric latitude
    /*! Compute the geodetic latitude \f$\phi\f$ as function of the parametric
    * latitude \f$\beta\f$:
    *
    * \f[
    *     \phi(\beta)=\arctan\left(\dfrac{\tan(\beta)}{1-f}\right)
    * \f]
    *
    * \brief inverseParametricLatitude
    * \param [in] beta
    * \param [in] degrees
    * \return
    * \sa parametricLatitude
    */
    double inverseParametricLatitude(const double &beta, bool degrees=true);

    //! Rectifying latitude
    /*! Compute the rectifying latitude \f$\mu\f$ as function of the
    * geodetic latitude \f$\phi\f$:
    *
    * \f[
    *     \mu(\phi)=\dfrac{\pi}{2}\dfrac{m(\phi)}{m_p}
    * \f]
    *
    * where \f$m(\phi)\f$ is the meridian distance from equator to latitude
    * \f$\phi\f$ and \f$m_p\f$ is the quarter meridian distance
    * (\f$m_p=m(\pi/2)\f$.
    * \brief rectifyingLatitude
    * \param [in] lat
    * \param [in] degrees
    * \return
    * \see <a href="https://en.wikipedia.org/wiki/Latitude#Auxiliary_latitudes">WIKI</a>
    * \sa meridianDistance
    */
    double rectifyingLatitude(const double &lat, bool degrees=true);

    //! Inverse rectifying latitude
    /*! TO DO...
    * \brief inverseRectifyingLatitude
    * \param [in] mu
    * \param [in] degrees
    * \return
    */
    double inverseRectifyingLatitude(const double &mu, bool degrees=true);

    //! Authalic latitude
    /*! Compute the authalic latitude \f$\xi\f$ as function of the
    * geodetic latitude \f$\phi\f$:
    *
    * \f[
    *     \left\{\begin{array}{rcl}
    *         q(\phi) & = &\dfrac{(1-e^2)\sin\phi}{1-e^2\sin^2\phi}+
    *                       \dfrac{1-e^2}{e}\mathrm{arctanh}(e\sin\phi)\\
    *         q_p & = & q(\pi/2)=1+\dfrac{1-e^2}{e}\mathrm{arctanh}(e)\\
    *         \xi(\phi) & = & \arcsin\left(\dfrac{q(\phi)}{q_p}\right)
    *     \end{array}\right.
    * \f]
    *
    * \brief authalicLatitude
    * \param [in] lat
    * \param [in] degrees
    * \return
    * \see <a href="https://en.wikipedia.org/wiki/Latitude#Auxiliary_latitudes">WIKI</a>
    */
    double authalicLatitude(const double &lat, bool degrees=true);

    //! Inverse authalic latitude
    /*! TO DO...
    * \brief inverseAuthalicLatitude
    * \param [in] xi
    * \param [in] degrees
    * \return
    */
    double inverseAuthalicLatitude(const double &xi, bool degrees=true);

    //! Conformal latitude
    /*! Compute the conformal latitude \f$\chi\f$ as function of the
    * geodetic latitude \f$\phi\f$:
    *
    * \f[
    *     \chi(\phi)=\arcsin\big[\tanh\big(\mathrm{arctanh}(\sin(\phi))-
    *         e\mathrm{arctanh}(e\sin(\phi))\big)\big]
    * \f]
    *
    * \brief conformalLatitude
    * \param [in] lat
    * \param [in] degrees
    * \return
    */
    double conformalLatitude(const double &lat, bool degrees=true);

    //! Inverse conformal latitude
    /*! TO DO...
    * \brief inverseConformalLatitude
    * \param [in] chi
    * \param [in] degrees
    * \return
    */
    double inverseConformalLatitude(const double &chi, bool degrees=true);

    //! Isometric latitude
    /*! Compute the isometric latitude \f$\psi\f$ as function of the
    * geodetic latitude \f$\phi\f$:
    *
    * \f[
    *     \psi(\phi)=\mathrm{arctanh}\big[\sin\big(\chi(\phi)\big)\big]
    *         =\mathrm{arctanh}\big[\sin(\phi)\big]-
    *           e\mathrm{arctanh}\big[\sin(e\phi)\big]
    * \f]
    *
    * \brief isometricLatitude
    * \param [in] lat
    * \param [in] degrees
    * \return
    */
    double isometricLatitude(const double &lat, bool degrees=true);

    //! Inverse isometric latitude
    /*! Compute the geodetic latitude \f$\phi\f$ as function of the
    * isometric latitude \f$\psi\f$. Computation is made through
    * the inverse conformal latitude:
    *
    * \f[
    *     \phi(\psi)=\chi^{-1}\big[\arcsin\big(\tanh(\psi)\big)\big]
    * \f]
    *
    * \brief inverseIsometricLatitude
    * \param [in] psi
    * \param [in] degrees
    * \return
    */
    double inverseIsometricLatitude(const double &psi, bool degrees=true);

    /*! ********************************************************************
     * \brief Transform geodetic coordinates to geocentric (ECEF) coordinates.
     *
     * Transform geodetic coordinates \f$(\lambda,\phi,H)\f$ to geocentric
     * coordinates \f$(X,Y,Z)\f$, also knwon as the Earth-Centered
     * Earth-Fixed (ECEF) cartesian coordinates system
     * <a href="https://en.wikipedia.org/wiki/ECEF" target="_blank">[Wiki]</a>.
     * The transformation is straightforward from the definition of the
     * ellipsoid:
     *
     * \f[
     *     \left\{\begin{array}{rcl}
     *       X & = & \big(\nu(\phi) + H\big)\cos(\phi)\cos(\lambda) \\
     *       Y & = & \big(\nu(\phi) + H\big)\cos(\phi)\sin(\lambda) \\
     *       Z & = & \big((1-e^2)\nu(\phi) + H\big)\sin(\phi)
     *     \end{array}\right.
     * \f]
     *
     * where \f$\nu(\phi)\f$ is the prime vertical curvature radius
     * of the point at latitude \f$\phi\f$
     * (see Ellipsoid::primeVerticalCurvatureRadius).
     *
     * \param [in] lon
     * \param [in] lat
     * \param [in] alt
     * \param [out] x
     * \param [out] y
     * \param [out] z
     * \param [in] degrees
     *********************************************************************/
    void geodeticToGeocentric(const double &lon, const double &lat, const double &alt,
                             double &x, double &y, double &z, bool degrees=true);


    /*! ********************************************************************
     * \brief Transform geocentric (ECEF) coordinates to geodetic coordinates.
     *
     * Transforms geocentric coordinates \f$(X,Y,Z)\f$ to
     * geodetic coordinates \f$(\lambda,\phi,H)\f$ on an ellipsoid of
     * revolution. The computation is made as follows:
     *
     * 1. Longitude \f$\lambda\f$ is computed analytically:
     *
     *    \f[
     *      \lambda=\arctan\left(\frac{Y}{X}\right)
     *    \f]
     *
     * 2. Latitude \f$\phi\f$ is computed from:
     *
     *    1. the approximated Bowring's formula \cite Bowring_85, \cite IGN_TCG :
     *
     *       \f[
     *           \left\{\begin{array}{rcl}
     *               u & = & \arctan\left[\dfrac{Z}{\sqrt{X^2+Y^2}}\left(1-f+
     *                       \dfrac{ae^2}{\sqrt{X^2+Y^2+Z^2}}\right)\right] \\
     *              \phi & = & \arctan\left[\dfrac{(1-f)Z+ae^2\sin^3(u)}
     *                  {(1-f)\left(\sqrt{X^2+Y^2}-ae^2\cos^3(u)\right)}\right]
     *           \end{array}\right.
     *       \f]
     *
     *       This formula provides an accuracy on distances of the order of µm
     *       with the WGS84 Ellipsoïd.
     *
     *    2. the computed approximated value can then be improved numerically
     *       from iterative method, providing an accurate initial guess. The
     *       method used here is the Fixed-Point Iteration method
     *       \cite WIKI_Fixed_Point_Iteration by solving the iterative scheme:
     *
     *       \f[
     *           \phi_{n+1} =
     *              \arctan\left[\dfrac{Z+e^2\nu(\phi_n)\sin(\phi_n)}
     *              {\sqrt{X^2+Y^2}}\right],\quad n=0,1,2,3,\ldots
     *       \f]
     *
     *       until the defined numerical precision (here the machine epsilon
     *       for double precision floating point type). Initialization of this
     *       iterative method with the approximated Bowring's formula provides
     *       a very fast convergence of the iterative scheme (generally, one or
     *       two iterations are sufficient).
     *
     * 3. Finally, from longitude and latitude computed previously, altitude
     *    is computed from the modified Bowring's expression \cite Bowring_85 :
     *
     *    \f[
     *        H=\sqrt{X^2+Y^2}\cos(\phi)+Z\sin(\phi)-a\sqrt{1-e^2\sin^2(\phi)}
     *    \f]
     *
     * \param [in] x, y, z The geocentric coordinates in meters to be transformed
     *             into geodetic coordinates.
     * \param [out] lon, lat, alt The geodetic coordinates in order: longitude,
     *              latitude and altitude [in meters].
     * \param [in] degrees
     * \param [in] maxiter
     *********************************************************************/
    void geocentricToGeodetic(const double &x, const double &y, const double &z,
                             double &lon, double &lat, double &alt,
                             bool degrees=true, std::size_t maxiter=10);


private:
    // ============== PRIVATE CLASS MEMBERS ==============
    double m_a,    // Equatorial radius [m]
           m_f,    // first flattening parameter
           m_b,    // Polar radius [m]
           m_f2,   // second flattening parameter
           m_n,    // third flattening parameter
           m_e2,   // the excentricity squared
           m_e,    // the ellipsoïd excentricity
           m_ep2,  // the second excentricity squared
           m_mp,   // Length of a quarter meridian
           // Convenient value used multiple times
           m_1_e2,    // 1 - m_e2
           m_a_1_e2,  // m_a * (1 - m_e2)
           m_1_f;     // 1 - m_f
    vector m_phimu,  // Coefficients of the inverse rectifying latitude
           m_phixi,  // Coefficients of the inverse authalic latitude
           m_phichi; // Coefficients of the inverse conformal latitude
    const std::size_t m_size_coeffs = 10;
    // ============== PRIVATE CLASS METHODS ==============
    void initInverseLattitudeCoeffs();
};

// Definition of classical Ellipsoïds
/*! ********************************************************************
 * \brief The Clarke 1880 IGN Ellipsoid
 *
 *
 *********************************************************************/
inline static Ellipsoid Clk80IGN(Constants::CLK80IGN_a,
                                 Constants::CLK80IGN_b,
                                 EllipsoidInit::fromRadiusAndRadius);

/*! ********************************************************************
 * \brief The GRS80 Ellipsoid
 *********************************************************************/
inline static Ellipsoid GRS80(Constants::GRS80_a,
                              Constants::GRS80_f,
                              EllipsoidInit::fromRadiusAndFlattening);

/*! ********************************************************************
 * \brief The WGS84 Ellipsoid
 *********************************************************************/
inline static Ellipsoid WGS84(Constants::WGS84_a,
                              Constants::WGS84_f,
                              EllipsoidInit::fromRadiusAndFlattening);

} // namespace Osl::Geography

} // namespace Osl

#endif // OSL_GEOGRAPHY_ELLIPSOID_H
