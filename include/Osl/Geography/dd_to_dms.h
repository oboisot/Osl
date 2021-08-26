/*! ********************************************************************
 * \file dd_to_dms.h
 * \brief Header file of Osl::Geography::dd_to_dms function.
 *********************************************************************/

#ifndef OSL_GEOGRAPHY_DD_TO_DMS_H
#define OSL_GEOGRAPHY_DD_TO_DMS_H

#include <cmath>

namespace Osl { // namespace Osl

namespace Geography { // namespace Osl::Geography

/*! ********************************************************************
 * \brief Convert geodetic coordinates from decimal degrees to
 *        Degrees-Minutes-Seconds (DMS).
 *
 * This function allows to convert geodetic coordinates from
 * decimal degrees to Degrees-Minutes-Seconds (DMS).
 *
 * Decimal degrees \f$dd\f$ are converted to DMS coordinates
 * \f$d\f$, \f$m\f$, \f$s\f$ following the algorithm:
 *
 * -# \f$d = \big\lfloor\left\vert dd\right\vert\big\rfloor\f$
 * -# \f$m_d = 60\left(\left\vert dd\right\vert-d\right)\f$
 * -# \f$m = \big\lfloor m_t\big\rfloor\f$
 * -# \f$s = 60\left(m_t-m\right)\f$
 * -# \f$d = \mathrm{sign}(dd)d\f$
 *
 * \param [in] dd The decimal degrees representation of the geodetic coordinate.
 * \param [out] d, m, s The degrees, minutes and seconds representation of
 *              the geodetic coordinates in that order.
 *********************************************************************/
inline void dd_to_dms(const double &dd, double &d, double &m, double &s)
{
    if (dd < 0)
        s = 60.0 * std::modf(-60.0 * std::modf(dd, &d), &m);
    else
        s = 60.0 * std::modf(60.0 * std::modf(dd, &d), &m);
}

} // namespace Osl::Geography

} // namespace Osl

#endif // DD_TO_DMS_H
