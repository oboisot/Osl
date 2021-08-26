/*! ********************************************************************
 * \file Line3D.h
 * \brief Header file of Osl::Geometry::Shape3D::Line3D class.
 *********************************************************************/

#ifndef OSL_GEOMETRY_SHAPE3D_LINE3D_H
#define OSL_GEOMETRY_SHAPE3D_LINE3D_H

#include "Osl/Geometry/Vector3D.h"

namespace Osl {

namespace Geometry {

namespace Shape3D {

class Line3D
{
public:
    // ============== CONSTRUCTOR ==============
    Line3D();
    Line3D(const Vector3D &point, const Vector3D &direction);
    Line3D(const Line3D &other); // Copy constructor

    // ============== DESTRUCTOR ==============
    ~Line3D();

    // ============== CLASS METHODS ==============
        // Setter
    void setPoint(const Vector3D &point);
    void setPoint(const double &px, const double &py, const double &pz);
    void setDirection(const Vector3D &direction);
    void setDirection(const double &dx, const double &dy, const double &dz);

        // Getter
    Vector3D getPoint() const;
    Vector3D getDirection() const;

    // ============== OPERATORS ==============
    // Operations between vectors
    Line3D operator=(const Line3D &other); // Assignement from another Line
    // Comparison operators
    bool operator==(const Line3D &other) const;
    bool operator!=(const Line3D &other) const;
    // Function call
    Vector3D operator()(const double &t);

private:
    Vector3D m_point = NULL_VEC, m_direction = NULL_VEC;
};

} // namespace Osl::Geometry::Shape3D

} // namespace Osl::Geometry

} // namespace Osl

#endif // OSL_GEOMETRY_SHAPE3D_LINE3D_H
