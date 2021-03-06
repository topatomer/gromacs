#
# This file is part of the GROMACS molecular simulation package.
#
# Copyright (c) 2018,2019,2020,2021, by the GROMACS development team, led by
# Mark Abraham, David van der Spoel, Berk Hess, and Erik Lindahl,
# and including many others, as listed in the AUTHORS file in the
# top-level source directory and at http://www.gromacs.org.
#
# GROMACS is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public License
# as published by the Free Software Foundation; either version 2.1
# of the License, or (at your option) any later version.
#
# GROMACS is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with GROMACS; if not, see
# http://www.gnu.org/licenses, or write to the Free Software Foundation,
# Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.
#
# If you want to redistribute modifications to GROMACS, please
# consider that scientific software is very special. Version
# control is crucial - bugs must be traceable. We will be happy to
# consider code for inclusion in the official distribution, but
# derived work must not be called official GROMACS. Details are found
# in the README & COPYING files - if they are missing, get the
# official version at http://www.gromacs.org.
#
# To help us fund GROMACS development, we humbly ask that you cite
# the research papers on the package. Check out http://www.gromacs.org.

# The legacy public API headers may still be installed,
# but may be removed or changed without warning.
add_subdirectory(legacy)

# Activate targets for new C++ API components and docs.
if(GMX_NATIVE_WINDOWS)
    # GMXAPI has not been tested in Microsoft environments.
    # GMXAPI requires position-independent code
    set(_GMXAPI_DEFAULT OFF)
else()
    set(_GMXAPI_DEFAULT ON)
endif()
option(GMXAPI "Install GROMACS API." ${_GMXAPI_DEFAULT})
if (GMXAPI)
    add_subdirectory(gmxapi)
endif()

# Activate targets NBLIB
if(GMX_NATIVE_WINDOWS OR NOT BUILD_SHARED_LIBS OR CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    # NBLIB has not been tested in Microsoft environments.
    # NBLIB requires position-independent code
    # NBLIB causes an ICE in icc 19.1.2.20200623
    set(_NBLIB_DEFAULT OFF)
else()
    set(_NBLIB_DEFAULT ON)
endif()
option(GMX_INSTALL_NBLIB_API "Install nblib headers" ${_NBLIB_DEFAULT})
if (GMX_INSTALL_NBLIB_API)
    if(NOT ${BUILD_SHARED_LIBS})
        message(FATAL_ERROR "NBLIB requires position-independent code. Set -DGMX_INSTALL_NBLIB_API=OFF or -DBUILD_SHARED_LIBS=ON.")
    else()
        add_subdirectory(nblib)
    endif()
endif()
