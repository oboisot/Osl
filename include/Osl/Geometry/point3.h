#ifndef OSL_GEOMETRY_POINT3_H
#define OSL_GEOMETRY_POINT3_H


#include "Osl/Globals.h"
#include "Osl/Maths/Comparison/almost_equal.h"
#include "Osl/Maths/Comparison/almost_zero.h"

/*! ********************************************************************
 * \file Point3.h
 * \brief Header file of Osl::Geometry::Point3 class.
 *********************************************************************/

namespace Osl { // namespace Osl

namespace Geometry { // namespace Osl::Geometry

class Point3
{
public:
    //! Default Constructor.
    Point3();

    //! Constructor taking the 3 parameters of the vector.
    /*!
     * \brief Point3
     * \param x
     * \param y
     * \param z
     */
    Point3(const double &x, const double &y, const double &z);

    //! Copy constructor
    /*!
     * \brief Point3
     * \param other
     */
    Point3(const Point3 &other); // Copy constructor

    //! Default Destructor
    ~Point3();

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
    void operator-();
    // Operations between vectors
    Point3 operator=(const Point3 &other); // Assignement from another vector
    Point3 operator+(const Point3 &other); // Summation between vectors
    void operator+=(const Point3 &other);
    Point3 operator-(const Point3 &other); // Differenciation between vectors
    void operator-=(const Point3 &other);
    // Scalar operations
    Point3 operator*(const double &rhs);   // Multiplication
    void operator*=(const double &rhs);
    Point3 operator/(const double &rhs);   // Division
    void operator/=(const double &rhs);
    // Comparison operators
    bool operator==(const Point3 &other) const;
    bool operator!=(const Point3 &other) const;

    // Copy of this vector
    Point3 clone();

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

    // Vector / Vector operations
    /*!
     * \brief dotProduct
     * \return the result of the dot product between this vector and another
     */
    double dotProduct(const Point3 &other);       // dot product

    /*!
     * \brief crossProduct
     * \return the resulting vector of the cross product between this vector and another
     */
    void crossProduct(const Point3 &other); // Cross product

    /*!
     * \brief projectOn
     * \return the projection of this vector onto another one
     * \sa <a href="https://en.wikipedia.org/wiki/Vector_projection">WIKI</a>
     */
    void projectOn(const Point3 &other);    // Projection of this vector onto another one

    /*!
     * \brief rejectFrom
     * \return the rejection of this vector from another one
     * \sa <a href="https://en.wikipedia.org/wiki/Vector_projection">WIKI</a>
     */
    void rejectFrom(const Point3 &other);   // Rejection of this vector from another one

    /*!
     * \brief isColinear
     * \return true if this vector is colinear to another one, else return false.
     */
    bool isColinear(const Point3 &other); // Is this vector colinear to another

    /*!
     * \brief isColinear
     * \return true if this vector is perpendicular to another one, else return false.
     */
    bool isPerpendicular(const Point3 &other); // Is this vector perpendicular to another

private:
    double m_x = 0.0, m_y = 0.0, m_z = 0.0; // Default vector to null vector
};

// Reverse scalar multiplication (made global to the class)
inline Point3 operator*(double lhs, Point3 vec)
{
    return vec * lhs;
}

inline std::ostream &operator<<(std::ostream &os, Point3 point)
{
    double x, y, z;
    point.getCoordinates(x, y, z);
    os << "(" << x << ", " << y << ", " << z << ")";
    return os;
}

// Definition of classical vectors
inline static Point3 NULL_VEC;

} // namespace Osl::Geometry

} // namespace Osl

#endif // OSL_GEOMETRY_POINT3_H
