#include "Rotation3D.h"

namespace Osl { // namespace Osl

namespace Geometry { // namespace Osl::Geometry

static const std::unordered_set<std::string> EULER_CONVENTION = {
    "xyz", "xzy", "yxz", "yzx", "zxy", "zyx", // Tait-Bryan angles (Euler improper)
    "xyx", "xzx", "yxy", "yzy", "zxz", "zyz"  // Euler angles
};

// ============== CONSTRUCTOR ==============
Rotation3D::Rotation3D(){}

    // Initialization of elementary rotations
Rotation3D::Rotation3D(const char &axis, const double &angle, bool degrees)
{
    double ang_rad = degrees ? angle * Constants::m_degtorad : angle;
    double c = std::cos(ang_rad),  // Cosine of the rotation angle
           s = std::sin(ang_rad);  // Sine of the rotation angle
    switch (axis)
    {
    case 'x':
        // X-axis rotation matrix
        m_matrix[0][0] = 1, m_matrix[0][1] = 0, m_matrix[0][2] = 0;
        m_matrix[1][0] = 0, m_matrix[1][1] = c, m_matrix[1][2] = -s;
        m_matrix[2][0] = 0, m_matrix[2][1] = s, m_matrix[2][2] = c;
        break;
    case 'y':
        // Y-axis rotation matrix
        m_matrix[0][0] = c,  m_matrix[0][1] = 0, m_matrix[0][2] = s;
        m_matrix[1][0] = 0,  m_matrix[1][1] = 1, m_matrix[1][2] = 0;
        m_matrix[2][0] = -s, m_matrix[2][1] = 0, m_matrix[2][2] = c;
        break;
    case 'z':
        // Z-axis rotation matrix
        m_matrix[0][0] = c, m_matrix[0][1] = -s, m_matrix[0][2] = 0;
        m_matrix[1][0] = s, m_matrix[1][1] = c,  m_matrix[1][2] = 0;
        m_matrix[2][0] = 0, m_matrix[2][1] = 0,  m_matrix[2][2] = 1;
        break;
    default:
        throw std::invalid_argument("Osl::Geometry::Rotation3D.setRotation(): "
                                    "axis must be a char between 'x', 'y' or 'z'.");
    }
}

Rotation3D::Rotation3D(const std::string &axis, const double &angle, bool degrees)
{
    double ang_rad = degrees ? angle * Constants::m_degtorad : angle;
    double c = std::cos(ang_rad),  // Cosine of the rotation angle
           s = std::sin(ang_rad);  // Sine of the rotation angle
    if (axis == "x") // X-axis rotation matrix
    {
        m_matrix[0][0] = 1, m_matrix[0][1] = 0, m_matrix[0][2] = 0;
        m_matrix[1][0] = 0, m_matrix[1][1] = c, m_matrix[1][2] = -s;
        m_matrix[2][0] = 0, m_matrix[2][1] = s, m_matrix[2][2] = c;
    }
    else if (axis == "y") // Y-axis rotation matrix
    {
        m_matrix[0][0] = c,  m_matrix[0][1] = 0, m_matrix[0][2] = s;
        m_matrix[1][0] = 0,  m_matrix[1][1] = 1, m_matrix[1][2] = 0;
        m_matrix[2][0] = -s, m_matrix[2][1] = 0, m_matrix[2][2] = c;
    }
    else if (axis == "z") // Z-axis rotation matrix
    {
        m_matrix[0][0] = c, m_matrix[0][1] = -s, m_matrix[0][2] = 0;
        m_matrix[1][0] = s, m_matrix[1][1] = c,  m_matrix[1][2] = 0;
        m_matrix[2][0] = 0, m_matrix[2][1] = 0,  m_matrix[2][2] = 1;
    }
    else
        throw std::invalid_argument("Osl::Geometry::Rotation3D.setRotation(): "
                                    "axis must be a string between \"x\", \"y\" or \"z\".");
}

