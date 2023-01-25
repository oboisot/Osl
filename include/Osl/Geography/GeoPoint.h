/*! ********************************************************************
 * \file GeoPoint.h
 * \brief Header file of Osl::Geography::GeoPoint class.
 *********************************************************************/

#ifndef OSL_GEOGRAPHY_GEOPOINT_H
#define OSL_GEOGRAPHY_GEOPOINT_H

#include "Ellipsoid.h"
#include "Osl/Maths/Comparison/almost_equal.h"

namespace Osl { // namespace Osl

namespace Geography { // namespace Osl::Geography

/*! ********************************************************************
 * \enum GeoPointInit
 * \brief Enumeration for the initialization of the GeoPoint class.
 *********************************************************************/
enum class GeoPointInit
{
    /*! GeoPoint initialization from geodetic coordinates.*/
    fromGeodetic,
    /*! GeoPoint initialization from geocentric coordinates.*/
    fromGeocentric
};

class GeoPoint
{
public:
    // ============== CONSTRUCTOR ==============
    //! Default Constructor.
    /*!
     * \brief GeoPoint
     * \note The default constructor uses WGS84 ellipsoid as default.
     */
    GeoPoint();

    //!
    /*!
     * \brief GeoPoint
     * \param elps
     * \param lon, lat
     * \param alt
     * \param init
     * \param degrees (It has no effect if init==GeoPointInit::fromGeocentric)
     */
    GeoPoint(Ellipsoid* elps,
             const double &lon, const double &lat, const double &alt,
             enum GeoPointInit init=GeoPointInit::fromGeodetic,
             bool degrees=true);

    //! Copy constructor
    GeoPoint(const GeoPoint &other);

    //! Default destructor
    ~GeoPoint();

    // ============== CLASS METHODS ==============
    // ********** SETTER **********
    void setCoords(const double &lon, const double &lat, const double &alt,
                   enum GeoPointInit init=GeoPointInit::fromGeodetic,
                   bool degrees=true);
    void setGeocentricCoords(const double &x, const double &y, const double &z);
    void setGeodeticCoords(const double &lon_rad, const double &lat_rad, const double &alt);

    // ********** GETTER **********
    void getGeodeticCoords(double &lon, double & lat, double &alt,
                           bool degrees=true);
    double getLon(bool degrees=true) const;
    double getLat(bool degrees=true) const;
    double getAlt() const;
    void getGeocentricCoords(double &x, double &y, double &z);
    double getX() const;
    double getY() const;
    double getZ() const;
    Ellipsoid* getEllipsoidPtr() const;

    // ============== OPERATORS ==============
    GeoPoint operator=(const GeoPoint &other); // Assignement from another GeoPoint
    // Comparison operators
    bool operator==(const GeoPoint &other) const;
    bool operator!=(const GeoPoint &other) const;

    // ============== GEOPOINT FUNCTIONS ==============
    /*! Transform a GeoPoint from a reference ellipsoid to another.
     *
     * The transformation is made through Helmert's formulation which is a
     * 7-parameters similitude transform. The algorithm of the transform is as
     * follows:
     *
     * 1. Transform geodetic coordinates to cartesian coordinates:
     *
     *    \f[
     *      (\lambda_1,\phi_1,h_1)\rightarrow(X_1,Y_1,Z_1)
     *    \f]
     *
     *    This is made by default in the initialization of a GeoPoint.
     *
     * 2. Compute the similitude transform:
     *
     *    \f[
     *      \begin{pmatrix}X_2 \\ Y_2 \\ Z_2\end{pmatrix} =
     *      \begin{pmatrix}T_x \\ T_y \\ T_z\end{pmatrix} +
     *      (1+s)
     *      \mathbf{R}\begin{pmatrix}X_1 \\ Y_1 \\ Z_1\end{pmatrix}
     *    \f]
     *
     *    with \f$\overrightarrow{T}=(T_x,T_y,T_z)\f$ is the translation
     *    from Ellipsoid 1 to Ellipsoid 2, \f$s\f$ is the scale factor
     *    of the transformation and \f$\mathbf{R}\f$ is the rotation matrix
     *    between referential 1 and referential 2. This rotation matrix can be
     *    taken exact:
     *
     *    \f[
     *      \mathbf{R}(\theta_x,\theta_y,\theta_z)=
     *          R_x(\theta_x)R_y(\theta_y)R_z(\theta_z)
     *    \f]
     *
     *    where \f$R_x\f$, \f$R_y\f$ and \f$R_z\f$ are the elementary rotation
     *    matrix of angles \f$\theta_x\f$, \f$\theta_y\f$ and \f$\theta_z\f$
     *    around axes \f$x\f$, \f$y\f$ and \f$z\f$, respectively.
     *    This rotation matrix is often approximated by its small angles
     *    version:
     *
     *    \f[
     *      R=\begin{pmatrix}
     *            1  & -\theta_z  &  \theta_y \\
     *            \theta_z &  1    & -\theta_x \\
     *            -\theta_y &  \theta_x  &  1  \\
     *        \end{pmatrix}
     *    \f]
     *
     * 3. Once the new geocentric coordinates \f$(X_2,Y_2,Z_2)\f$ are
     *    computed the corresponding geodetic coordinates are estimated:
     *
     *    \f[
     *      (X_2,Y_2,Z_2)\rightarrow(\lambda_2,\phi_2,h_2)
     *    \f]
     *
     * \brief toEllipsoid
     * \param elps2
     * \param T12x, T12y, T12z
     * \param R12x, R12y, R12z
     * \param degrees
     * \return
     *
     * \note This method is numerically more acurate than the historical
     * analytical Molodensky method \cite Deakin_04.
     */
    GeoPoint toEllipsoid(Ellipsoid *elps2,
                         const double &T12x, const double &T12y, const double &T12z,
                         const double &R12x=0.0, const double &R12y=0.0, const double &R12z=0.0,
                         const double &S12=0.0, bool degrees=false);

    void toEllipsoidInplace(Ellipsoid *elps2,
                            const double &Tx, const double &Ty, const double &Tz,
                            const double &Rx=0.0, const double &Ry=0.0, const double &Rz=0.0,
                            const double &scale=0.0);

private:
    Ellipsoid *m_elps = WGS84;        // The referential Ellipsoid (default to WGS84 Ellipsoid)
//    Geometry::Vector3D m_geocentric;  // Contains the geocentric coordinates
    double m_x, m_y, m_z,
           m_lon_rad, m_lat_rad,      // longitude and latitude in radians
           m_alt;                     // altitude in meters
};

} // namespace Osl::Geometry

} // namespace Osl

#endif // OSL_GEOGRAPHY_GEOPOINT_H
