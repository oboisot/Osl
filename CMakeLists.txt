cmake_minimum_required(VERSION 3.14)

#################
# PROJECT INFOS #
#################
project(Osl LANGUAGES CXX
            VERSION 0.1)

################
# C++ STANDARD #
################
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


######################
# CONFIGURATION FILE #
######################
configure_file(OslConfig.h.in OslConfig.h)

####################
# OPTIONAL COMMAND #
####################
# Definition of variables
set(INCLUDE_ENDIAN OFF) # "Include Endian module"
#option(INCLUDE_ENDIAN "Include Endian module" OFF)
set(BUILD_SHARED_LIBS ON) # Option to build .so
#option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
set(MAKE_EXE ON)
#option(MAKE_EXE "Create an executable" ON)
option(USE_OpenMP "Use OpenMP" ON)

###################
# SETTING HEADERS #
###################
set(OSL_HEADERS include/Osl/Osl.h
                include/Osl/Constants.h
                include/Osl/Globals.h
                # OSl::Geography
                include/Osl/Geography/Geography.h
                include/Osl/Geography/Ellipsoid.h
                include/Osl/Geography/GeoPoint.h
                include/Osl/Geography/LocalCartesian.h
                include/Osl/Geography/dms_to_dd.h
                include/Osl/Geography/dd_to_dms.h
                # OSl::Geometry
                include/Osl/Geometry/Geometry.h
                include/Osl/Geometry/vector3.h
                include/Osl/Geometry/Vector3D.h
                include/Osl/Geometry/rotmatrix3.h
                include/Osl/Geometry/Rotation3D.h
                # OSl::Geometry::Interpolator3D
                include/Osl/Geometry/Interpolator3D/Interpolator3D.h
                include/Osl/Geometry/Interpolator3D/LinearSpline3D.h
                include/Osl/Geometry/Interpolator3D/CubicSpline3D.h
                # OSl::Geometry::Shape
                include/Osl/Geometry/Shape3D/Shape3D.h
                include/Osl/Geometry/Shape3D/Line3D.h
                include/Osl/Geometry/Shape3D/Plane3D.h
                include/Osl/Geometry/Shape3D/Cone3D.h
                include/Osl/Geometry/Shape3D/Sphere3D.h
                include/Osl/Geometry/Shape3D/Ellipsoid3D.h
                # Osl::Maths
                include/Osl/Maths/Maths.h
                # Osl::Maths::Interpolator
                include/Osl/Maths/Interpolator/Interpolator.h
                include/Osl/Maths/Interpolator/InterpolatorEnum.h
                include/Osl/Maths/Interpolator/LinearSpline.h
                include/Osl/Maths/Interpolator/QuadraticSpline.h
                include/Osl/Maths/Interpolator/CubicSpline.h
                include/Osl/Maths/Interpolator/ComplexLinearSpline.h
                include/Osl/Maths/Interpolator/ComplexQuadraticSpline.h
                include/Osl/Maths/Interpolator/ComplexCubicSpline.h
                include/Osl/Maths/Interpolator/Sinc.h
                # Osl::Maths::Comparison
                include/Osl/Maths/Comparison/Comparison.h
                include/Osl/Maths/Comparison/almost_equal.h
                include/Osl/Maths/Comparison/almost_zero.h
                include/Osl/Maths/Comparison/almost_one.h
                include/Osl/Maths/Comparison/true_zero.h
                # Osl::Maths::Arrays
                include/Osl/Maths/Arrays/Arrays.h
                include/Osl/Maths/Arrays/linspace.h
                include/Osl/Maths/Arrays/logspace.h
                include/Osl/Maths/Arrays/regspace.h
                # Osl::Maths::Functions
                include/Osl/Maths/Functions/sinc.h
                # Osl::Maths::Roots
                include/Osl/Maths/Roots/Roots.h
                include/Osl/Maths/Roots/linear_root.h
                include/Osl/Maths/Roots/quadratic_roots.h
                include/Osl/Maths/Roots/cubic_roots.h
                include/Osl/Maths/Roots/quartic_roots.h)

