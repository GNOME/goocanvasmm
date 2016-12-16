## Copyright (c) 2009  goocanvasmm Development Team
##
## This file is part of goocanvasmm.
##
## goocanvasmm is free software: you can redistribute it and/or modify it
## under the terms of the GNU Lesser General Public License as published
## by the Free Software Foundation, either version 2.1 of the License,
## or (at your option) any later version.
##
## goocanvasmm is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
## See the GNU Lesser General Public License for more details.
##
## You should have received a copy of the GNU Lesser General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.

AC_INIT([goocanvasmm], [2.99.1], [http://bugzilla.gnome.org/], [goocanvasmm], [http://www.gtkmm.org/])
AC_PREREQ([2.59])

AC_CONFIG_SRCDIR([goocanvas/src/canvas.hg])
AC_CONFIG_AUX_DIR([build])
AC_CONFIG_MACRO_DIR([build])
AC_CONFIG_HEADERS([build/config.h goocanvas/goocanvasmmconfig.h])

AM_INIT_AUTOMAKE([1.9 -Wno-portability check-news dist-bzip2 no-define nostdinc tar-ustar])
AM_MAINTAINER_MODE
AC_ARG_VAR([ACLOCAL_FLAGS], [aclocal flags, e.g. -I <macro dir>])

MM_PREREQ([0.9.5])
MM_INIT_MODULE([goocanvasmm-3.0])

# Copy the mm-common .pl scripts into docs/,
# and use them from there,
# then dist them to avoid a tarball-build dependency.
MM_CONFIG_DOCTOOL_DIR([doc])

# http://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
AC_SUBST([GOOCANVASMM_SO_VERSION], [6:0:0])

AC_PROG_CXX

MM_AX_CXX_COMPILE_STDCXX_11([noext],[mandatory])

AC_DISABLE_STATIC
AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL

AC_SUBST([GOOCANVASMM_MODULES], ['gtkmm-4.0 >= 3.18.0 goocanvas-3.0 >= 2.0.1'])
PKG_CHECK_MODULES([GOOCANVASMM], [$GOOCANVASMM_MODULES])

MM_PKG_CONFIG_SUBST([GTHREAD_CFLAGS], [--cflags-only-other gthread-2.0])
MM_PKG_CONFIG_SUBST([GMMPROC_DIR], [--variable=gmmprocdir glibmm-2.52])
MM_PKG_CONFIG_SUBST([GMMPROC_EXTRA_M4_DIR], [--variable=gmmprocm4dir gtkmm-4.0 pangomm-1.42 atkmm-2.26])

MM_ARG_ENABLE_DOCUMENTATION
MM_ARG_WITH_TAGFILE_DOC([libstdc++.tag], [mm-common-libstdc++])
MM_ARG_WITH_TAGFILE_DOC([libsigc++-2.0.tag], [sigc++-3.0])
MM_ARG_WITH_TAGFILE_DOC([glibmm-2.4.tag], [glibmm-2.52])
MM_ARG_WITH_TAGFILE_DOC([cairomm-1.0.tag], [cairomm-1.16])
MM_ARG_WITH_TAGFILE_DOC([pangomm-1.4.tag], [pangomm-1.42])
MM_ARG_WITH_TAGFILE_DOC([gtkmm-3.0.tag], [gtkmm-4.0])

AC_LANG([C++])
MM_ARG_ENABLE_WARNINGS([GOOCANVASMM_WXXFLAGS],
                       [-Wall],
                       [-pedantic -Wall -Wextra -Wformat-security -Wsuggest-override -Wshadow -Wno-long-long],
                       [G PANGO ATK GDK GDK_PIXBUF GTK SIGC GLIBMM ATKMM PANGOMM CAIROMM GTKMM])

AC_CONFIG_FILES([Makefile
                 codegen/Makefile
                 goocanvas/${GOOCANVASMM_MODULE_NAME}.pc:goocanvas/goocanvasmm.pc.in
                 goocanvas/${GOOCANVASMM_MODULE_NAME}-uninstalled.pc:goocanvas/goocanvasmm-uninstalled.pc.in
                 goocanvas/src/Makefile
                 goocanvas/goocanvasmm/Makefile
                 examples/Makefile
                 tests/Makefile
                 doc/Makefile
                 doc/reference/Doxyfile])
AC_OUTPUT
