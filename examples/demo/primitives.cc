/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Author:    Paul Davis pjdavis@engineering.uiowa.edu
 * Copyright: University of Iowa 2006
 * FileInfo:  $Id$
 *
 */
#include <iostream>
#include "primitives.h"

Primitives::Primitives()
  : _name("Primitives")
{
  _vbox = Gtk::manage(new Gtk::VBox());

  Gtk::Label* lbl = Gtk::manage(new Gtk::Label("Drag an item with button 1. Click button 2 on an item to lower it, or button 3 to raise it."));
  _vbox->pack_start(*lbl, Gtk::PACK_SHRINK);


//====

  _canvas = Gtk::manage(new Goocanvas::Canvas());
  _setup_divisions();
  _setup_rectangles();
  _setup_ellipses();
  _setup_texts();
  _setup_images();
  _setup_lines();

  _scrolled_window = Gtk::manage(new Gtk::ScrolledWindow());
  _scrolled_window->add(*_canvas);
  _vbox->pack_start(*_scrolled_window, Gtk::PACK_EXPAND_WIDGET);

//====
}

const Glib::ustring&
Primitives::getName()
{
  return _name ;
}

Gtk::Widget*
Primitives::getWidget()
{
  return _vbox ;
}

bool
Primitives::_on_background_button_press(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventButton* ev)
{
  return false;
}

bool
Primitives::_on_button_press(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventButton* ev)
{
  std::cerr << "Clicked!" << std::endl ;
  return false;
}

bool
Primitives::_on_button_release(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventButton* ev)
{
  return false;
}

bool
Primitives::_on_motion_notify(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventMotion* ev)
{
  return false;
}

void
Primitives::_setup_signals(const Glib::RefPtr<Goocanvas::Item>& item)
{
  item->signal_button_press_event().connect(sigc::mem_fun(*this, &Primitives::_on_button_press));
  item->signal_button_release_event().connect(sigc::mem_fun(*this, &Primitives::_on_button_release));
  item->signal_motion_notify_event().connect(sigc::mem_fun(*this, &Primitives::_on_motion_notify));
}

void
Primitives::_setup_heading(const Glib::ustring& heading, int pos)
{
  double x = (pos%3) * 200 + 100 ;
  double y = (pos/3) * 150 + 5 ;

  Glib::RefPtr<Goocanvas::Text> text = Goocanvas::Text::create(heading, x, y, -1, Gtk::ANCHOR_N);
  _canvas->get_root_item()->add_child(text);
#ifdef GLIBMM_PROPERTIES_ENABLED
  text->property_font() = "Sans 12" ;
#else
  text->set_property("font", Glib::ustring("Sans 12"));
#endif

  text->skew_y(30, x, y);
}

void
Primitives::_setup_divisions()
{
  Glib::RefPtr<Goocanvas::Group> group = Goocanvas::Group::create();
  _canvas->get_root_item()->add_child(group);
  group->translate(2, 2);

  Glib::RefPtr<Goocanvas::ItemSimple> item ;

  item = Goocanvas::Rect::create(0, 0, 600, 450);
        group->add_child(item);
#ifdef GLIBMM_PROPERTIES_ENABLED
  item->property_line_width() = 4.0 ;
#else
  item->set_property("line_width", 4.0);
#endif

  item = Goocanvas::Polyline::create(0, 150, 600, 150);
  group->add_child(item);
#ifdef GLIBMM_PROPERTIES_ENABLED
  item->property_line_width() = 4.0 ;
#else
  item->set_property("line_width", 4.0);
#endif

  item = Goocanvas::Polyline::create(0, 300, 600, 300);
  group->add_child(item);
#ifdef GLIBMM_PROPERTIES_ENABLED
  item->property_line_width() = 4.0 ;
#else
  item->set_property("line_width", 4.0);
#endif

  item = Goocanvas::Polyline::create(200, 0, 200, 450);
  group->add_child(item);
#ifdef GLIBMM_PROPERTIES_ENABLED
  item->property_line_width() = 4.0 ;
#else
  item->set_property("line_width", 4.0);
#endif

  item = Goocanvas::Polyline::create(400, 0, 400, 450);
  group->add_child(item);
#ifdef GLIBMM_PROPERTIES_ENABLED
  item->property_line_width() = 4.0 ;
#else
  item->set_property("line_width", 4.0);
#endif

  _setup_heading("Rectangles", 0);
  _setup_heading("Ellipses", 1);
  _setup_heading("Texts", 2);
  _setup_heading("Images", 3);
  _setup_heading("Lines", 4);
  _setup_heading("No Curves", 5);
  _setup_heading("Arcs", 6);
  _setup_heading("Polygons", 7);
  _setup_heading("Widgets", 8);
}

