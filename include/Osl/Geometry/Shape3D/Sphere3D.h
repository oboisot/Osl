/*! ********************************************************************
 * \file Sphere3D.h
 * \brief Header file of Osl::Geometry::Shape3D::Sphere3D class.
 *********************************************************************/

#ifndef OSL_GEOMETRY_SHAPE3D_SPHERE3D_H
#define OSL_GEOMETRY_SHAPE3D_SPHERE3D_H

#include "Osl/Geometry/Vector3D.h"
#include "Osl/Geometry/Rotation3D.h"

namespace Osl {

namespace Geometry {

namespace Shape3D {

class Sphere3D
{
public:
    // ============== CONSTRUCTOR ==============
    Sphere3D();
    Sphere3D(const Vector3D &center, const double &radius);
    Sphere3D(const Vector3D &center, const double &radius, const Rotation3D &rotation);
    Sphere3D(const Sphere3D &sphere); // Copy constructor

    // ============== DESTRUCTOR ==============
    ~Sphere3D();

    // ============== CLASS METHODS ==============
        // Setter
    void setCenter(const Vector3D &center);
    void setCenter(const double &xc, const double &yc, const double &zc);
    void setRadius(const double &radius);
    void setRotation(const Rotation3D &rotation);
        // Getter
    Vector3D getCenter() const;
    double getRadius() const;
    Rotation3D getRotation() const;
    void getSphereReferential(Vector3D &xaxis, Vector3D &yaxis, Vector3D &zaxis);

    // ============== OPERATORS ==============
    // Operations between vectors
    Sphere3D operator=(const Sphere3D &other); // Assignement from another Sphere3D
    // Comparison operators
    bool operator==(const Sphere3D &other) const;
    bool operator!=(const Sphere3D &other) const;
    // Function call
    Vector3D operator()(const double &lambda, const double &phi, bool degrees=true);

    // ============== SPHERE3D METHODS ==============
    void scale(const double &scale);
    Sphere3D scaled(const double &scale);

private:
    Vector3D m_center = NULL_VEC;
    double m_radius = 0.0;
    Rotation3D m_rotation; // Initialize to identity
};

} // namespace Osl::Geometry::Shape3D

} // namespace Osl::Geometry

} // namespace Osl

#endif // OSL_GEOMETRY_SHAPE3D_SPHERE3D_H
