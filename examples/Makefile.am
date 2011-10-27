include $(top_srcdir)/examples/Makefile.am_fragment

AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = -I$(top_builddir) $(GOOCANVASMM_CFLAGS)
AM_CXXFLAGS = $(GOOCANVASMM_WXXFLAGS)
LDADD       = $(GOOCANVASMM_LIBS)

check_PROGRAMS = \
	coordinates/example \
	custom_item/example \
	demo/example \
	drag_to_canvas/example \
	simple/example \
	moving_shapes/example	\
	table/example \
	tablemodel/example \
	text/example

coordinates_example_SOURCES = \
  coordinates/main.cc \
  coordinates/window.cc \
  coordinates/window.h
  
custom_item_example_SOURCES = \
  custom_item/main.cc \
  custom_item/exampleitem.cc \
  custom_item/exampleitem.h \
  custom_item/examplewindow.cc \
  custom_item/examplewindow.h
  
demo_example_SOURCES = \
  demo/main.cc \
  demo/page.h \
  demo/primitives.h \
  demo/primitives.cc \
  demo/window.cc \
  demo/window.h
  
drag_to_canvas_example_SOURCES = \
  drag_to_canvas/main.cc \
  drag_to_canvas/examplewindow.cc \
  drag_to_canvas/examplewindow.h

simple_example_SOURCES = \
  simple/main.cc \
  simple/examplewindow.cc \
  simple/examplewindow.h

moving_shapes_example_SOURCES = \
  moving_shapes/main.cc \
  moving_shapes/window.cc \
  moving_shapes/window.h

table_example_SOURCES = \
  table/main.cc \
  table/examplewindow.cc \
  table/examplewindow.h
  
tablemodel_example_SOURCES = \
  tablemodel/main.cc \
  tablemodel/examplewindow.cc \
  tablemodel/examplewindow.h
  
text_example_SOURCES = \
  text/main.cc \
  text/window.cc \
  text/window.h
  
dist_noinst_DATA = \
	demo/demo.glade \
	demo/flower.png \
	demo/toroid.png
