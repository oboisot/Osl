/*! ********************************************************************
 * \file Rotation3D.h
 * \brief Header file of Osl::Geometry::Rotation3D class.
 *********************************************************************/

#ifndef OSL_GEOMETRY_ROTATION3D_H
#define OSL_GEOMETRY_ROTATION3D_H

#include <unordered_set>
#include "Osl/Constants.h"
#include "Vector3D.h"

namespace Osl { // namespace Osl

namespace Geometry { // namespace Osl::Geometry

class Rotation3D
{
public:
    //! Default Constructor.
    Rotation3D();

    //! Initialization from axis and angle.
    /*! ********************************************************************
     * \brief Rotation3D
     * \param axis
     * \param angle
     * \param degrees
     *********************************************************************/
    Rotation3D(const char &axis, const double &angle, bool degrees=true);

    //! Initialization from axis and angle.
    /*! ********************************************************************
     * \brief Rotation3D
     * \param axis
     * \param angle
     * \param degrees
     *********************************************************************/
    Rotation3D(const std::string &axis, const double &angle, bool degrees=true);

    //! Initialization from axis and angle.
    /*! ********************************************************************
     * \brief Rotation3D
     * \param axis
     * \param angle
     * \param degrees
     *********************************************************************/
    Rotation3D(const Vector3D &axis, const double &angle, bool degrees=true);

    //! Initialization from Euler angles
    /*! ********************************************************************
     * \brief Initialize the rotation matrix from Euler angles
     *        (proper and improper, using intrinsic definition)
     * \see <a href="https://en.wikipedia.org/wiki/Euler_angles">WIKI</a>
     * Returns the rotation matrix in the form : R = R(c[0],a1) * R(c[1],a2) * R(c[2],a2)
     * It must be noted that the application of a rotation matrix is made from right to left on the resulting vector
     *********************************************************************/
    Rotation3D(const std::string &convention, const double &a1,
               const double &a2, const double &a3, bool degrees=true);

    //! Initialization from two couple of non colinear vectors.
    /*! ********************************************************************
     * \brief Rotation3D
     * \param u1
     * \param v1
     * \param u2
     * \param v2
     *********************************************************************/
    Rotation3D(const Vector3D &u1, const Vector3D &v1,
               const Vector3D &u2, const Vector3D &v2);

    //! Initialization from matrix coefficients.
    /*! ********************************************************************
     * \brief Rotation3D
     * \param m00, m01, m02, m10, m11, m12, m20, m21, m22
     *********************************************************************/
    Rotation3D(const double &m00, const double &m01, const double &m02,
               const double &m10, const double &m11, const double &m12,
               const double &m20, const double &m21, const double &m22);

    //! Copy constructor
    /*! ********************************************************************
     * \brief Rotation3D
     * \param other
     */
    Rotation3D(const Rotation3D &other); // Copy constructor

    //! Default Destructor
    ~Rotation3D();

    // ============== CLASS METHODS ==============
    // ********** SETTER **********
    void setRotation(const char &axis, const double &angle, bool degrees=true);
    void setRotation(const std::string &axis, const double &angle, bool degrees=true);
    void setRotation(const Vector3D &axis, const double &angle, bool degrees=true);
    void setRotation(const std::string &convention, const double &a1, const double &a2, const double &a3, bool degrees=true);
    void setRotation(const Vector3D &u1, const Vector3D &v1, const Vector3D &u2, const Vector3D &v2);
    void setRotation(const double &m00, const double &m01, const double &m02,
                     const double &m10, const double &m11, const double &m12,
                     const double &m20, const double &m21, const double &m22);
    // ********** GETTER **********
    //! Get coefficient of the rotation matrix
    /*!
     * \brief getCoeff
     * \param row
     * \param col
     * \return
     */
    double getCoeff(std::size_t row, std::size_t col) const;

    //! Get roation matrix
    /*!
     * \brief getMatrix
     * \return
     */
    matrix getMatrix() const;

    // ============== OPERATORS ==============
    // Operators between matrices
    Rotation3D operator=(const Rotation3D &other); // Assignement from another Rotation3d
    Rotation3D operator*(const Rotation3D &other);
    Rotation3D &operator*=(const Rotation3D &other);

    //! Compute the product of this rotation matrix to a vector.
    /*!
     * \brief operator *
     * \param vec
     * \return
     */
    Vector3D operator*(const Vector3D &vec);

    // Comparison operators
    //! Check equality between two rotation matrices.
    /*!
     * \brief operator ==
     * \param other
     * \return
     * \sa operator != ()
     */
    bool operator==(const Rotation3D &other) const;
    bool operator!=(const Rotation3D &other) const;

    // ============== MATRIX FUNCTIONS ==============
    //! Compute the trace of the rotation matrix
    /*!
     * \brief trace
     * \return
     */
    double trace() const;

    //! Compute the matrix transpose of the rotation matrix
    /*!
     * \brief transpose
     * \return
     * \sa inverse()
     */
    Rotation3D transpose() const;

    //! Compute the inverse matrix of the rotation matrix
    /*!
     * \brief inverse
     * \return
     * \sa transpose()
     */
    Rotation3D inverse() const;

    //! Check if the rotation matrix is the identity matrix
    /*!
     * \brief isIdentity
     * \return
     */
    bool isIdentity() const;

    // ============== ROTATION MATRIX FUNCTIONS ==============
    //! Compute the rotation matrix as a "rotation vector"
    /*!
     * \brief getRotationVector
     * \param degrees
     * \return The rotation vector
     *
     * \see <a href="https://en.wikipedia.org/wiki/Axis%E2%80%93angle_representation#Rotation_vector">WIKI</a>
     *
     */
    Vector3D rotationVector(bool degrees=true) const;

    //! Compute Euler angles of the rotation matrix following the given convention.
    /*!
     * \brief getEulerAngles
     * \param convention
     * \param a1
     * \param a2
     * \param a3
     * \param degrees
     */
    void eulerAngles(const std::string &convention, double &a1, double &a2, double &a3, bool degrees=true) const;

private:
    // Private member
    matrix m_matrix{{1.0, 0.0, 0.0},
                    {0.0, 1.0, 0.0},
                    {0.0, 0.0, 1.0}};
    const std::size_t m_row = 3, m_col = 3;
};

inline std::ostream &operator<<(std::ostream &os, const Rotation3D &rot)
{
//    os << std::fixed;
    matrix mat = rot.getMatrix();
    matrix::iterator rowbegin = mat.begin(), rowend = mat.end();
    vector::iterator colbegin, colend;
    for (matrix::iterator row = rowbegin ; row != rowend ; ++row) // row loop
    {
        os << "(";
        colbegin = row->begin(), colend = row->end();
        for (vector::iterator col = colbegin ; col != colend ; ++col)
        {
            if (col != colend - 1)
                os << *col << " ";
            else
                os << *col;
        }
        if (row != rowend - 1)
            os << ")" << std::endl;
        else
            os << ")";
    }
    return os;
}

// Definition of Identity matrix
inline static Rotation3D Identity;

} // namespace Osl::Geometry

} // namespace Osl

#endif // OSL_GEOMETRY_ROTATION3D_H
