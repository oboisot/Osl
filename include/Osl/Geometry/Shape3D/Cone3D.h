/*! ********************************************************************
 * \file Cone3D.h
 * \brief Header file of Osl::Geometry::Shape3D::Cone3D class.
 *********************************************************************/

#ifndef OSL_GEOMETRY_SHAPE3D_CONE3D_H
#define OSL_GEOMETRY_SHAPE3D_CONE3D_H

#include "Osl/Geometry/Vector3D.h"
#include "Osl/Geometry/Rotation3D.h"

namespace Osl {

namespace Geometry {

namespace Shape3D {

class Cone3D
{
public:
    // ============== CONSTRUCTOR ==============
    // *****************************************
    // * An elliptic cone is defined from its cartesian equation:
    // *
    // * (x - xc)^2 / tan(xangle) + (y - yc)^2 / tan(yangle) = (z - zc)^2
    // *
    // * for an elliptic cone whose revolution axis is oriented following the
    // * z-axis direction with opening
    // * HALF-angles 'xangle' and 'yangle' following the x-axis and y-axis
    // * directions, respectively. The origin, or vertex, of the cone is
    // * given by point C = (xc, yc, zc).
    // *
    // * For an elliptic cone whose referential differs from the absolute
    // * cartesian system (x_r, y_r, z_r) the rotation matrix passing from
    // * the absolute reference system to the referetal attached to the
    // * elliptic cone can be passed as argument. The full rotation matrix is
    // * necessary to keep orientation of the opening HALF-angles.
    // ******************************************
    Cone3D();
    Cone3D(const Vector3D &vertex, const double &xangle, const double &yangle,
           bool degrees=true);
    Cone3D(const Vector3D &vertex, const double &xangle, const double &yangle,
           const Rotation3D &rotation, bool degrees=true);
    Cone3D(const Cone3D &cone); // Copy constructor

    // ============== DESTRUCTOR ==============
    ~Cone3D();

    // ============== CLASS METHODS ==============
        // Setter
    void setVertex(const Vector3D &vertex);
    void setVertex(const double &xc, const double &yc, const double &zc);
    void setOpeningAngles(const double &xangle, const double &yangle, bool degrees=true);
    void setOpeningXangle(const double &xangle, bool degrees=true);
    void setOpeningYangle(const double &yangle, bool degrees=true);
    void setRotation(const Rotation3D &rotation);
        // Getter
    Vector3D getVertex() const;
    double getOpeningXangle(bool degrees=true) const;
    double getOpeningYangle(bool degrees=true) const;
    Rotation3D getRotation() const;
    void getOpeningAngles(double &xangle, double &yangle, bool degrees=true);
    void getEllipticConeReferential(Vector3D &xaxis, Vector3D &yaxis, Vector3D &zaxis);

    // ============== OPERATORS ==============
    Cone3D operator=(const Cone3D &other); // Assignement from another Cone3D
        // Comparison operators
    bool operator==(const Cone3D &other) const;
    bool operator!=(const Cone3D &other) const;
    // Function call
    Vector3D operator()(const double &f, const double &theta, bool degrees=true);

    // ============== ELLIPTICCONE3D METHODS ==============
    void scale(const double &scale);
    Cone3D scaled(const double &scale);
    void xAngleScale(const double &xscale);
    Cone3D xAngleScaled(const double &xscale);
    void yAngleScale(const double &yscale);
    Cone3D yAngleScaled(const double &yscale);
//    Vector3D pointAt(const double &f, const double &theta, bool degrees=true);

private:
    Vector3D m_vertex = NULL_VEC;
    double m_xangle = 0.0,
           m_yangle = 0.0; // Opening angles, default main axis of the cone is the z-axis.
    Rotation3D m_rotation;

    //
    void setXangleDegrees(const double &xangle);
    void setYangleDegrees(const double &yangle);
    void setXangleRadians(const double &xangle);
    void setYangleRadians(const double &yangle);
};

} // namespace Osl::Geometry::Shape3D

} // namespace Osl::Geometry

} // namespace Osl

#endif // OSL_GEOMETRY_SHAPE3D_CONE3D_H