void
Primitives::_setup_rectangles()
{
  Glib::RefPtr<Goocanvas::Rect> rect ;
  Glib::RefPtr<Goocanvas::Item> root = _canvas->get_root_item();

  rect = Goocanvas::Rect::create(20, 30, 50, 30);
  root->add_child(rect);
#ifdef GLIBMM_PROPERTIES_ENABLED
  rect->property_stroke_color() = "red" ;
  rect->property_line_width() = 8.0 ;
#else
  rect->set_property("stroke_color", Glib::ustring("red"));
  rect->set_property("line_width", 8.0);
#endif
  _setup_signals(rect);

  rect = Goocanvas::Rect::create(90, 40, 90, 60);
  root->add_child(rect);
  //rect->property_fill_pattern() = _create_stipple("mediumseagreen");
  Cairo::RefPtr<Cairo::Pattern> p = _create_stipple("mediumseagreen");
  g_object_set(rect->gobj(), "fill-pattern", p->cobj(), NULL);
#ifdef GLIBMM_PROPERTIES_ENABLED
  rect->property_stroke_color() = "black" ;
  rect->property_line_width() = 4.0 ;
#else
  rect->set_property("stroke_color", Glib::ustring("black"));
  rect->set_property("line_width", 4.0);
#endif
  _setup_signals(rect);

  rect = Goocanvas::Rect::create(10, 80, 70, 60);
  root->add_child(rect);
#ifdef GLIBMM_PROPERTIES_ENABLED
  rect->property_fill_color() = "steelblue" ;
#else
  rect->set_property("fill_color", Glib::ustring("steelblue"));
#endif
  _setup_signals(rect);

  rect = Goocanvas::Rect::create(20, 90, 70, 60);
  root->add_child(rect);
#ifdef GLIBMM_PROPERTIES_ENABLED
  rect->property_fill_color_rgba() = 0x3cb37180 ;
  rect->property_stroke_color() = "blue" ;
  rect->property_line_width() = 2.0 ;
#else
  rect->set_property("fill_color_rgba", 0x3cb37180);
  rect->set_property("stroke_color", Glib::ustring("blue"));
  rect->set_property("line_width", 2.0);
#endif
  _setup_signals(rect);

  rect = Goocanvas::Rect::create(110, 80, 50, 30);
  root->add_child(rect);
#ifdef GLIBMM_PROPERTIES_ENABLED
  rect->property_radius_x() = 20.0 ;
  rect->property_radius_y() = 10.0 ;
  rect->property_stroke_color() = "yellow" ;
  rect->property_fill_color_rgba() = 0x3cb3f180 ;
#else
  rect->set_property("radius_x", 20.0);
  rect->set_property("radius_y", 10.0);
  rect->set_property("stroke_color", Glib::ustring("yellow"));
  rect->set_property("fill_color_rgba", 0x3cb3f180);
#endif
  _setup_signals(rect);

  rect = Goocanvas::Rect::create(30, 20, 50, 30);
  root->add_child(rect);
#ifdef GLIBMM_PROPERTIES_ENABLED
  rect->property_fill_color() = "yellow" ;
#else
  rect->set_property("fill_color", Glib::ustring("yellow"));
#endif
  _setup_signals(rect);
}

