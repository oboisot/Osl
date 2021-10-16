/*! ********************************************************************
 * \file LocalCartesian.h
 * \brief Header file of Osl::Geography::LocalENU and Osl::Geography::LocalNED
 *********************************************************************/

#ifndef OSL_GEOGRAPHY_LOCALENU_H
#define OSL_GEOGRAPHY_LOCALENU_H

#include "Ellipsoid.h"
#include "Osl/Geometry/Vector3D.h"
#include "Osl/Geometry/Rotation3D.h"

namespace Osl { // namespace Osl

namespace Geography { // namespace Osl::Geography

namespace LocalCartesian { // namespace Osl::Geography::LocalCartesian

class LocalENU
{
public:
    //! Default Constructor.
    LocalENU();

    //! Copy constructor
    LocalENU(const LocalENU &other);

    // ============== DESTRUCTOR ==============
    //! Default destructor
    ~LocalENU();

    // ============== CLASS METHODS ==============
    // ********** SETTER **********
    /*! ********************************************************************
     * \brief LocalENU
     * \param [in] elps
     * \param [in] X0 (lon0)
     * \param [in] Y0 (lat0)
     * \param [in] Z0 (alt0)
     * \param [in] init
     *********************************************************************/
//    void setFromGeocentric(Ellipsoid* elps, const double &x, const double &y, const double &z);

    /*! ********************************************************************
     * \brief LocalENU
     * \param [in] elps
     * \param [in] X0 (lon0)
     * \param [in] Y0 (lat0)
     * \param [in] Z0 (alt0)
     * \param [in] init
     *********************************************************************/
//    void setFromGeodetic(Ellipsoid* elps, double lon, double lat, double alt=0);

};


class LocalNED
{
public:
    //! Default Constructor.
    LocalNED();

    //! Copy constructor
    LocalNED(const LocalNED &other);

    /*! ********************************************************************
     * \brief LocalNED
     * \param [in] elps
     * \param [in] lon0
     * \param [in] lat0
     * \param [in] alt0
     * \param [in] init
     *********************************************************************/
//    LocalNED(const double &lon0, const double &lat0, const double &alt0,
//             Ellipsoid &elps=WGS84, bool degrees=true);

    /*! ********************************************************************
     * \brief LocalNED
     * \param [in] X0 (lon0)
     * \param [in] Y0 (lat0)
     * \param [in] Z0 (alt0)
     * \param [in] elps
     *********************************************************************/
//    LocalNED(const double &x0, const double &y0, const double &z0,
//             Ellipsoid &elps=WGS84);

    // ============== DESTRUCTOR ==============
    //! Default destructor
    ~LocalNED();

    // ============== CLASS METHODS ==============
    // ********** SETTER **********

    // ********** GETTER **********
    Geometry::Vector3D getOriginAsVector3D();
    void getOriginCoordinates(double &x0, double &y0, double &z0);
    Geometry::Rotation3D getGeocentricToNEDRotation();
    Geometry::Rotation3D getNEDtoGeocentricRotation();

    // ============== OPERATORS ==============

    //
    void geocentricPointToNEDPoint(const double &xgeo, const double &ygeo, const double &zgeo,
                                   double &xned, double &yned, double &zned);
    void geocentricVectorToNEDVector(const double &xgeo, const double &ygeo, const double &zgeo,
                                     double &xned, double &yned, double &zned);
    void NEDPointToGeocentricPoint(const double &xned, const double &yned, const double &zned,
                                   double &xgeo, double &ygeo, double &zgeo);
    void NEDVectorToGeocentricVector(const double &xned, const double &yned, const double &zned,
                                     double &xgeo, double &ygeo, double &zgeo);

private:
    double m_x0, m_y0, m_z0;
    double m_r00, m_r01, m_r02, // Rotation matrix ECEF -> NED
           m_r10, m_r11, m_r12, // note: rotation NED -> ECEF = transpose(R_ECEF->NED)
           m_r20, m_r21, m_r22;
};

} // namespace Osl::Geography::LocalCartesian

} // namespace Osl::Geography

} // namespace Osl

#endif // OSL_GEOGRAPHY_LOCALENU_H
