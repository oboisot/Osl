#ifndef OSL_GEOMETRY_VECTOR3D_H
#define OSL_GEOMETRY_VECTOR3D_H

#include "Osl/Globals.h"
#include "Osl/Maths/Comparison/almost_equal.h"
#include "Osl/Maths/Comparison/almost_one.h"
#include "Osl/Maths/Comparison/almost_zero.h"

/*! ********************************************************************
 * \file Vector3D.h
 * \brief Header file of Osl::Geometry::Vector3D class.
 *********************************************************************/

namespace Osl { // namespace Osl

namespace Geometry { // namespace Osl::Geometry

class Vector3D
{
public:
    //! Default Constructor.
    Vector3D();

    //! Constructor taking the 3 parameters of the vector.
    /*!
     * \brief Vector3D
     * \param x
     * \param y
     * \param z
     */
    Vector3D(const double &x, const double &y, const double &z);

    //! Copy constructor
    /*!
     * \brief Vector3D
     * \param other
     */
    Vector3D(const Vector3D &other); // Copy constructor

    //! Default Destructor
    ~Vector3D();

    // ============== CLASS METHODS ==============
    // ********** SETTER **********
    void setX(const double &x);
    void setY(const double &y);
    void setZ(const double &z);
    void setCoordinates(const double &x, const double &y, const double &z);
    // ********** GETTER **********
    double getX() const;
    double getY() const;
    double getZ() const;
    void getCoordinates(double &x, double &y, double &z);

    // ============== OPERATORS ==============
    // Unary operators
    Vector3D operator-();
    // Operations between vectors
    Vector3D operator=(const Vector3D &other); // Assignement from another vector
    Vector3D operator+(const Vector3D &other);  // Summation between vectors
    Vector3D &operator+=(const Vector3D &other);
    Vector3D operator-(const Vector3D &other);  // Differenciation between vectors
    Vector3D &operator-=(const Vector3D &other);
    // Scalar operations
    Vector3D operator*(const double &rhs);      // Multiplication
    Vector3D &operator*=(const double &rhs);
    Vector3D operator/(const double &rhs);      // Division
    Vector3D &operator/=(const double &rhs);
    // Comparison operators
    bool operator==(const Vector3D &other) const;
    bool operator!=(const Vector3D &other) const;

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
     * \brief isNull
     * \return
     */
    bool isNull() const;

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
    Vector3D normalized();

    // Vector / Vector operations
    /*!
     * \brief dotProduct
     * \return the result of the dot product between this vector and another
     */
    double dotProduct(const Vector3D &other);       // dot product

    /*!
     * \brief crossProduct
     * \return the resulting vector of the cross product between this vector and another
     */
    Vector3D crossProduct(const Vector3D &other); // Cross product

    /*!
     * \brief projectOn
     * \return the projection of this vector onto another one
     * \sa <a href="https://en.wikipedia.org/wiki/Vector_projection">WIKI</a>
     */
    Vector3D projectOn(const Vector3D &other);    // Projection of this vector onto another one

    /*!
     * \brief rejectFrom
     * \return the rejection of this vector from another one
     * \sa <a href="https://en.wikipedia.org/wiki/Vector_projection">WIKI</a>
     */
    Vector3D rejectFrom(const Vector3D &other);   // Rejection of this vector from another one

    /*!
     * \brief isColinear
     * \return true if this vector is colinear to another one, else return false.
     */
    bool isColinear(const Vector3D &other); // Is this vector colinear to another

    /*!
     * \brief isColinear
     * \return true if this vector is perpendicular to another one, else return false.
     */
    bool isPerpendicular(const Vector3D &other); // Is this vector perpendicular to another

private:
    double m_x = 0.0, m_y = 0.0, m_z = 0.0; // Default vector to null vector
};

// Reverse scalar multiplication (made global to the class)
inline Vector3D operator*(double lhs, Vector3D vec)
{
    return vec * lhs;
}

inline std::ostream &operator<<(std::ostream &os, const Vector3D &vec)
{
    os << "(" << vec.getX() << ", " << vec.getY() << ", " << vec.getZ() << ")";
    return os;
}

// Definition of classical vectors
inline static Vector3D NULL_VEC(0.0, 0.0, 0.0);
inline static Vector3D XAXIS(1.0, 0.0, 0.0),
                       YAXIS(0.0, 1.0, 0.0),
                       ZAXIS(0.0, 0.0, 1.0);

//! A vector container of Vector3D
typedef std::vector<Vector3D> vector3d;

} // namespace Osl::Geometry

} // namespace Osl

#endif // OSL_GEOMETRY_VECTOR3D_H
