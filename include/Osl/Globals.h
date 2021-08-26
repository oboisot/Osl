/*! ********************************************************************
 * \file Globals.h
 * \brief Header file for global typedefs definition.
 *********************************************************************/

#ifndef OSL_GLOBALS_H
#define OSL_GLOBALS_H

#include <cmath>
#include <complex>
#include <vector>
#include <stdexcept>

namespace Osl {
/*! ********************************************************************
 * \brief Defines complex numbers.
 *********************************************************************/
typedef std::complex<double> complex ;

/*! ********************************************************************
 * \brief Defines \em vector containers for real numbers.
 *********************************************************************/
typedef std::vector<double> vector;

/*! ********************************************************************
 * \brief Defines \em vector containers for complex numbers.
 *********************************************************************/
typedef std::vector<complex> cvector;

/*! ********************************************************************
 * \brief Defines \em matrix containers (2d vector) for real numbers.
 *********************************************************************/
typedef std::vector<vector> matrix;

/*! ********************************************************************
 * \brief Defines \em matrix containers (2d vector) for complex numbers.
 *********************************************************************/
typedef std::vector<cvector> cmatrix ;

} // namespace Osl

#endif // OSL_GLOBALS_H
