#ifndef OSL_GEOMETRY_VECTOR3_H
#define OSL_GEOMETRY_VECTOR3_H

#include "Osl/Globals.h"
#include "Osl/Maths/Comparison/almost_equal.h"
#include "Osl/Maths/Comparison/almost_one.h"
#include "Osl/Maths/Comparison/almost_zero.h"

/*! ********************************************************************
 * \file Vector3.h
 * \brief Header file of Osl::Geometry::Vector3 class.
 *********************************************************************/

namespace Osl { // namespace Osl

namespace Geometry { // namespace Osl::Geometry

class Vector3
{
public:
    //! x coordinate of the 3D vector, default to 0.0
    double x=0.0;
    //! y coordinate of the 3D vector, default to 0.0
    double y=0.0;
    //! z coordinate of the 3D vector, default to 0.0
    double z=0.0;

    //! Default Constructor.
    Vector3();

    //! Constructor taking the 3 parameters of the vector.
    /*!
     * \brief Vector3D
     * \param x
     * \param y
     * \param z
     */
    Vector3(const double &x, const double &y, const double &z);

    //! Copy constructor
    /*!
     * \brief Vector3D
     * \param other
     */
    Vector3(const Vector3 &other); // Copy constructor

    //! Default Destructor
    ~Vector3();

    // ============== CLASS METHODS ==============
    // ********** SETTER **********
    void setX(const double &xn);
    void setY(const double &yn);
    void setZ(const double &zn);
    void setCoordinates(const double &xn, const double &yn, const double &zn);
    // ********** GETTER **********
    double getX() const;
    double getY() const;
    double getZ() const;
    void getCoordinates(double &xn, double &yn, double &zn);

    // ============== OPERATORS ==============
    // Unary operators
    Vector3 operator-();
    // Operations between vectors
    Vector3 operator=(const Vector3 &other); // Assignement from another vector
    Vector3 operator+(const Vector3 &other);  // Summation between vectors
    Vector3 &operator+=(const Vector3 &other);
    Vector3 operator-(const Vector3 &other);  // Differenciation between vectors
    Vector3 &operator-=(const Vector3 &other);
    // Scalar operations
    Vector3 operator*(const double &rhs);      // Multiplication
    Vector3 &operator*=(const double &rhs);
    Vector3 operator/(const double &rhs);      // Division
    Vector3 &operator/=(const double &rhs);
    // Comparison operators
    bool operator==(const Vector3 &other) const;
    bool operator!=(const Vector3 &other) const;

    // ============== VECTOR OPERATIONS ==============
    /*!
     * \brief norm2
     * \return
     */
    double norm2() const;

    /*!
     * \brief norm
     * \return
     */
    double norm() const;

    /*!
     * \brief sum
     * \return
     */
    double sum() const;

    /*!
     * \brief In-place normalization of this vector.
     * \note If this vector is the null vector, it is returned without warning.
     * \sa normalized()
     */
    void normalize();

    /*!
     * \brief normalized
     * \return A normalized copy of the vector.
     * \note If the vector is the null vector, a null vector is returned.
     */
    Vector3 normalized();

    // Vector / Vector operations
    /*!
     * \brief dotProduct
     * \return the result of the dot product between this vector and another
     */
    double dotProduct(const Vector3 &other);       // dot product

    /*!
     * \brief crossProduct
     * \return the resulting vector of the cross product between this vector and another
     */
    Vector3 crossProduct(const Vector3 &other); // Cross product

    /*!
     * \brief projectOn
     * \return the projection of this vector onto another one
     * \sa <a href="https://en.wikipedia.org/wiki/Vector_projection">WIKI</a>
     */
    Vector3 projectOn(const Vector3 &other);    // Projection of this vector onto another one

    /*!
     * \brief rejectFrom
     * \return the rejection of this vector from another one
     * \sa <a href="https://en.wikipedia.org/wiki/Vector_projection">WIKI</a>
     */
    Vector3 rejectFrom(const Vector3 &other);   // Rejection of this vector from another one

    /*!
     * \brief isNull
     * \return
     */
    bool isNull() const;

    /*!
     * \brief isColinear
     * \return true if this vector is colinear to another one, else return false.
     */
    bool isColinear(const Vector3 &other); // Is this vector colinear to another

    /*!
     * \brief isColinear
     * \return true if this vector is perpendicular to another one, else return false.
     */
    bool isPerpendicular(const Vector3 &other); // Is this vector perpendicular to another
};

// Reverse scalar multiplication (made global to the class)
inline Vector3 operator*(double lhs, Vector3 vec)
{
    return vec * lhs;
}

inline std::ostream &operator<<(std::ostream &os, const Vector3 &vec)
{
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

// Definition of classical vectors
inline static Vector3 NULL_VECTOR(0.0, 0.0, 0.0);
inline static Vector3 XAXIS(1.0, 0.0, 0.0),
                      YAXIS(0.0, 1.0, 0.0),
                      ZAXIS(0.0, 0.0, 1.0);

} // namespace Osl::Geometry

} // namespace Osl

#endif // VECTOR3_H
