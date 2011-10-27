include $(top_srcdir)/examples/Makefile.am_fragment

AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = -I$(top_builddir) $(GOOCANVASMM_CFLAGS)
AM_CXXFLAGS = $(GOOCANVASMM_WXXFLAGS)
LDADD       = $(GOOCANVASMM_LIBS)

check_PROGRAMS = \
	child_properties/test

child_properties_test_SOURCES = \
  child_properties/main.cc
  