    // Initialization from given axis and angle
Rotation3D::Rotation3D(const Vector3D &axis, const double &angle, bool degrees)
{
    // Rotation angle
    double ang_rad = degrees ? angle * Constants::m_degtorad : angle;
    double c = std::cos(ang_rad),  // Cosine of the rotation angle
           s = std::sin(ang_rad);  // Sine of the rotation angle
    // Rotation axis
    Vector3D n_axis = axis; n_axis.normalize();// Normalized axis
    double x, y, z;
    n_axis.getCoordinates(x, y, z);
    // Rotation matrix
    double mc = 1 - c;
    double xyc = x * y * mc, xzc = x * z * mc, yzc = y * z * mc;
    double xs = x * s, ys = y * s, zs = z * s;
    m_matrix[0][0] = c + x * x * mc;
    m_matrix[0][1] = xyc - zs;
    m_matrix[0][2] = xzc + ys;
    m_matrix[1][0] = xyc + zs;
    m_matrix[1][1] = c + y * y * mc;
    m_matrix[1][2] = yzc - xs;
    m_matrix[2][0] = xzc - ys;
    m_matrix[2][1] = yzc + xs;
    m_matrix[2][2] = c + z * z * mc;
}

Rotation3D::Rotation3D(const std::string &convention,
                       const double &a1, const double &a2, const double &a3, bool degrees)
{
    //if (EULER_CONVENTION.contains(convention)) // C++20
    if (EULER_CONVENTION.find(convention) != EULER_CONVENTION.end())
    {
        Rotation3D r1(convention[0], a1, degrees);
        Rotation3D r2(convention[1], a2, degrees);
        Rotation3D r3(convention[2], a3, degrees);
        m_matrix = (r1 * r2 * r3).m_matrix;
    }
    else
        throw std::invalid_argument("Osl::Geometry::Rotation3D.setRotation(): "
                                    "'convention' is not a recognized convention.");
}

    // Initialization from two couple of vectors
Rotation3D::Rotation3D(const Vector3D &u1, const Vector3D &v1,
                       const Vector3D &u2, const Vector3D &v2)
{
    // Repère orthonormé formé à partir de u1 et v1, u1 -> x, v1 -> y, w1 -> z
    Vector3D u1n = u1; u1n.normalize();
    Vector3D v1n = v1; v1n = v1n.rejectFrom(u1); v1n.normalize();
    Vector3D w1n = u1n.crossProduct(v1n);

    // Repère orthonormé formé à partir de u2 et v2, u2 -> x, v2 -> y, w2 -> z
    Vector3D u2n = u2; u2n.normalize();
    Vector3D v2n = v2; v2n = v2n.rejectFrom(u2); v2n.normalize();
    Vector3D w2n = u2n.crossProduct(v2n);

    // Transpose of the rotation matrix from referential 0 to referential 1
    double u1nx, u1ny, u1nz, v1nx, v1ny, v1nz, w1nx, w1ny, w1nz;
    u1n.getCoordinates(u1nx, u1ny, u1nz);
    v1n.getCoordinates(v1nx, v1ny, v1nz);
    w1n.getCoordinates(w1nx, w1ny, w1nz);
    Rotation3D R01T(u1nx, u1ny, u1nz,
                    v1nx, v1ny, v1nz,
                    w1nx, w1ny, w1nz);

    // Rotation matrix from referential 0 to referential 2
    double u2nx, u2ny, u2nz, v2nx, v2ny, v2nz, w2nx, w2ny, w2nz;
    u2n.getCoordinates(u2nx, u2ny, u2nz);
    v2n.getCoordinates(v2nx, v2ny, v2nz);
    w2n.getCoordinates(w2nx, w2ny, w2nz);
    Rotation3D R02(u2nx, v2nx, w2nx,
                   u2ny, v2ny, w2ny,
                   u2nz, v2nz, w2nz);
    // Rotation matrix from referential 1 to referential 2: R12 = R02 * R01T
    m_matrix = (R02 * R01T).m_matrix;
}

