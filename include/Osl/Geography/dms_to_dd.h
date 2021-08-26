/*! ********************************************************************
 * \file dms_to_dd.h
 * \brief Header file of Osl::Geography::dms_to_dd function.
 *********************************************************************/

#ifndef OSL_GEOGRAPHY_DMS_TO_DD_H
#define OSL_GEOGRAPHY_DMS_TO_DD_H

namespace Osl { // namespace Osl

namespace Geography { // namespace Osl::Geography

/*! ********************************************************************
 * \brief Convert geodetic coordinates from Degrees-Minutes-Seconds (DMS)
 *        to decimal degrees.
 *
 * This function allows to convert geodetic coordinates from
 * Degrees-Minutes-Seconds (DMS) to decimal degrees. The orientation
 * of the coordinates (North-South, or West-East) are taken into
 * account through the sign of the \em d (degree) parameter with +1
 * for North or East orientation and -1 for South or West orientation.
 *
 * DMS coordinates (\f$d\f$, \f$m\f$, \f$s\f$) are converted to
 * decimal degrees \f$dd\f$ through the relationship:
 *
 * \f[
 *     dd=\mathrm{sign}(d)\left(\vert d\vert+\dfrac{m}{60}+\dfrac{s}{3600}\right)
 * \f]
 *
 *
 * \param [in] d, m, s The degrees, minutes and seconds representation of
 *             the geodetic coordinates in that order.
 * \returns The decimal degrees representation of the geodetic coordinate.
 *********************************************************************/
inline double dms_to_dd(const double &d, const double &m, const double &s)
{
    if (d < 0)
        return -(-d + m / 60.0 + s / 3600.0);
    return d + m / 60.0 + s / 3600.0;
}

/*! ********************************************************************
 * \brief Convert geodetic coordinates from Degrees-Minutes-Seconds (DMS)
 *        to decimal degrees.
 *
 * This function allows to convert geodetic coordinates from
 * Degrees-Minutes-Seconds (DMS) to decimal degrees. The orientation
 * of the coordinates (North-South, or West-East) are taken into
 * account through the sign of the \em d (degree) parameter with +1
 * for North or East orientation and -1 for South or West orientation.
 *
 * DMS coordinates (\f$d\f$, \f$m\f$, \f$s\f$) are converted to
 * decimal degrees \f$dd\f$ through the relationship:
 *
 * \f[
 *     dd=\mathrm{sign}(d)\left(\vert d\vert+\dfrac{m}{60}+\dfrac{s}{3600}\right)
 * \f]
 *
 *
 * \param [in] d, m, s The degrees, minutes and seconds representation of
 *             the geodetic coordinates in that order.
 * \param [out] dd The decimal degrees representation of the geodetic coordinate.
 *********************************************************************/
inline void dms_to_dd(const double &d, const double &m, const double &s, double &dd)
{
    if (d < 0)
        dd = -(-d + m / 60.0 + s / 3600.0);
    else
        dd = d + m / 60.0 + s / 3600.0;
}

} // namespace Osl::Geometry

} // namespace Osl

#endif // OSL_GEOGRAPHY_DMS_TO_DD_H
