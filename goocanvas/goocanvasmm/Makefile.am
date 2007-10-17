## Copyright (c) 2001
## The goocanvasmm development team.

SUBDIRS			= private

sublib_name		= goocanvasmm
sublib_libname = goocanvasmm-0.1
sublib_libversion = $(LIBGOOCANVASMM_SO_VERSION)
sublib_namespace	= Goocanvas
sublib_cflags		= $(LIBGOOCANVASMM_CFLAGS)
sublib_topdir = goocanvas


files_extra_h	= init.h wrap_init.h types.h 
files_extra_cc	= init.cc

include $(top_srcdir)/build_shared/Makefile_build_gensrc.am_fragment

lib_LTLIBRARIES			= libgoocanvasmm-0.1.la
libgoocanvasmm_0_1_la_SOURCES	= $(files_all_cc)
libgoocanvasmm_0_1_la_LDFLAGS	= $(common_ldflags)
libgoocanvasmm_0_1_la_LIBADD	= $(LIBGOOCANVASMM_LIBS)

