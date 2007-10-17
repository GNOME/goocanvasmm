## Copyright (c) 2001
## The libgnomecanvasmm development team.

SUBDIRS			= private

sublib_name		= libgnomecanvasmm
sublib_libname = libgnomecanvasmm-2.6
sublib_libversion = $(LIBGNOMECANVASMM_SO_VERSION)
sublib_namespace	= Canvas
sublib_cflags		= $(LIBGNOMECANVASMM_CFLAGS)
sublib_topdir = libgnomecanvas

files_extra_h		= affinetrans.h properties.h init.h point.h
files_extra_cc		= affinetrans.cc properties.cc init.cc point.cc

include $(top_srcdir)/build_shared/Makefile_build_gensrc.am_fragment

lib_LTLIBRARIES			= libgnomecanvasmm-2.6.la
libgnomecanvasmm_2_6_la_SOURCES	= $(files_all_cc)
libgnomecanvasmm_2_6_la_LDFLAGS	= $(common_ldflags)
libgnomecanvasmm_2_6_la_LIBADD	= $(LIBGNOMECANVASMM_LIBS)

