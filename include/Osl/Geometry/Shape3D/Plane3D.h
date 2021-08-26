/*! ********************************************************************
 * \file Plane3D.h
 * \brief Header file of Osl::Geometry::Shape3D::Plane3D class.
 *********************************************************************/

#ifndef OSL_GEOMETRY_SHAPE3D_PLANE3D_H
#define OSL_GEOMETRY_SHAPE3D_PLANE3D_H

#include "Osl/Geometry/Vector3D.h"

namespace Osl {

namespace Geometry {

namespace Shape3D {

class Plane3D
{
public:
    // ============== CONSTRUCTOR ==============
    Plane3D();
    Plane3D(const Vector3D &normal, const Vector3D &point);
    Plane3D(const Vector3D &u, const Vector3D &v, const Vector3D &point);
    Plane3D(const Vector3D &normal, const double &d);
    Plane3D(const Plane3D &other); // Copy constructor

    // ============== DESTRUCTOR ==============
    ~Plane3D();

    // ============== CLASS METHODS ==============
        // Setter
    void setPoint(const Vector3D &point);
    void setPoint(const double &px, const double &py, const double &pz);
    void setNormal(const Vector3D &normal);
    void setNormal(const double &nx, const double &ny, const double &nz);

        // Getter
    Vector3D getPoint() const;
    Vector3D getNormal() const;
    void getPlaneVectors(Vector3D &u, Vector3D &v);

    // ============== OPERATORS ==============
    // Operations between vectors
    Plane3D operator=(const Plane3D &other); // Assignement from another Plane
    // Comparison operators
    bool operator==(const Plane3D &other) const;
    bool operator!=(const Plane3D &other) const;
    // Function call
    Vector3D operator()(const double &t, const double &s);

    // ============== PLANE FUNCTIONS ==============
    double distanceToOrigin();
    double distanceToPoint(const Vector3D &point);

private:
    Vector3D m_normal = NULL_VEC, m_point = NULL_VEC;
    Vector3D m_u = NULL_VEC, m_v = NULL_VEC; // Two vectors of the plane

    void setPlaneVectors();
};

} // namespace Osl::Geometry::Shape3D

} // namespace Osl::Geometry

} // namespace Osl

#endif // OSL_GEOMETRY_SHAPE3D_PLANE3D_H
