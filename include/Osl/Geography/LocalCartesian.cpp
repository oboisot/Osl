/*! ********************************************************************
 * \file LocalENU.cpp
 * \brief Source file of Osl::Geography::LocalENU class.
 *********************************************************************/

#include "LocalCartesian.h"

namespace Osl { // namespace Osl

namespace Geography { // namespace Osl::Geography

namespace LocalCartesian { // namespace Osl::Geography::LocalCartesian

// ====================
// ===== LocalENU =====
// ====================
LocalENU::LocalENU()
{

}

// ====================
// ===== LocalNED =====
// ====================
LocalNED::LocalNED(){}

LocalNED::LocalNED(const LocalNED &other):
    m_x0(other.m_x0), m_y0(other.m_y0), m_z0(other.m_z0),
    m_r00(other.m_r00), m_r01(other.m_r01), m_r02(other.m_r02),
    m_r10(other.m_r10), m_r11(other.m_r11), m_r12(other.m_r12),
    m_r20(other.m_r20), m_r21(other.m_r21), m_r22(other.m_r22){}

//LocalNED::LocalNED(const double &lon0, const double &lat0, const double &alt0,
//                   bool degrees)

} // namespace Osl::Geography::LocalCartesian

} // namespace Osl::Geography

} // namespace Osl
