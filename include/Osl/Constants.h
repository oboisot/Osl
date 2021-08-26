/*! ********************************************************************
 * \file Constants.h
 * \brief Header file for the Osl::Constants namespace.
 * \namespace Osl::Constants This is the Osl::Constants namespace which
 *            provides a set of numerical, mathematical, physical and
 *            geodesic constants.
 *********************************************************************/

#ifndef OSL_CONSTANTS_H
#define OSL_CONSTANTS_H

#include <limits>

namespace Osl { // Osl namespace

namespace Constants { // Osl::Constants namespace

/*! ********************************************************************
 * \brief Numeric resolution for double precision floating point.
 * 
 * The resolution is taken as 10 times the C ISO norm for double
 * precision resolution
 * <a href="https://en.wikipedia.org/wiki/
 * Machine_epsilon#Values_for_standard_hardware_floating_point_arithmetics"
 * target="_blank">[Wiki]</a>:
 * 
 * \f[
 *     res=10\times10^{-15}=10^{-14}
 * \f]
 * 
 * This resolution is used mainly for comparison between two double
 * precision numbers.
 *********************************************************************/
inline static constexpr double n_machine_res         = 1e-14;

/*! ********************************************************************
 * \brief Machine epsilon for double precision floating point.
 * 
 * The machine epsilon for double precision floating point is given by
 * <a href="https://en.wikipedia.org/wiki/Machine_epsilon"
 * target="_blank">[Wiki]</a>:
 * 
 * \f[
 *     \epsilon=2^{-52}\simeq 2.22\times10^{-16}
 * \f]
 * 
 * and gives the maximum relative error of the rounding of a double
 * precision floating point value. This constant is computed through
 * the <a href="https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon" 
 * target="_blank">std::numeric_limits<double>::epsilon()</a> function.
 *********************************************************************/
inline static constexpr double n_machine_eps = std::numeric_limits<double>::epsilon();

/*! ********************************************************************
 * Definition of the mathematical constant \f$\pi\f$.
 *********************************************************************/
inline static constexpr double m_pi          = static_cast<double>(3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798);
/*! ********************************************************************
 * Definition of the mathematical constant \f$\pi/2\f$.
 *********************************************************************/
inline static constexpr double m_pi_2        = static_cast<double>(1.57079632679489661923132169163975144209858469968755291048747229615390820314310449931401741267105853399);
/*! ********************************************************************
 * Definition of the mathematical constant \f$\pi/3\f$.
 *********************************************************************/
inline static constexpr double m_pi_3        = static_cast<double>(0.590817950301838675766055827780381727599183152040795709404602596617637094863677393791650218912848221805);
/*! ********************************************************************
 * Definition of the mathematical constant \f$\pi/4\f$.
 *********************************************************************/
inline static constexpr double m_pi_4        = static_cast<double>(0.785398163397448309615660845819875721049292349843776455243736148076954101571552249657008706335529266995);
/*! ********************************************************************
 * Definition of the mathematical constant \f$\pi/6\f$.
 *********************************************************************/
inline static constexpr double m_pi_6        = static_cast<double>(0.295408975150919337883027913890190863799591576020397854702301298308818547431838696895825109456424110903);
/*! ********************************************************************
 * Definition of the mathematical constant \f$\pi/8\f$.
 *********************************************************************/
inline static constexpr double m_pi_8        = static_cast<double>(0.392699081698724154807830422909937860524646174921888227621868074038477050785776124828504353167764633498);
/*! ********************************************************************
 * Definition of the mathematical constant \f$\pi/12\f$.
 *********************************************************************/
inline static constexpr double m_pi_12       = static_cast<double>(0.147704487575459668941513956945095431899795788010198927351150649154409273715919348447912554728212055451);
/*! ********************************************************************
 * Definition of the mathematical constant \f$2\pi\f$.
 *********************************************************************/
inline static constexpr double m_double_pi   = static_cast<double>(6.28318530717958647692528676655900576839433879875021164194988918461563281257241799725606965068423413596);
/*! ********************************************************************
 * Definition of the mathematical constant \f$\pi^2\f$.
 *********************************************************************/
inline static constexpr double m_pi_square   = static_cast<double>(9.86960440108935861883449099987615113531369940724079062641334937622004482241920524300177340371855223182);
/*! ********************************************************************
 * Definition of the mathematical constant \f$1/\pi\f$.
 *********************************************************************/
inline static constexpr double m_inv_pi      = static_cast<double>(0.318309886183790671537767526745028724068919291480912897495334688117793595268453070180227605532506171912);
/*! ********************************************************************
 * Definition of the mathematical constant \f$\sqrt{\pi}\f$.
 *********************************************************************/
inline static constexpr double m_sqrt_pi     = static_cast<double>(1.77245385090551602729816748334114518279754945612238712821380778985291128459103218137495065673854466542);
/*! ********************************************************************
 * Definition of the mathematical constant \f$1/\sqrt{\pi}=\sqrt{pi}/\pi\f$.
 *********************************************************************/
inline static constexpr double m_inv_sqrt_pi = static_cast<double>(0.564189583547756286948079451560772585844050629328998856844085721710642468441493414486743660202107363443);
/*! ********************************************************************
 * Conversion factor from degrees to radians \f$\pi/180\f$.
 *********************************************************************/
inline static constexpr double m_degtorad    = static_cast<double>(0.0174532925199432957692369076848861271344287188854172545609719144017100911460344944368224156963450948221);
/*! ********************************************************************
 * Conversion factor from radians to degrees \f$180/\pi\f$.
 *********************************************************************/
inline static constexpr double m_radtodeg    = static_cast<double>(57.2957795130823208767981548141051703324054724665643215491602438612028471483215526324409689958511109442);
/*! ********************************************************************
 * Definition of classical rational number \f$1/3\f$.
 *********************************************************************/
inline static constexpr double m_1_3         = static_cast<double>(0.333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333);
/*! ********************************************************************
 * Definition of classical rational number \f$2/3\f$.
 *********************************************************************/
inline static constexpr double m_2_3         = static_cast<double>(0.666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666);
/*! ********************************************************************
 * Definition of classical rational number \f$1/6\f$.
 *********************************************************************/
inline static constexpr double m_1_6         = static_cast<double>(0.166666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666);
/*! ********************************************************************
 * Definition of classical irrational number \f$\sqrt{2}\f$.
 *********************************************************************/
inline static constexpr double m_sqrt_2      = static_cast<double>(1.41421356237309504880168872420969807856967187537694807317667973799073247846210703885038753432764157274);
/*! ********************************************************************
 * Definition of classical irrational number \f$1/\sqrt{2}=\sqrt{2}/2\f$.
 *********************************************************************/
inline static constexpr double m_inv_sqrt_2  = static_cast<double>(0.707106781186547524400844362104849039284835937688474036588339868995366239231053519425193767163820786368);
/*! ********************************************************************
 * Definition of classical irrational number \f$\sqrt{3}\f$.
 *********************************************************************/
inline static constexpr double m_sqrt_3      = static_cast<double>(1.73205080756887729352744634150587236694280525381038062805580697945193301690880003708114618675724857568);
/*! ********************************************************************
 * Definition of classical irrational number \f$1/\sqrt{3}=\sqrt{3}/3\f$.
 *********************************************************************/
inline static constexpr double m_inv_sqrt_3  = static_cast<double>(0.577350269189625764509148780501957455647601751270126876018602326483977672302933345693715395585749525225);
/*! ********************************************************************
 * Definition of the natural exponential \f$e\f$.
 *********************************************************************/
inline static constexpr double m_exp         = static_cast<double>(2.71828182845904523536028747135266249775724709369995957496696762772407663035354759457138217852516642743);
/*! ********************************************************************
 * Definition of the base 2 logarithm \f$\mathrm{ln}(2)\f$.
 *********************************************************************/
inline static constexpr double m_ln2         = static_cast<double>(0.693147180559945309417232121458176568075500134360255254120680009493393621969694715605863326996418687542);
/*! ********************************************************************
 * Definition of the base 2 logarithm \f$1/\mathrm{ln}(2)\f$.
 *********************************************************************/
inline static constexpr double m_inv_ln2     = static_cast<double>(1.4426950408889634073599246810018921374266459541529859341354494069311092191811850798855266228935063445);
/*! ********************************************************************
 * Definition of the base 10 logarithm \f$\mathrm{ln}(10)\f$.
 *********************************************************************/
inline static constexpr double m_ln10        = static_cast<double>(2.30258509299404568401799145468436420760110148862877297603332790096757260967735248023599720508959829834);
/*! ********************************************************************
 * Definition of the base 2 logarithm \f$1/\mathrm{ln}(10)\f$.
 *********************************************************************/
inline static constexpr double m_inv_ln10    = static_cast<double>(0.434294481903251827651128918916605082294397005803666566114453783165864649208870774729224949338431748319);


/*! ********************************************************************
 * \brief Speed of light in vacuum.
 * 
 * The fundamental constant of the speed of light in vacuum is given by
 * <a href="https://physics.nist.gov/cgi-bin/cuu/Value?c|search_for=speed+of+light"
 * target="_blank">[NIST:c]</a>:
 * 
 * \f[
 *     c=299792458.0\quad\mbox{m.s$^{-1}$}
 * \f]
 *********************************************************************/
inline static constexpr double p_c   = static_cast<double>(299792458.0);
/*! ********************************************************************
 * \brief Vacuum electric permittivity.
 * 
 * The fundamental constant of the vacuum electric permittivity is given
 * by <a href="https://physics.nist.gov/cgi-bin/cuu/
 * Value?ep0|search_for=Vacuum+electric+permittivity"
 * target="_blank">[NIST:eps0]</a>:
 * 
 * \f[
 *     \epsilon_0=8.8541878128\times10^{-12}\quad\mbox{F.m$^{-1}$}
 * \f]
 *********************************************************************/
inline static constexpr double p_eps0 = static_cast<double>(8.8541878128e-12);
/*! ********************************************************************
 * \brief Vacuum magnetic permeability.
 * 
 * The fundamental constant of the vacuum magnetic permeability is given
 * by <a href="https://physics.nist.gov/cgi-bin/cuu/
 * Value?mu0|search_for=vacuum+magnetic+permeability"
 * target="_blank">[NIST:mu0]</a>:
 * 
 * \f[
 *     \mu_0=1.25663706212\times10^{-6}\quad\mbox{H.m$^{-1}$}
 * \f]
 *********************************************************************/
inline static constexpr double p_mu0  = static_cast<double>(1.25663706212e-6);
/*! ********************************************************************
 * \brief Planck constant.
 * 
 * The fundamental Planck constant is given by
 * <a href="https://physics.nist.gov/cgi-bin/cuu/
 * Value?h|search_for=planck+constant" target="_blank">[NIST:h]</a>:
 * 
 * \f[
 *     h=6.62607015\times10^{-34}\quad\mbox{J.Hz$^{-1}$}
 * \f]
 *********************************************************************/
inline static constexpr double p_h    = static_cast<double>(6.62607015e-34);
/*! ********************************************************************
 * \brief Newtonian constant of gravitation.
 * 
 * The fundamental newtonian constant of gravitation is given by
 * <a href="https://physics.nist.gov/cgi-bin/cuu/
 * Value?bg|search_for=newtonian+constant+of+gravitation"
 * target="_blank">[NIST:G]</a>:
 * 
 * \f[
 *     G=6.67430\times10^{-11}\quad\mbox{m$^3$.kg$^{-1}$.s$^{-2}$}
 * \f]
 *********************************************************************/
inline static constexpr double p_G    = static_cast<double>(6.67430e-11);
/*! ********************************************************************
 * \brief Standard acceleration of gravity.
 * 
 * The fundamental standard acceleration of gravity constant is given
 * by <a href="https://physics.nist.gov/cgi-bin/cuu/
 * Value?gn|search_for=standard+acceleration+of+gravity"
 * target="_blank">[NIST:gn]</a>:
 * 
 * \f[
 *     g_n=9.80665\quad\mbox{m.s$^{-2}$}
 * \f]
 *********************************************************************/
inline static constexpr double p_gn   = static_cast<double>(9.80665);

/*! ********************************************************************
 * \brief Equatorial radius of the WGS84 Ellipsoid.
 * 
 * The equatorial radius of the World Geodetic System 1984 (G1762) datum
 * (WGS84) Ellipsoid is defined as
 * <a href="https://epsg.org/datum_1156/World-Geodetic-System-1984-G1762.html"
 * target="_blank">[EPSG:WGS84]</a>:
 * 
 * \f[
 *     a=6378137.0\quad\mbox{m}
 * \f]
 *********************************************************************/
inline static constexpr double WGS84_a = static_cast<double>(6378137.0);
/*! ********************************************************************
 * \brief Flattening parameter of the WGS84 Ellipsoid.
 * 
 * The flattening parameter of the World Geodetic System 1984 (G1762) datum
 * (WGS84) Ellipsoid is defined as
 * <a href="https://epsg.org/datum_1156/World-Geodetic-System-1984-G1762.html"
 * target="_blank">[EPSG:WGS84]</a>:
 * 
 * \f[
 *     1/f=298.257223563
 * \f]
 *********************************************************************/
inline static constexpr double WGS84_f = static_cast<double>(1.0/298.257223563);

/*! ********************************************************************
 * \brief Equatorial radius of the GRS80 Ellipsoid.
 * 
 * The equatorial radius of the Geodetic Reference System 1980 (GRS80)
 * Ellipsoid is defined as
 * <a href="https://epsg.org/ellipsoid_7019/GRS-1980.html"
 * target="_blank">[EPSG:GRS80]</a>:
 * 
 * \f[
 *     a=6378137.0\quad\mbox{m}
 * \f]
 *********************************************************************/
inline static constexpr double GRS80_a = static_cast<double>(6378137.0);
/*! ********************************************************************
 * \brief Flattening parameter of the GRS80 Ellipsoid.
 * 
 * The flattening parameter of the Geodetic Reference System 1980 (GRS80)
 * Ellipsoid is defined as
 * <a href="https://epsg.org/ellipsoid_7019/GRS-1980.html"
 * target="_blank">[EPSG:GRS80]</a>:
 * 
 * \f[
 *     1/f=298.257222101
 * \f]
 *********************************************************************/
inline static constexpr double GRS80_f = static_cast<double>(1.0/298.257222101);

/*! ********************************************************************
 * \brief Equatorial radius of the Clarke 1880 IGN Ellipsoid.
 * 
 * The equatorial radius of the Nouvelle Triangulation Française (NTF)
 * datum Ellipsoid, Clarke 1880 IGN, is defined as
 * <a href="https://epsg.org/datum_6275/Nouvelle-Triangulation-Francaise.html"
 * target="_blank">[EPSG:NTF]</a>:
 * 
 * \f[
 *     a=6378249.2\quad\mbox{m}
 * \f]
 *********************************************************************/
inline static constexpr double CLK80IGN_a = static_cast<double>(6378249.2);
/*! ********************************************************************
 * \brief Polar radius of the Clarke 1880 IGN Ellipsoid. 
 * 
 * The polar radius of the Nouvelle Triangulation Française (NTF) datum
 * Ellipsoid, Clarke 1880 IGN, is defined as
 * <a href="https://epsg.org/datum_6275/Nouvelle-Triangulation-Francaise.html"
 * target="_blank">[EPSG:NTF]</a>:
 * 
 * \f[
 *     b=6356515.0\quad\mbox{m}
 * \f]
 *********************************************************************/
inline static constexpr double CLK80IGN_b = static_cast<double>(6356515.0);


} // Osl::Constants

} // Osl

#endif // OSL_CONSTANTS_H