void
Primitives::_setup_ellipses()
{
  Glib::RefPtr<Goocanvas::Ellipse> ellipse ;
  Glib::RefPtr<Goocanvas::Item> root = _canvas->get_root_item();

  ellipse = Goocanvas::Ellipse::create(245, 45, 25, 15);
  root->add_child(ellipse);
#ifdef GLIBMM_PROPERTIES_ENABLED
  ellipse->property_stroke_color() = "goldenrod" ;
  ellipse->property_line_width() = 8.0 ;
#else
  ellipse->set_property("stroke_color", Glib::ustring("goldenrod"));
  ellipse->set_property("line_width", 8.0);
#endif
  _setup_signals(ellipse);

  ellipse = Goocanvas::Ellipse::create(335, 70, 45, 30);
  root->add_child(ellipse);
#ifdef GLIBMM_PROPERTIES_ENABLED
  ellipse->property_fill_color() = "wheat" ;
  ellipse->property_stroke_color() = "midnightblue" ;
  ellipse->property_line_width() = 4.0 ;
  ellipse->property_title() = "An ellipse" ;
#else
  ellipse->set_property("fill_color", Glib::ustring("wheat"));
  ellipse->set_property("stroke_color", Glib::ustring("midnightblue"));
  ellipse->set_property("line_width", 4.0);
  ellipse->set_property("title", Glib::ustring("An ellipse"));
#endif
  _setup_signals(ellipse);

  ellipse = Goocanvas::Ellipse::create(245, 110, 35, 30);
  root->add_child(ellipse);
  //ellipse->property_fill_pattern() = _create_stipple("cadetblue");
  Cairo::RefPtr<Cairo::Pattern> p = _create_stipple("cadetblue");
  g_object_set(ellipse->gobj(), "fill-pattern", p->cobj(), NULL);

#ifdef GLIBMM_PROPERTIES_ENABLED
  ellipse->property_stroke_color() = "black" ;
  ellipse->property_line_width() = 1.0 ;
#else
  ellipse->set_property("stroke_color", Glib::ustring("black"));
  ellipse->set_property("line_width", 1.0);
#endif
  _setup_signals(ellipse);
}

void
Primitives::_setup_texts()
{
  Glib::RefPtr<Goocanvas::Text> text ;
        Glib::RefPtr<Goocanvas::Item> anchor;

  anchor = _create_anchor(420, 20);
  text = Goocanvas::Text::create("Anchor NW", 0, 0, -1, Gtk::ANCHOR_NW);
  anchor->add_child(text);
  //ellipse->property_fill_pattern() = _create_stipple("blue");
  Cairo::RefPtr<Cairo::Pattern> p = _create_stipple("blue");
  g_object_set(text->gobj(), "fill-pattern", p->cobj(), NULL);
#ifdef GLIBMM_PROPERTIES_ENABLED
  text->property_font() = "Sans Bold 24" ;
  text->property_alignment() = Pango::ALIGN_CENTER ;
  text->property_fill_color() = "firebrick" ;
#else
  text->set_property("font", Glib::ustring("Sans Bold 24"));
  text->set_property("alignment", Pango::ALIGN_CENTER);
  text->set_property("fill_color", Glib::ustring("firebrick"));
#endif
  _setup_signals(text);

  anchor = _create_anchor(470, 75);
  text = Goocanvas::Text::create("Anchor center\nJustify center\nMultiline text\n8bit text 'gibberish'", 0, 0, -1, Gtk::ANCHOR_CENTER);
  anchor->add_child(text);
#ifdef GLIBMM_PROPERTIES_ENABLED
  text->property_font() = "monospace bold 14" ;
  text->property_alignment() = Pango::ALIGN_CENTER ;
  text->property_fill_color() = "firebrick" ;
#else
  text->set_property("font", Glib::ustring("monospace bold 14"));
  text->set_property("alignment", Pango::ALIGN_CENTER);
  text->set_property("fill_color", Glib::ustring("firebrick"));
#endif
  _setup_signals(text);

  anchor = _create_anchor(420, 240);
  text = Goocanvas::Text::create(
    "This is a very long paragraph that will need to be wrapped over several lines so we can see what happens to line-breaking as the view is zoomed in and out.",
    0, 0, 180, Gtk::ANCHOR_W);
  anchor->add_child(text);
#ifdef GLIBMM_PROPERTIES_ENABLED
  text->property_font() = "Sans 12" ;
  text->property_fill_color() = "goldenrod" ;
#else
  text->set_property("font", Glib::ustring("Sans 12"));
  text->set_property("fill_color", Glib::ustring("goldenrod"));
#endif
  _setup_signals(text);

  text = Goocanvas::Text::create("Ellipsized text.", 20, 420, 115, Gtk::ANCHOR_W);
  _canvas->get_root_item()->add_child(text);
#ifdef GLIBMM_PROPERTIES_ENABLED
  text->property_font() = "Sans 12" ;
  text->property_fill_color() = "blue" ;
  text->property_ellipsize() = Pango::ELLIPSIZE_END ;
#else
  text->set_property("font", Glib::ustring("Sans 12"));
  text->set_property("fill_color", Glib::ustring("blue"));
  text->set_property("ellipsize", Pango::ELLIPSIZE_END);
#endif
  _setup_signals(text);
}

