pixmap_files	= flower.png toroid.png

EXTRA_DIST = README $(pixmap_files)

noinst_PROGRAMS = canvas_demo

canvas_demo_SOURCES = canvas.cc	\
	primitives.h primitives.cc \
	canvas_features.h canvas_features.cc \
	fifteen.h fifteen.cc \
	arrowhead.h arrowhead.cc \
	richtext.h richtext.cc \
	curve.h curve.cc

#Where to find the header files needed by the source files:
INCLUDES = -I$(top_builddir)/libgnomecanvas -I$(top_srcdir)/libgnomecanvas $(LIBGNOMECANVASMM_CFLAGS)

#The libraries that the executable needs to link against:
LIBS = $(top_builddir)/libgnomecanvas/libgnomecanvasmm/libgnomecanvasmm-2.6.la \
       $(LIBGNOMECANVASMM_LIBS)