    // Initialization from matrix coefficients
Rotation3D::Rotation3D(const double &m00, const double &m01, const double &m02,
                       const double &m10, const double &m11, const double &m12,
                       const double &m20, const double &m21, const double &m22)
{
    m_matrix[0][0] = m00, m_matrix[0][1] = m01, m_matrix[0][2] = m02;
    m_matrix[1][0] = m10, m_matrix[1][1] = m11, m_matrix[1][2] = m12;
    m_matrix[2][0] = m20, m_matrix[2][1] = m21, m_matrix[2][2] = m22;
}

// Copy constructor
Rotation3D::Rotation3D(const Rotation3D &other)
    : m_matrix(other.m_matrix) {}

// ============== DESTRUCTOR ==============
Rotation3D::~Rotation3D(){}

// ============== CLASS METHODS ==============
// ********** SETTER **********
void Rotation3D::setRotation(const char &axis, const double &angle, bool degrees)
{
    double ang_rad = degrees ? angle * Constants::m_degtorad : angle;
    double c = std::cos(ang_rad),  // Cosine of the rotation angle
           s = std::sin(ang_rad);  // Sine of the rotation angle
    switch (axis)
    {
    case 'x':
        // X-axis rotation matrix
        m_matrix[0][0] = 1, m_matrix[0][1] = 0, m_matrix[0][2] = 0;
        m_matrix[1][0] = 0, m_matrix[1][1] = c, m_matrix[1][2] = -s;
        m_matrix[2][0] = 0, m_matrix[2][1] = s, m_matrix[2][2] = c;
        break;
    case 'y':
        // Y-axis rotation matrix
        m_matrix[0][0] = c,  m_matrix[0][1] = 0, m_matrix[0][2] = s;
        m_matrix[1][0] = 0,  m_matrix[1][1] = 1, m_matrix[1][2] = 0;
        m_matrix[2][0] = -s, m_matrix[2][1] = 0, m_matrix[2][2] = c;
        break;
    case 'z':
        // Z-axis rotation matrix
        m_matrix[0][0] = c, m_matrix[0][1] = -s, m_matrix[0][2] = 0;
        m_matrix[1][0] = s, m_matrix[1][1] = c,  m_matrix[1][2] = 0;
        m_matrix[2][0] = 0, m_matrix[2][1] = 0,  m_matrix[2][2] = 1;
        break;
    default:
        throw std::invalid_argument("Osl::Geometry::Rotation3D.setRotation(): "
                                    "axis must be a char between 'x', 'y' or 'z'.");
    }
}

void Rotation3D::setRotation(const std::string &axis, const double &angle, bool degrees)
{
    double ang_rad = degrees ? angle * Constants::m_degtorad : angle;
    double c = std::cos(ang_rad),  // Cosine of the rotation angle
           s = std::sin(ang_rad);  // Sine of the rotation angle
    if (axis == "x") // X-axis rotation matrix
    {
        m_matrix[0][0] = 1, m_matrix[0][1] = 0, m_matrix[0][2] = 0;
        m_matrix[1][0] = 0, m_matrix[1][1] = c, m_matrix[1][2] = -s;
        m_matrix[2][0] = 0, m_matrix[2][1] = s, m_matrix[2][2] = c;
    }
    else if (axis == "y") // Y-axis rotation matrix
    {
        m_matrix[0][0] = c,  m_matrix[0][1] = 0, m_matrix[0][2] = s;
        m_matrix[1][0] = 0,  m_matrix[1][1] = 1, m_matrix[1][2] = 0;
        m_matrix[2][0] = -s, m_matrix[2][1] = 0, m_matrix[2][2] = c;
    }
    else if (axis == "z") // Z-axis rotation matrix
    {
        m_matrix[0][0] = c, m_matrix[0][1] = -s, m_matrix[0][2] = 0;
        m_matrix[1][0] = s, m_matrix[1][1] = c,  m_matrix[1][2] = 0;
        m_matrix[2][0] = 0, m_matrix[2][1] = 0,  m_matrix[2][2] = 1;
    }
    else
        throw std::invalid_argument("Osl::Geometry::Rotation3D.setRotation(): "
                                    "axis must be a string between \"x\", \"y\" or \"z\".");
}

void Rotation3D::setRotation(const Vector3D &axis, const double &angle, bool degrees)
{
    // Rotation angle
    double ang_rad = degrees ? angle * Constants::m_degtorad : angle;
    double c = std::cos(ang_rad),  // Cosine of the rotation angle
           s = std::sin(ang_rad);  // Sine of the rotation angle
    // Rotation axis
    Vector3D n_axis = axis; n_axis.normalize();// Normalized axis
    double x, y, z;
    n_axis.getCoordinates(x, y, z);
    // Rotation matrix
    double mc = 1 - c;
    double xyc = x * y * mc, xzc = x * z * mc, yzc = y * z * mc;
    double xs = x * s, ys = y * s, zs = z * s;
    m_matrix[0][0] = c + x * x * mc;
    m_matrix[0][1] = xyc - zs;
    m_matrix[0][2] = xzc + ys;
    m_matrix[1][0] = xyc + zs;
    m_matrix[1][1] = c + y * y * mc;
    m_matrix[1][2] = yzc - xs;
    m_matrix[2][0] = xzc - ys;
    m_matrix[2][1] = yzc + xs;
    m_matrix[2][2] = c + z * z * mc;
}

void Rotation3D::setRotation(const std::string &convention, const double &a1, const double &a2, const double &a3, bool degrees)
{
    //if (EULER_CONVENTION.contains(convention)) // C++20
    if (EULER_CONVENTION.find(convention) != EULER_CONVENTION.end())
    {
        Rotation3D r1(convention[0], a1, degrees);
        Rotation3D r2(convention[1], a2, degrees);
        Rotation3D r3(convention[2], a3, degrees);
        m_matrix = (r1 * r2 * r3).m_matrix;
    }
    else
        throw std::invalid_argument("Osl::Geometry::Rotation3D.setRotation(): "
                                    "'convention' is not a recognized convention.");
}

void Rotation3D::setRotation(const Vector3D &u1, const Vector3D &v1, const Vector3D &u2, const Vector3D &v2)
{
    // Repère orthonormé formé à partir de u1 et v1, u1 -> x, v1 -> y, w1 -> z
    Vector3D u1n = u1; u1n.normalize();
    Vector3D v1n = v1; v1n = v1n.rejectFrom(u1); v1n.normalize();
    Vector3D w1n = u1n.crossProduct(v1n);

    // Repère orthonormé formé à partir de u2 et v2, u2 -> x, v2 -> y, w2 -> z
    Vector3D u2n = u2; u2n.normalize();
    Vector3D v2n = v2; v2n = v2n.rejectFrom(u2); v2n.normalize();
    Vector3D w2n = u2n.crossProduct(v2n);

    // Transpose of the rotation matrix from referential 0 to referential 1
    double u1nx, u1ny, u1nz, v1nx, v1ny, v1nz, w1nx, w1ny, w1nz;
    u1n.getCoordinates(u1nx, u1ny, u1nz);
    v1n.getCoordinates(v1nx, v1ny, v1nz);
    w1n.getCoordinates(w1nx, w1ny, w1nz);
    Rotation3D R01T(u1nx, u1ny, u1nz,
                    v1nx, v1ny, v1nz,
                    w1nx, w1ny, w1nz);

    // Rotation matrix from referential 0 to referential 2
    double u2nx, u2ny, u2nz, v2nx, v2ny, v2nz, w2nx, w2ny, w2nz;
    u2n.getCoordinates(u2nx, u2ny, u2nz);
    v2n.getCoordinates(v2nx, v2ny, v2nz);
    w2n.getCoordinates(w2nx, w2ny, w2nz);
    Rotation3D R02(u2nx, v2nx, w2nx,
                   u2ny, v2ny, w2ny,
                   u2nz, v2nz, w2nz);
    // Rotation matrix from referential 1 to referential 2: R12 = R02 * R01T
    m_matrix = (R02 * R01T).m_matrix;
}

void Rotation3D::setRotation(const double &m00, const double &m01, const double &m02,
                             const double &m10, const double &m11, const double &m12,
                             const double &m20, const double &m21, const double &m22)
{
    m_matrix[0][0] = m00, m_matrix[0][1] = m01, m_matrix[0][2] = m02;
    m_matrix[1][0] = m10, m_matrix[1][1] = m11, m_matrix[1][2] = m12;
    m_matrix[2][0] = m20, m_matrix[2][1] = m21, m_matrix[2][2] = m22;
}

// ********** GETTER **********
double Rotation3D::getCoeff(std::size_t row, std::size_t col) const
{
    if ((row < 3) && (col < 3))
        return m_matrix[row][col];
    else
        throw std::invalid_argument("Osl::Geometry::Rotation3D.getCoeff(): "
                                    "Index must lies between 0 and 2.");
}

matrix Rotation3D::getMatrix() const
{
    return m_matrix;
}

// ============== OPERATORS ==============
// Assignement from another Rotation3D
Rotation3D Rotation3D::operator=(const Rotation3D &other)
{
    m_matrix = other.m_matrix;
    return *this;
}

Rotation3D Rotation3D::operator*(const Rotation3D &other)
{
    Rotation3D rot;
    for (std::size_t row = 0 ; row < m_row ; ++row)
    {
        for (std::size_t col = 0 ; col < m_col ; ++col)
        {
            rot.m_matrix[row][col] = 0.0;
            for (std::size_t k = 0 ; k < m_col ; ++k)
                rot.m_matrix[row][col] += m_matrix[row][k] * other.m_matrix[k][col];
        }
    }
    return rot;
}

Rotation3D &Rotation3D::operator*=(const Rotation3D &other)
{
    // Rotation3D rot = (*this) * other;
    // m_matrix = rot.m_matrix;
    m_matrix = ((*this) * other).m_matrix;
    return *this;
}

Vector3D Rotation3D::operator*(const Vector3D &vec)
{
    Vector3D vec_tmp = vec;
    double x, y, z;
    vec_tmp.getCoordinates(x, y, z);
    return Vector3D(m_matrix[0][0] * x + m_matrix[0][1] * y + m_matrix[0][2] * z,
                    m_matrix[1][0] * x + m_matrix[1][1] * y + m_matrix[1][2] * z,
                    m_matrix[2][0] * x + m_matrix[2][1] * y + m_matrix[2][2] * z);
}

// Comparison operators
bool Rotation3D::operator==(const Rotation3D &other) const
{
    for (std::size_t row = 0 ; row < m_row ; ++row)
    {
        for (std::size_t col = 0 ; col < m_col ; ++col)
        {
            if (!Maths::Comparison::almost_equal(m_matrix[row][col], other.m_matrix[row][col]))
                return false;
        }
    }
    return true;
}

bool Rotation3D::operator!=(const Rotation3D &other) const
{
    return !(*this == other);
}

// ============== MATRIX FUNCTIONS ==============
double Rotation3D::trace() const
{
    return m_matrix[0][0] + m_matrix[1][1] + m_matrix[2][2];
}

Rotation3D Rotation3D::transpose() const
{
    return Rotation3D(m_matrix[0][0], m_matrix[1][0], m_matrix[2][0],
                      m_matrix[0][1], m_matrix[1][1], m_matrix[2][1],
                      m_matrix[0][2], m_matrix[1][2], m_matrix[2][2]);
}

Rotation3D Rotation3D::inverse() const
{
    return this->transpose();
}

bool Rotation3D::isIdentity() const
{
    return *this == Identity;
}

// ============== ROTATION MATRIX FUNCTIONS ==============
Vector3D Rotation3D::rotationVector(bool degrees) const
{
    Vector3D axis(m_matrix[2][1] - m_matrix[1][2],
                  m_matrix[0][2] - m_matrix[2][0],
                  m_matrix[1][0] - m_matrix[0][1]);
    axis.normalize();
    double angle = std::acos(0.5 * (this->trace() - 1));
    if (degrees)
        angle *= Constants::m_radtodeg;
    return axis * angle;
}

void Rotation3D::eulerAngles(const std::string &convention,
                             double &a1, double &a2, double &a3, bool degrees) const
{
    if (EULER_CONVENTION.find(convention) != EULER_CONVENTION.end())
    {
        // ===== TAIT-BRYAN ANGLES CONVENTION =====
        if (convention == "xyz") // R = RxRyRz
        {
            if (m_matrix[0][2] < 1)
            {
                if (m_matrix[0][2] > -1)
                {
                    a1 = std::atan2(-m_matrix[1][2], m_matrix[2][2]);
                    a2 = std::asin(m_matrix[0][2]);
                    a3 = std::atan2(-m_matrix[0][1], m_matrix[0][0]);
                }
                else // m02 = -1
                {
                    // Not a unique solution: a3 - a1 = atan2(m10, m11)
                    a1 = -std::atan2(m_matrix[1][0], m_matrix[1][1]);
                    a2 = -Constants::m_pi_2;
                    a3 = 0.0;
                }
            }
            else // m02 = +1
            {
                // Not a unique solution: a3 + a1 = atan2(m10, m11)
                a1 = std::atan2(m_matrix[1][0], m_matrix[1][1]);
                a2 = Constants::m_pi_2;
                a3 = 0.0;
            }
        }
        else if (convention == "xzy")
        {
            if (m_matrix[0][1] < 1)
            {
                if (m_matrix[0][1] > -1)
                {
                    a1 = std::atan2(m_matrix[2][1], m_matrix[1][1]);
                    a2 = std::asin(-m_matrix[0][1]);
                    a3 = std::atan2(m_matrix[0][2], m_matrix[0][0]);
                }
                else // m01 = -1
                {
                    // Not a unique solution: a3 - a1 = atan2(-m20, m22)
                    a1 = -std::atan2(-m_matrix[2][0], m_matrix[2][2]);
                    a2 = Constants::m_pi_2;
                    a3 = 0.0;
                }
            }
            else // m01 = +1
            {
                a1 = std::atan2(-m_matrix[2][0], m_matrix[2][2]);
                a2 = -Constants::m_pi_2;
                a3 = 0.0;
            }
        }
        else if (convention == "yxz")
        {
            if (m_matrix[1][2] < 1)
            {
                if (m_matrix[1][2] > -1)
                {
                    a1 = std::atan2(m_matrix[0][2], m_matrix[2][2]);
                    a2 = std::asin(-m_matrix[1][2]);
                    a3 = std::atan2(m_matrix[1][0], m_matrix[1][1]);
                }
                else // m12 = -1
                {
                    // Not a unique solution: a3 - a1 = atan2(-m01, m00)
                    a1 = -std::atan2(-m_matrix[0][1], m_matrix[0][0]);
                    a2 = Constants::m_pi_2;
                    a3 = 0.0;
                }
            }
            else // m12 = +1
            {
                a1 = std::atan2(-m_matrix[0][1], m_matrix[0][0]);
                a2 = -Constants::m_pi_2;
                a3 = 0.0;
            }
        }
        else if (convention == "yzx")
        {
            if (m_matrix[1][0] < 1)
            {
                if (m_matrix[1][0] > -1)
                {
                    a1 = std::atan2(-m_matrix[2][0], m_matrix[0][0]);
                    a2 = std::asin(m_matrix[1][0]);
                    a3 = std::atan2(-m_matrix[1][2], m_matrix[1][1]);
                }
                else // m10 = -1
                {
                    // Not a unique solution: a3 - a1 = atan2(m21, m22)
                    a1 = -std::atan2(m_matrix[2][1], m_matrix[2][2]);
                    a2 = -Constants::m_pi_2;
                    a3 = 0.0;
                }
            }
            else // m10 = +1
            {
                a1 = std::atan2(m_matrix[2][1], m_matrix[2][2]);
                a2 = Constants::m_pi_2;
                a3 = 0.0;
            }
        }
        else if (convention == "zxy")
        {
            if (m_matrix[2][1] < 1)
            {
                if (m_matrix[2][1] > -1)
                {
                    a1 = std::atan2(-m_matrix[0][1], m_matrix[1][1]);
                    a2 = std::asin(m_matrix[2][1]);
                    a3 = std::atan2(-m_matrix[2][0], m_matrix[2][2]);
                }
                else // m21 = -1
                {
                    // Not a unique solution: a3 - a1 = atan2(m02, m00)
                    a1 = -std::atan2(m_matrix[0][2], m_matrix[0][0]);
                    a2 = -Constants::m_pi_2;
                    a3 = 0.0;
                }
            }
            else // m21 = +1
            {
                a1 = std::atan2(m_matrix[0][2], m_matrix[0][0]);
                a2 = Constants::m_pi_2;
                a3 = 0.0;
            }
        }
        else if (convention == "zyx")
        {
            if (m_matrix[2][0] < 1)
            {
                if (m_matrix[2][0] > -1)
                {
                    a1 = std::atan2(m_matrix[1][0], m_matrix[0][0]);
                    a2 = std::asin(-m_matrix[2][0]);
                    a3 = std::atan2(m_matrix[2][1], m_matrix[2][2]);
                }
                else // m20 = -1
                {
                    // Not a unique solution: a3 - a1 = atan2(-m12, m11)
                    a1 = -std::atan2(-m_matrix[1][2], m_matrix[1][1]);
                    a2 = Constants::m_pi_2;
                    a3 = 0.0;
                }
            }
            else // m20 = +1
            {
                a1 = std::atan2(-m_matrix[1][2], m_matrix[1][1]);
                a2 = -Constants::m_pi_2;
                a3 = 0.0;
            }
        } // ===== END OF TAIT-BRYAN ANGLES CONVENTION =====
        // ===== EULER ANGLES CONVENTION =====
        else if (convention == "xyx")
        {
            if (m_matrix[0][0] < 1)
            {
                if (m_matrix[0][0] > -1)
                {
                    a1 = std::atan2(m_matrix[1][0], -m_matrix[2][0]);
                    a2 = std::acos(m_matrix[0][0]);
                    a3 = std::atan2(m_matrix[0][1], m_matrix[0][2]);
                }
                else // m00 = -1
                {
                    // Not a unique solution: a3 - a1 = atan2(-m12, m11)
                    a1 = -std::atan2(-m_matrix[1][2], m_matrix[1][1]);
                    a2 = Constants::m_pi;
                    a3 = 0.0;
                }
            }
            else // m00 = +1
            {
                a1 = std::atan2(-m_matrix[1][2], m_matrix[1][1]);
                a2 = 0.0;
                a3 = 0.0;
            }
        }
        else if (convention == "xzx")
        {
            if (m_matrix[0][0] < 1)
            {
                if (m_matrix[0][0] > -1)
                {
                    a1 = std::atan2(m_matrix[2][0], m_matrix[1][0]);
                    a2 = std::acos(m_matrix[0][0]);
                    a3 = std::atan2(m_matrix[0][2], -m_matrix[0][1]);
                }
                else // m00 = -1
                {
                    // Not a unique solution: a3 - a1 = atan2(-m12, m11)
                    a1 = -std::atan2(m_matrix[2][1], m_matrix[2][2]);
                    a2 = Constants::m_pi;
                    a3 = 0.0;
                }
            }
            else // m00 = +1
            {
                a1 = std::atan2(m_matrix[2][1], m_matrix[2][2]);
                a2 = 0.0;
                a3 = 0.0;
            }
        }
        else if (convention == "yxy")
        {
            if (m_matrix[1][1] < 1)
            {
                if (m_matrix[1][1] > -1)
                {
                    a1 = std::atan2(m_matrix[0][1], m_matrix[2][1]);
                    a2 = std::acos(m_matrix[1][1]);
                    a3 = std::atan2(m_matrix[1][0], -m_matrix[1][2]);
                }
                else // m11 = -1
                {
                    // Not a unique solution: a3 - a1 = -atan2(m02, m00)
                    a1 = -std::atan2(m_matrix[0][2], m_matrix[0][0]);
                    a2 = Constants::m_pi;
                    a3 = 0.0;
                }
            }
            else // m11 = +1
            {
                a1 = std::atan2(m_matrix[0][2], m_matrix[0][0]);
                a2 = 0.0;
                a3 = 0.0;
            }
        }
        else if (convention == "yzy")
        {
            if (m_matrix[1][1] < 1)
            {
                if (m_matrix[1][1] > -1)
                {
                    a1 = std::atan2(m_matrix[2][1], -m_matrix[0][1]);
                    a2 = std::acos(m_matrix[1][1]);
                    a3 = std::atan2(m_matrix[1][2], m_matrix[1][0]);
                }
                else // m11 = -1
                {
                    // Not a unique solution: a3 - a1 = atan2(-m20, m22)
                    a1 = -std::atan2(-m_matrix[2][0], m_matrix[2][2]);
                    a2 = Constants::m_pi;
                    a3 = 0.0;
                }
            }
            else // m11 = +1
            {
                a1 = std::atan2(-m_matrix[2][0], m_matrix[2][2]);
                a2 = 0.0;
                a3 = 0.0;
            }
        }
        else if (convention == "zxz")
        {
            if (m_matrix[2][2] < 1)
            {
                if (m_matrix[2][2] > -1)
                {
                    a1 = std::atan2(m_matrix[0][2], -m_matrix[1][2]);
                    a2 = std::acos(m_matrix[2][2]);
                    a3 = std::atan2(m_matrix[2][0], m_matrix[2][1]);
                }
                else // m22 = -1
                {
                    // Not a unique solution: a3 - a1 = atan2(-m01, m00)
                    a1 = -std::atan2(-m_matrix[0][1], m_matrix[0][0]);
                    a2 = Constants::m_pi;
                    a3 = 0.0;
                }
            }
            else // m22 = +1
            {
                a1 = std::atan2(-m_matrix[0][1], m_matrix[0][0]);
                a2 = 0.0;
                a3 = 0.0;
            }
        }
        else if (convention == "zyz")
        {
            if (m_matrix[2][2] < 1)
            {
                if (m_matrix[2][2] > -1)
                {
                    a1 = std::atan2(m_matrix[1][2], m_matrix[0][2]);
                    a2 = std::acos(m_matrix[2][2]);
                    a3 = std::atan2(m_matrix[2][1], -m_matrix[2][0]);
                }
                else // m22 = -1
                {
                    // Not a unique solution: a3 - a1 = atan2(m10, m11)
                    a1 = -std::atan2(m_matrix[1][0], m_matrix[1][1]);
                    a2 = Constants::m_pi;
                    a3 = 0.0;
                }
            }
            else // m22 = +1
            {
                a1 = std::atan2(m_matrix[1][0], m_matrix[1][1]);
                a2 = 0.0;
                a3 = 0.0;
            }
        }
        // ===== END OF EULER ANGLES CONVENTION =====
        if (degrees)
        {
            a1 *= Constants::m_radtodeg;
            a2 *= Constants::m_radtodeg;
            a3 *= Constants::m_radtodeg;
        }
    }
    else
        throw std::invalid_argument("Osl::Geometry::Rotation3D.eulerAngles(): "
                                    "'convention' is not a recognized convention.");
}

} // namespace Osl::Geometry

} // namespace Osl