void
Primitives::_setup_images()
{
  Glib::RefPtr<Gdk::Pixbuf> pb;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
  {
    pb = Gdk::Pixbuf::create_from_file("toroid.png");
  }
  catch(...)
  {
    g_warning("Couldn't find the toroid.png sample file.");
  }
#else
  std::auto_ptr<Glib::Error> error;
  pb = Gdk::Pixbuf::create_from_file("toroid.png", error);
  if(error.get())
  {
    g_warning("Couldn't find the toroid.png sample file.");
  }
#endif

  double w = pb->get_width();
  double h = pb->get_height();

  Glib::RefPtr<Goocanvas::Image> img = Goocanvas::Image::create(pb, 100.0 - w / 2.0, 225.0 - h / 2.0);
  _canvas->get_root_item()->add_child(img);
#ifdef GLIBMM_PROPERTIES_ENABLED
  img->property_width() = w ;
  img->property_height() = h ;
#else
  img->set_property("width", w);
  img->set_property("height", h);
#endif
  _setup_signals(img);

  _create_flower(20.0, 170.0, Gtk::ANCHOR_NW);
  _create_flower(180.0, 170.0, Gtk::ANCHOR_NE);
  _create_flower(20.0, 280.0, Gtk::ANCHOR_SW);
  _create_flower(180.0, 280.0, Gtk::ANCHOR_SE);
}

void
Primitives::_setup_lines()
{
  _create_polish_diamond();
  _create_hilbert();

  Glib::RefPtr<Goocanvas::Polyline> line ;
  Glib::RefPtr<Goocanvas::Item> root = _canvas->get_root_item();

/*
  Glib::RefPtr<Goocanvas::Points> points = Goocanvas::Points::create(4);
  points->set_coordinate(0, 340, 170);
  points->set_coordinate(1, 340, 230);
  points->set_coordinate(2, 390, 230);
  points->set_coordinate(3, 390, 170);
  line = Goocanvas::Polyline::create(false, points); 
        root->add_child(line);
*/

  line = Goocanvas::Polyline::create(356, 180, 374, 220);
        root->add_child(line);
#ifdef GLIBMM_PROPERTIES_ENABLED
  line->property_stroke_color() = "blue" ;
  line->property_line_width() = 1.0 ;
  line->property_start_arrow() = true ;
  line->property_end_arrow() = true ;
  line->property_arrow_tip_length() = 5.0 ;
  line->property_arrow_length() = 6.0 ;
  line->property_arrow_width() = 6.0 ;
#else
  line->set_property("stroke_color", Glib::ustring("blue"));
  line->set_property("line_width", 1.0);
  line->set_property("start_arrow", true);
  line->set_property("end_arrow", true);
  line->set_property("arrow_tip_length", 5.0);
  line->set_property("arrow_length", 6.0);
  line->set_property("arrow_width", 6.0);
#endif
  _setup_signals(line);

  line = Goocanvas::Polyline::create(356, 220, 374, 180);
        root->add_child(line);
#ifdef GLIBMM_PROPERTIES_ENABLED
  line->property_stroke_color() = "blue" ;
  line->property_line_width() = 1.0 ;
  line->property_start_arrow() = true ;
  line->property_end_arrow() = true ;
  line->property_arrow_tip_length() = 5.0 ;
  line->property_arrow_length() = 6.0 ;
  line->property_arrow_width() = 6.0 ;
#else
  line->set_property("stroke_color", Glib::ustring("blue"));
  line->set_property("line_width", 1.0);
  line->set_property("start_arrow", true);
  line->set_property("end_arrow", true);
  line->set_property("arrow_tip_length", 5.0);
  line->set_property("arrow_length", 6.0);
  line->set_property("arrow_width", 6.0);
#endif
  _setup_signals(line);
}