if(INCLUDE_ENDIAN)
    list(APPEND OSL_HEADERS include/Osl/Endian/Endian.h
                            include/Osl/Endian/Endianness.h
                            include/Osl/Endian/SwapEndian.h)
endif()

###################
# SETTING SOURCES #
###################
set(OSL_SOURCES # Geography
                include/Osl/Geography/Ellipsoid.cpp
                include/Osl/Geography/GeoPoint.cpp
                include/Osl/Geography/LocalCartesian.cpp
                # Geometry
                include/Osl/Geometry/vector3.cpp
                include/Osl/Geometry/Vector3D.cpp
                include/Osl/Geometry/rotmatrix3.cpp
                include/Osl/Geometry/Rotation3D.cpp
                include/Osl/Geometry/Interpolator3D/LinearSpline3D.cpp
                include/Osl/Geometry/Interpolator3D/CubicSpline3D.cpp
                include/Osl/Geometry/Shape3D/Line3D.cpp
                include/Osl/Geometry/Shape3D/Plane3D.cpp
                include/Osl/Geometry/Shape3D/Cone3D.cpp
                include/Osl/Geometry/Shape3D/Sphere3D.cpp
                include/Osl/Geometry/Shape3D/Ellipsoid3D.cpp
                # Maths
                include/Osl/Maths/Interpolator/LinearSpline.cpp
                include/Osl/Maths/Interpolator/QuadraticSpline.cpp
                include/Osl/Maths/Interpolator/CubicSpline.cpp
                include/Osl/Maths/Interpolator/ComplexLinearSpline.cpp
                include/Osl/Maths/Interpolator/ComplexQuadraticSpline.cpp
                include/Osl/Maths/Interpolator/ComplexCubicSpline.cpp
                include/Osl/Maths/Interpolator/Sinc.cpp)

###################
# SETTING LIB/EXE #
###################
if (MAKE_EXE)
    add_executable(${PROJECT_NAME} ${OSL_HEADERS} ${OSL_SOURCES} include/Osl/OslExe.cpp) # Build an executable 'Osl'
else()
    add_library(${PROJECT_NAME} ${OSL_HEADERS} ${OSL_SOURCES} include/Osl/OslLib.cpp) # Build a library
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX # Needed for header files only
                                                 VERSION ${PROJECT_VERSION})

#########################################
# ADDING SUB-DIRECTORIES TO THE PROJECT #
#########################################
# Osl
target_include_directories(${PROJECT_NAME} PUBLIC include
                                                  include/Osl)
# Geography
target_include_directories(${PROJECT_NAME} PUBLIC include/Osl/Geography)
# Geometry
target_include_directories(${PROJECT_NAME} PUBLIC include/Osl/Geometry
                                                  include/Osl/Geometry/Interpolator
                                                  include/Osl/Geometry/Shape)
# Maths
target_include_directories(${PROJECT_NAME} PUBLIC include/Osl/Maths
                                                  include/Osl/Maths/Interpolator)

#####################
# COMPILATION FLAGS #
#####################
# OpenMP
if(USE_OpenMP)
  find_package(OpenMP)
  if(OpenMP_FOUND)
      set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#      target_include_directories(${PROJECT_NAME} PUBLIC ${OpenMP_C_INCLUDE_DIRS})
#      target_include_directories(${PROJECT_NAME} PUBLIC ${OpenMP_CXX_INCLUDE_DIRS})
#      include_directories(${OpenMP_C_INCLUDE_DIRS})
#      include_directories(${OpenMP_CXX_INCLUDE_DIRS})
  endif()
endif()
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")

#add_compile_options(-Wall -Wextra -pedantic -Werror)

#message("CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_CXX_FLAGS_DEBUG}")
#message("CMAKE_CXX_FLAGS_RELEASE is ${CMAKE_CXX_FLAGS_RELEASE}")
#message("CMAKE_CXX_FLAGS_RELWITHDEBINFO is ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
#message("CMAKE_CXX_FLAGS_MINSIZEREL is ${CMAKE_CXX_FLAGS_MINSIZEREL}")

################
# INSTALLATION #
################
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/${PROJECT_NAME}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/static/${PROJECT_NAME})
install(FILES OslConfig.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
install(FILES ${OSL_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
