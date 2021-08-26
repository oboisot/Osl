/*! ********************************************************************
 * \file Ellipsoid3D.h
 * \brief Header file of Osl::Geometry::Shape3D::Ellipsoid3D class.
 *********************************************************************/

#ifndef OSL_GEOMETRY_SHAPE3D_ELLIPSOID3D_H
#define OSL_GEOMETRY_SHAPE3D_ELLIPSOID3D_H

#include "Osl/Geometry/Vector3D.h"
#include "Osl/Geometry/Rotation3D.h"
#include "Sphere3D.h"

namespace Osl {

namespace Geometry {

namespace Shape3D {

class Ellipsoid3D
{
public:
    // ============== CONSTRUCTOR ==============
    Ellipsoid3D();
    Ellipsoid3D(const Vector3D &center,
                const double &xradius, const double &yradius, const double &zradius);
    Ellipsoid3D(const Vector3D &center,
                const double &xradius, const double &yradius, const double &zradius,
                const Vector3D &u, const Vector3D &v, const Vector3D &w);
    Ellipsoid3D(const Vector3D &center,
                const double &xradius, const double &yradius, const double &zradius,
                const Rotation3D &rotation);
    Ellipsoid3D (const Ellipsoid3D &elps); // Copy constructor

    // ============== DESTRUCTOR ==============
    ~Ellipsoid3D();

    // ============== CLASS METHODS ==============
        // Setter
    void setCenter(const Vector3D &center);
    void setCenter(const double &xc, const double &yc, const double &zc);
    void setRadii(const double &xradius, const double &yradius, const double &zradius);
    void setXradius(const double &xradius);
    void setYradius(const double &yradius);
    void setZradius(const double &zradius);
    void setRotation(const Rotation3D &rotation);
        // Getter
    Vector3D getCenter() const;
    double getXradius() const;
    double getYradius() const;
    double getZradius() const;
    Rotation3D getRotation() const;
    void getRadii(double &xradius, double &yradius, double &zradius);
    void getEllipsoidReferential(Vector3D &xaxis, Vector3D &yaxis, Vector3D &zaxis);

    // ============== OPERATORS ==============
    Ellipsoid3D operator=(const Ellipsoid3D &other); // Assignement from another Ellipsoid3D
    Ellipsoid3D operator=(const Sphere3D &other);    // Assignement from a Sphere3D
    // Comparison operators
    bool operator==(const Ellipsoid3D &other) const;
    bool operator!=(const Ellipsoid3D &other) const;
    // Function call
    Vector3D operator()(const double &lambda, const double &phi, bool degrees=true);

    // ============== ELLIPSOID3D METHODS ==============
    void scale(const double &scale);
    Ellipsoid3D scaled(const double &scale);
    void xScale(const double &xscale);
    Ellipsoid3D xScaled(const double &xscale);
    void yScale(const double &yscale);
    Ellipsoid3D yScaled(const double &yscale);
    void zScale(const double &zscale);
    Ellipsoid3D zScaled(const double &zscale);

private:
    Vector3D m_center = NULL_VEC;
    double m_xradius = 0.0,
           m_yradius = 0.0,
           m_zradius = 0.0;
    Rotation3D m_rotation; // Default to identity
    Vector3D m_u = XAXIS,  // Referential of the ellipsoid, default to default referential
             m_v = YAXIS,
             m_w = ZAXIS;
};

} // namespace Osl::Geometry::Shape3d

} // namespace Osl::Geometry

} // namespace Osl

#endif // OSL_GEOMETRY_SHAPE3D_ELLIPSOID3D_H