Cairo::RefPtr<Cairo::Pattern>
Primitives::_create_stipple(const Glib::ustring& color)
{
  unsigned char data[16] = {
      0, 0, 0, 255,
      0, 0, 0, 0,
      0, 0, 0, 0,
      0, 0, 0, 255
    };

  Gdk::Color c(color);
  data[2] = data[14] = c.get_red() << 8 ;
  data[1] = data[13] = c.get_green() << 8 ;
  data[0] = data[12] = c.get_blue() << 8 ;

  Cairo::RefPtr<Cairo::ImageSurface> surface = Cairo::ImageSurface::create(data, Cairo::FORMAT_ARGB32, 2, 2, 8);
  Cairo::RefPtr<Cairo::SurfacePattern> pattern = Cairo::SurfacePattern::create(surface);
  pattern->set_extend(Cairo::EXTEND_REPEAT);
  return pattern ;
}

Glib::RefPtr<Goocanvas::Item>
Primitives::_create_anchor(double x, double y)
{
  cairo_matrix_t m = { 0.8, 0.2, -0.3, 0.5, x, y };

  Glib::RefPtr<Goocanvas::Group> group = Goocanvas::Group::create();
  _canvas->get_root_item()->add_child(group);
  group->translate(x, y);
  //group->property_transform() = &m ;
  g_object_set(group->gobj(), "transform", &m, NULL);

  Glib::RefPtr<Goocanvas::Rect> rect = Goocanvas::Rect::create(-2.5, -2.5, 4, 4);
  group->add_child(rect);
#ifdef GLIBMM_PROPERTIES_ENABLED
  rect->property_line_width() = 1.0 ;
#else
  rect->set_property("line_width", 1.0);
#endif

  _setup_signals(group);

  return group ;
}

void
Primitives::_create_flower(double x, double y, Gtk::AnchorType anchor)
{
  Cairo::RefPtr<Cairo::ImageSurface> surface ;

  try
  {
    surface = Cairo::ImageSurface::create_from_png("flower.png");
  }

  catch(...)
  {
    g_warning("Couldn't find flower.png sample image.");
    return ;
  }

  double w = surface->get_width();
  double h = surface->get_height();

  Cairo::RefPtr<Cairo::SurfacePattern> pattern = Cairo::SurfacePattern::create(surface);

  Glib::RefPtr<Goocanvas::Image> img = Goocanvas::Image::create(x, y);
   _canvas->get_root_item()->add_child(img);
  //TODO: img->property_pattern() = pattern ;
  g_object_set(img->gobj(), "pattern", pattern->cobj(), NULL);
#ifdef GLIBMM_PROPERTIES_ENABLED
  img->property_width() = w ;
  img->property_height() = h ;
#else
  img->set_property("width", w);
  img->set_property("height", h);
#endif
  _setup_signals(img);
}

void
Primitives::_create_polish_diamond()
{
  Glib::RefPtr<Goocanvas::Group> group = Goocanvas::Group::create();
  _canvas->get_root_item()->add_child(group); 
  group->translate(270, 230);

  Glib::RefPtr<Goocanvas::Polyline> line ;

  double vertices = 10.0 ;
  double radius = 60.0 ;

  for(int i = 0 ; i < vertices ; i++)
  {
    double a = 2.0 * M_PI * i / vertices ;
    double x1 = radius * cos(a);
    double y1 = radius * sin(a);

    for(int j = i + 1 ; j < vertices ; j++)
    {
      a = 2.0 * M_PI * j / vertices ;
      double x2 = radius * cos(a);
      double y2 = radius * sin(a);

      line = Goocanvas::Polyline::create(x1, y1, x2, y2);
      group->add_child(line);
    }
  }

  _setup_signals(group);
}

void
Primitives::_create_hilbert()
{
  
}
