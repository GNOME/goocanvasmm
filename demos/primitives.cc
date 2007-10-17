/* primitives.cc
 *
 * Copyright (C) 2002 The libgnomecanvasmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "primitives.h"

#include <cmath>

#include <libgnomecanvasmm/group.h>
#include <libgnomecanvasmm/rect.h>
#include <libgnomecanvasmm/ellipse.h>
#include <libgnomecanvasmm/line.h>
#include <libgnomecanvasmm/text.h>
#include <libgnomecanvasmm/polygon.h>
#include <libgnomecanvasmm/widget.h>
#include <libgnomecanvasmm/pixbuf.h>
#include <libgnomecanvasmm/bpath.h>
#include <libgnomecanvasmm/path-def.h>
#include <libgnomecanvasmm/properties.h>

Primitives::Primitives(bool aa)
: Gtk::VBox(false, 4)
{
  set_border_width(4);
  
  Gtk::Label* label 
      = Gtk::manage(new Gtk::Label("Drag an item with button 1.  Click button 2 on an item to lower it,\n"
                              "or button 3 to raise it.  Shift+click with buttons 2 or 3 to send\n"
                              "an item to the bottom or top, respectively."));
  pack_start(*label, Gtk::PACK_SHRINK);
  
  Gtk::HBox* hbox = Gtk::manage(new Gtk::HBox(false, 4));
  pack_start(*hbox, Gtk::PACK_SHRINK);
  
  hbox->pack_start(*Gtk::manage(new Gtk::Label("Zoom:")), Gtk::PACK_SHRINK);
  
  Gtk::Adjustment* spin_adj 
      = Gtk::manage(new Gtk::Adjustment(1.00, 0.05, 5.00, 0.05, 0.50, 0.50));
  Gtk::SpinButton* spin = Gtk::manage(new Gtk::SpinButton(*spin_adj, 1.0, 2));
  hbox->pack_start(*spin, Gtk::PACK_SHRINK);
  
  Gtk::Table* table = Gtk::manage(new Gtk::Table(2, 2, false));
  pack_start(*table);
  table->set_row_spacings(4);
  table->set_col_spacings(4);
  
  Gtk::Frame* frame = Gtk::manage(new Gtk::Frame());
  frame->set_shadow_type(Gtk::SHADOW_IN);
  table->attach(*frame, 0, 1, 0, 1, 
                Gtk::AttachOptions(Gtk::EXPAND | Gtk::FILL | Gtk::PACK_SHRINK),
                Gtk::AttachOptions(Gtk::EXPAND | Gtk::FILL | Gtk::PACK_SHRINK));
  
  Gnome::Canvas::Canvas* canvas;
  if(aa == true) {
      canvas = Gtk::manage(new Gnome::Canvas::CanvasAA());
  } else {
      canvas = Gtk::manage(new Gnome::Canvas::Canvas());
  }
  canvas->set_flags(Gtk::CAN_FOCUS);
  canvas->grab_focus();
  frame->add(*canvas);
  canvas->set_size_request(600, 450);
  canvas->set_scroll_region(0, 0, 600, 450);
  canvas->set_center_scroll_region(false);
  canvas->signal_key_press_event()
      .connect(sigc::bind(sigc::mem_fun(*this, &Primitives::on_key_press), canvas));

  Gtk::HScrollbar* hscroll
      = Gtk::manage(new Gtk::HScrollbar(*canvas->get_hadjustment()));
  table->attach(*hscroll, 0, 1, 1, 2,
                Gtk::AttachOptions(Gtk::EXPAND | Gtk::FILL | Gtk::PACK_SHRINK),
                Gtk::AttachOptions(Gtk::FILL));

  Gtk::VScrollbar* vscroll
      = Gtk::manage(new Gtk::VScrollbar(*canvas->get_vadjustment()));
  table->attach(*vscroll, 1, 2, 0, 1,
                Gtk::AttachOptions(Gtk::FILL),
                Gtk::AttachOptions(Gtk::EXPAND | Gtk::FILL | Gtk::PACK_SHRINK));

  spin_adj->signal_value_changed()
      .connect(sigc::bind(sigc::mem_fun(*this, &Primitives::on_zoom_changed),
                    canvas,
                    spin_adj));

  setup_divisions(*canvas->root());
  setup_rectangles(*canvas->root());
  setup_ellipses(*canvas->root());
  setup_images(*canvas->root());
  setup_texts(*canvas->root());
  setup_lines(*canvas->root());
  setup_polygons(*canvas->root());
  setup_curves(*canvas->root());
  setup_widgets(*canvas->root());
}


Primitives::~Primitives()
{
}


void
Primitives::on_zoom_changed(Gnome::Canvas::Canvas* canvas,
                            Gtk::Adjustment* adj)
{
  canvas->set_pixels_per_unit(adj->get_value());
}


bool
Primitives::on_key_press(GdkEventKey *event, Gnome::Canvas::Canvas* canvas)
{
  int x, y;
  canvas->get_scroll_offsets(x, y);

  if(event->keyval == GDK_Up) {
      canvas->scroll_to(x, y - 20);
  } else if(event->keyval == GDK_Down) {
      canvas->scroll_to(x, y + 20);
  } else if(event->keyval == GDK_Left) {
      canvas->scroll_to(x - 10, y);
  } else if(event->keyval == GDK_Right) {
      canvas->scroll_to(x + 10, y);
  } else {
      return false;
  }

  return true;
}


bool
Primitives::on_item_event(GdkEvent* event, Gnome::Canvas::Item* item)
{
  static double x, y;
  double item_x, item_y;
  static bool dragging;

  item_x = event->button.x;
  item_y = event->button.y;

  item->get_parent_group()->w2i(item_x, item_y);

  switch(event->type) {
  case GDK_BUTTON_PRESS:
    switch(event->button.button) {
    case 1:
      if(event->button.state & GDK_SHIFT_MASK) {
        delete item;
      }  else {
        x = item_x;
        y = item_y;

        item->grab(GDK_POINTER_MOTION_MASK | GDK_BUTTON_RELEASE_MASK,
                   Gdk::Cursor(Gdk::FLEUR),
                   event->button.time);
        dragging = true;
      }
      break;

    case 2:
      if(event->button.state & GDK_SHIFT_MASK) {
        item->lower_to_bottom();
      } else {
        item->lower(1);
      }
      break;

    case 3:
      if(event->button.state & GDK_SHIFT_MASK) {
        item->raise_to_top();
      } else {
        item->raise(1);
      }
      break;

    default:
      break;
    }

    break;

  case GDK_MOTION_NOTIFY:
    if(dragging &&(event->motion.state & GDK_BUTTON1_MASK)) {
      double new_x = item_x;
      double new_y = item_y;

      item->move(new_x - x, new_y - y);
      x = new_x;
      y = new_y;
    }
    break;

  case GDK_BUTTON_RELEASE:
    item->ungrab(event->button.time);
    dragging = false;
    break;

  default:
     break;
  }

  return false;
}


void
Primitives::setup_heading(Gnome::Canvas::Group& root,
                          const Glib::ustring& heading,
                          int pos)
{
  Gnome::Canvas::Text* text = Gtk::manage(new Gnome::Canvas::Text(root));
  text->property_text() = heading;
  text->property_x() =(double)((pos % 3) * 200 + 100);
  text->property_y() =(double)((pos / 3) * 150 + 5);
  text->property_font() = "Sans 12";
  text->property_anchor() = Gtk::ANCHOR_N;
  text->property_fill_color() = "black";
}


void
Primitives::setup_divisions(Gnome::Canvas::Group& root)
{
  Gnome::Canvas::Group* group = Gtk::manage(new Gnome::Canvas::Group(root));
  group->property_x() = 0.0;
  group->property_y() = 0.0;
  group->signal_event()
      .connect(sigc::bind(sigc::mem_fun(*this, &Primitives::on_item_event), group));

  Gnome::Canvas::Rect* rect = Gtk::manage(new Gnome::Canvas::Rect(*group));
  rect->property_x1() = 0.0;
  rect->property_y1() = 0.0;
  rect->property_x2() = 600.0;
  rect->property_y2() = 450.0;
  rect->property_outline_color() = "black";
  rect->property_width_units() = 4.0;

  Gnome::Canvas::Points points(2);

  points[0] = Gnome::Art::Point(0.0, 150.0);
  points[1] = Gnome::Art::Point(600.0, 150.0);
  Gnome::Canvas::Line* line = Gtk::manage(new Gnome::Canvas::Line(*group));
  line->property_points().set_value(points);
  line->property_fill_color() = "black";
  line->property_width_units() = 4.0;

  points[0] = Gnome::Art::Point(0.0, 300.0);
  points[1] = Gnome::Art::Point(600.0, 300.0);
  line = Gtk::manage(new Gnome::Canvas::Line(*group));
  line->property_points().set_value(points);
  line->property_fill_color() = "black";
  line->property_width_units() = 4.0;

  points[0] = Gnome::Art::Point(200.0, 0.0);
  points[1] = Gnome::Art::Point(200.0, 450.0);
  line = Gtk::manage(new Gnome::Canvas::Line(*group));
  line->property_points().set_value(points);
  line->property_fill_color() = "black";
  line->property_width_units() = 4.0;

  points[0] = Gnome::Art::Point(400.0, 0.0);
  points[1] = Gnome::Art::Point(400.0, 450.0);
  line = Gtk::manage(new Gnome::Canvas::Line(*group));
  line->property_points().set_value(points);
  line->property_fill_color() = "black";
  line->property_width_units() = 4.0;

  setup_heading(*group, "Rectangles", 0);
  setup_heading(*group, "Ellipses", 1);
  setup_heading(*group, "Texts", 2);
  setup_heading(*group, "Images", 3);
  setup_heading(*group, "Lines", 4);
  setup_heading(*group, "Curves", 5);
  setup_heading(*group, "Arcs", 6);
  setup_heading(*group, "Polygons", 7);
  setup_heading(*group, "Widges", 8);
}

#define gray50_width 2
#define gray50_height 2
static char gray50_bits[] = { 0x02, 0x01 };

void
Primitives::setup_rectangles(Gnome::Canvas::Group& root)
{
  Gnome::Canvas::Rect* rect = Gtk::manage(new Gnome::Canvas::Rect(root));
  rect->property_x1() = 20.0;
  rect->property_y1() = 30.0;
  rect->property_x2() = 70.0;
  rect->property_y2() = 70.0;
  rect->property_outline_color() = "red";
  rect->property_width_pixels() = 8;
  rect->signal_event()
      .connect(sigc::bind(sigc::mem_fun(*this, &Primitives::on_item_event), rect));

  if(root.get_canvas()->property_aa() == true) {
    rect = Gtk::manage(new Gnome::Canvas::Rect(root));
    rect->property_x1() = 90.0;
    rect->property_y1() = 40.0;
    rect->property_x2() = 180.0;
    rect->property_y2() = 100.0;
    rect->property_fill_color_rgba() = 0x3cb37180;
    rect->property_outline_color() = "black";
    rect->property_width_units() = 4.0;
    rect->signal_event()
        .connect(sigc::bind(sigc::mem_fun(*this, &Primitives::on_item_event), rect));
  } else {
    rect = Gtk::manage(new Gnome::Canvas::Rect(root));
    rect->property_x1() = 90.0;
    rect->property_y1() = 40.0;
    rect->property_x2() = 180.0;
    rect->property_y2() = 100.0;
    rect->property_fill_color() = "mediumseagreen";
    rect->property_fill_stipple()
        .set_value(Gdk::Bitmap::create(gray50_bits,
                                       gray50_width,
                                       gray50_height));
    rect->property_outline_color() = "black";
    rect->property_width_units() = 4.0;
    rect->signal_event()
        .connect(sigc::bind(sigc::mem_fun(*this, &Primitives::on_item_event), rect));
  }

  rect = Gtk::manage(new Gnome::Canvas::Rect(root));
  rect->property_x1() = 10.0;
  rect->property_y1() = 80.0;
  rect->property_x2() = 80.0;
  rect->property_y2() = 140.0;
  rect->property_fill_color() = "steelblue";
  rect->signal_event()
      .connect(sigc::bind(sigc::mem_fun(*this, &Primitives::on_item_event), rect));
}


void
Primitives::setup_ellipses(Gnome::Canvas::Group& root)
{
  Gnome::Canvas::Ellipse* ellipse
      = Gtk::manage(new Gnome::Canvas::Ellipse(root));
  ellipse->property_x1() = 220.0;
  ellipse->property_y1() = 30.0;
  ellipse->property_x2() = 270.0;
  ellipse->property_y2() = 60.0;
  ellipse->property_outline_color() = "goldenrod";
  ellipse->property_width_pixels() = 8;
  ellipse->signal_event()
      .connect(sigc::bind(sigc::mem_fun(*this, &Primitives::on_item_event), ellipse));

  ellipse = Gtk::manage(new Gnome::Canvas::Ellipse(root));
  ellipse->property_x1() = 290.0;
  ellipse->property_y1() = 40.0;
  ellipse->property_x2() = 380.0;
  ellipse->property_y2() = 100.0;
  ellipse->property_fill_color() = "wheat";
  ellipse->property_outline_color() = "midnightblue";
  ellipse->property_width_units() = 4.0;
  ellipse->signal_event()
      .connect(sigc::bind(sigc::mem_fun(*this, &Primitives::on_item_event), ellipse));

  if(root.get_canvas()->property_aa() == true) {
    ellipse = Gtk::manage(new Gnome::Canvas::Ellipse(root));
    ellipse->property_x1() = 210.0;
    ellipse->property_y1() = 80.0;
    ellipse->property_x2() = 280.0;
    ellipse->property_y2() = 140.0;
    ellipse->property_fill_color_rgba() = 0x5f9ea080;
    ellipse->property_outline_color() = "black";
    ellipse->property_width_pixels() = 0;
    ellipse->signal_event()
        .connect(sigc::bind(sigc::mem_fun(*this, &Primitives::on_item_event), ellipse));
  } else {
    ellipse = Gtk::manage(new Gnome::Canvas::Ellipse(root));
    ellipse->property_x1() = 210.0;
    ellipse->property_y1() = 80.0;
    ellipse->property_x2() = 280.0;
    ellipse->property_y2() = 140.0;
    ellipse->property_fill_color() = "cadetblue";
    ellipse->property_fill_stipple()
        .set_value(Gdk::Bitmap::create(gray50_bits,
                                       gray50_width,
                                       gray50_height));
    ellipse->property_outline_color() = "black";
    ellipse->property_width_pixels() = 0;
    ellipse->signal_event()
        .connect(sigc::bind(sigc::mem_fun(*this, &Primitives::on_item_event), ellipse));
  }
}


Gnome::Canvas::Group*
Primitives::make_anchor(Gnome::Canvas::Group& root, double x, double y)
{
  Gnome::Canvas::Group* group = Gtk::manage(new Gnome::Canvas::Group(root));
  group->property_x() = x;
  group->property_y() = y;
  group->signal_event()
      .connect(sigc::bind(sigc::mem_fun(*this, &Primitives::on_item_event), group));

  Gnome::Canvas::Rect* rect = Gtk::manage(new Gnome::Canvas::Rect(*group));
  rect->property_x1() = -2.0;
  rect->property_y1() = -2.0;
  rect->property_x2() = 2.0;
  rect->property_y2() = 2.0;
  rect->property_outline_color() = "black";
  rect->property_width_pixels() = 0;

  return group;
}


void
Primitives::setup_texts(Gnome::Canvas::Group& root)
{
  Gnome::Canvas::Text* text;

  if(root.get_canvas()->property_aa() == true) {
    text = Gtk::manage(new Gnome::Canvas::Text(*make_anchor(root,
                                                       420.0, 20.0)));
    text->property_text() = "Anchor NW";
    text->property_x() = 0.0;
    text->property_y() = 0.0;
    text->property_font() = "Sans Bold 24";
    text->property_anchor() = Gtk::ANCHOR_NW;
    text->property_fill_color_rgba() = 0x0000ff80;
  } else {
    text = Gtk::manage(new Gnome::Canvas::Text(*make_anchor(root,
                                                       420.0, 20.0)));
    text->property_text() = "Anchor NW";
    text->property_x() = 0.0;
    text->property_y() = 0.0;
    text->property_font() = "Sans Bold 24";
    text->property_anchor() = Gtk::ANCHOR_NW;
    text->property_fill_color() = "blue";
    text->property_fill_stipple()
        .set_value(Gdk::Bitmap::create(gray50_bits,
                                       gray50_width,
                                       gray50_height));
  }

  text = Gtk::manage(new Gnome::Canvas::Text(*make_anchor(root,
                                                     470.0, 75.0)));
  text->property_text() = "Anchor center\nJustify center\nMultiline text";
  text->property_x() = 0.0;
  text->property_y() = 0.0;
  text->property_font() = "monospace bold 14";
  text->property_anchor() = Gtk::ANCHOR_CENTER;
  text->property_justification() = Gtk::JUSTIFY_CENTER;
  text->property_fill_color() = "firebrick";

  text = Gtk::manage(new Gnome::Canvas::Text(*make_anchor(root,
                                                     590.0, 140.0)));

//   text->property_text() = "Clipped text\nClipped text\nClipped text\nClipped text\nClipped text\nClipped text";
//   text->property_x() = 0.0;
//   text->property_y() = 0.0;
//   text->property_font() = "Sans 12";
//   text->property_anchor() = Gtk::ANCHOR_SE;
//   text->property_clip() = true;
//   text->property_clip_width() = 50.0;
//   text->property_clip_height() = 55.0;
//   text->property_x_offset() = 10.0;
//   text->property_fill_color() = "darkgreen";

  // example for setting values using the properties mechanism
  *text << Gnome::Canvas::Properties::text ("Clipped text\nClipped text\nClipped text\nClipped text\nClipped text\nClipped text")
        << Gnome::Canvas::Properties::x (0.0)
        << Gnome::Canvas::Properties::y (0.0)
        << Gnome::Canvas::Properties::font ("Sans 12")
        << Gnome::Canvas::Properties::anchor (Gtk::ANCHOR_SE)
        << Gnome::Canvas::Properties::clip (true)
        << Gnome::Canvas::Properties::clip_width (50.0)
        << Gnome::Canvas::Properties::clip_height (55.0)
        << Gnome::Canvas::Properties::x_offset (10.0)
        << Gnome::Canvas::Properties::fill_color ("darkgreen");
}


void
Primitives::plant_flower(Gnome::Canvas::Group& root,
                         double x, double y)
{
  Glib::RefPtr<Gdk::Pixbuf> image
      = Gdk::Pixbuf::create_from_file("flower.png");
  if(image) {
    Gnome::Canvas::Pixbuf* pixbuf
        = Gtk::manage(new Gnome::Canvas::Pixbuf(root, x, y, image));
    pixbuf->signal_event()
        .connect(sigc::bind(sigc::mem_fun(*this, &Primitives::on_item_event), pixbuf));
  }
}


void
Primitives::setup_images(Gnome::Canvas::Group& root)
{
  Glib::RefPtr<Gdk::Pixbuf> image
      = Gdk::Pixbuf::create_from_file("toroid.png");
  if(image) {
    Gnome::Canvas::Pixbuf* pixbuf
        = Gtk::manage(new Gnome::Canvas::Pixbuf(root, 100.0, 225.0, image));
    pixbuf->signal_event()
        .connect(sigc::bind(sigc::mem_fun(*this, &Primitives::on_item_event), pixbuf));
  }

  plant_flower(root,  20.0, 170.0);
  plant_flower(root, 180.0, 170.0);
  plant_flower(root,  20.0, 280.0);
  plant_flower(root, 180.0, 280.0);
}


#define VERTICES 10
#define RADIUS 60.0

void
Primitives::polish_diamond(Gnome::Canvas::Group& root)
{
  Gnome::Canvas::Group* group = Gtk::manage(new Gnome::Canvas::Group(root));
  group->property_x() = 270.0;
  group->property_y() = 230.0;
  group->signal_event()
      .connect(sigc::bind(sigc::mem_fun(*this, &Primitives::on_item_event), group));

  Gnome::Canvas::Points points(2);

  for(int i = 0; i < VERTICES; i++) {
    double a = 2.0 * M_PI * i / VERTICES;
    points[0] = Gnome::Art::Point(RADIUS * std::cos(a),
                                  RADIUS * std::sin(a));

    for(int j = i + 1; j < VERTICES; j++) {
      double a = 2.0 * M_PI * j / VERTICES;
      points[1] = Gnome::Art::Point(RADIUS * std::cos(a),
                                    RADIUS * std::sin(a));
      Gnome::Canvas::Line* line
          = Gtk::manage(new Gnome::Canvas::Line(*group));
      line->property_points().set_value(points);
      line->property_fill_color() = "black";
      line->property_width_units() = 1.0;
      line->property_cap_style() = Gdk::CAP_ROUND;
    }
  }
}


#define SCALE 7.0

void
Primitives::make_hilbert(Gnome::Canvas::Group& root)
{
  Glib::ustring hilbert("urdrrulurulldluuruluurdrurddldrrruluurdrurddldrddlulldrdldrrurd");

  Gnome::Canvas::Points points(hilbert.size() + 1);
  points[0] = Gnome::Art::Point(340.0, 290.0);

  for(int c = 0; c < hilbert.size(); ++c) {
    switch(hilbert[c]) {
    case 'u':
      points[c + 1] = Gnome::Art::Point(points[c].get_x(),
                                        points[c].get_y() - SCALE);
      break;

    case 'd':
      points[c + 1] = Gnome::Art::Point(points[c].get_x(),
                                        points[c].get_y() + SCALE);
      break;

    case 'l':
      points[c + 1] = Gnome::Art::Point(points[c].get_x() - SCALE,
                                        points[c].get_y());
      break;

    case 'r':
      points[c + 1] = Gnome::Art::Point(points[c].get_x() + SCALE,
                                        points[c].get_y());
      break;
    }
  }

  if(root.get_canvas()->property_aa() == true) {
    Gnome::Canvas::Line* line = Gtk::manage(new Gnome::Canvas::Line(root));
    line->property_points().set_value(points);
    line->property_fill_color_rgba() = 0xff000080;
    line->property_width_units() = 4.0;
    line->property_cap_style() = Gdk::CAP_PROJECTING;
    line->property_join_style() = Gdk::JOIN_MITER;
    line->signal_event()
        .connect(sigc::bind(sigc::mem_fun(*this, &Primitives::on_item_event), line));
  } else {
    Gnome::Canvas::Line* line = Gtk::manage(new Gnome::Canvas::Line(root));
    line->property_points().set_value(points);
    line->property_fill_color() = "red";
    line->property_fill_stipple()
        .set_value(Gdk::Bitmap::create(gray50_bits,
                                       gray50_width,
                                       gray50_height));
    line->property_width_units() = 4.0;
    line->property_cap_style() = Gdk::CAP_PROJECTING;
    line->property_join_style() = Gdk::JOIN_MITER;
    line->signal_event()
        .connect(sigc::bind(sigc::mem_fun(*this, &Primitives::on_item_event), line));
  }
}


void
Primitives::setup_lines(Gnome::Canvas::Group& root)
{
  polish_diamond(root);
  make_hilbert(root);

  Gnome::Canvas::Points points;

  points.push_back(Gnome::Art::Point(340.0, 170.0));
  points.push_back(Gnome::Art::Point(340.0, 230.0));
  points.push_back(Gnome::Art::Point(390.0, 230.0));
  points.push_back(Gnome::Art::Point(390.0, 170.0));
  Gnome::Canvas::Line* line = Gtk::manage(new Gnome::Canvas::Line(root));
  line->property_points().set_value(points);
  line->property_fill_color() = "midnightblue";
  line->property_width_units() = 3.0;
  line->property_first_arrowhead() = true;
  line->property_last_arrowhead() = true;
  line->property_arrow_shape_a() = 8.0;
  line->property_arrow_shape_b() = 12.0;
  line->property_arrow_shape_c() = 4.0;
  line->signal_event()
      .connect(sigc::bind(sigc::mem_fun(*this, &Primitives::on_item_event), line));

  points.clear();
  points.push_back(Gnome::Art::Point(356.0, 180.0));
  points.push_back(Gnome::Art::Point(374.0, 220.0));
  line = Gtk::manage(new Gnome::Canvas::Line(root));
  line->property_points().set_value(points);
  line->property_fill_color() = "blue";
  line->property_width_pixels() = 0;
  line->property_first_arrowhead() = true;
  line->property_last_arrowhead() = true;
  line->property_arrow_shape_a() = 6.0;
  line->property_arrow_shape_b() = 6.0;
  line->property_arrow_shape_c() = 4.0;
  line->signal_event()
      .connect(sigc::bind(sigc::mem_fun(*this, &Primitives::on_item_event), line));

  points.clear();
  points.push_back(Gnome::Art::Point(356.0, 220.0));
  points.push_back(Gnome::Art::Point(374.0, 180.0));
  line = Gtk::manage(new Gnome::Canvas::Line(root));
  line->property_points().set_value(points);

//   line->property_fill_color() = "blue";
//   line->property_width_pixels() = 0;
//   line->property_first_arrowhead() = true;
//   line->property_last_arrowhead() = true;
//   line->property_arrow_shape_a() = 6.0;
//   line->property_arrow_shape_b() = 6.0;
//   line->property_arrow_shape_c() = 4.0;

  // example for setting values using the properties mechanism
  *line << Gnome::Canvas::Properties::fill_color ("blue")
        << Gnome::Canvas::Properties::width_pixels (0)
        << Gnome::Canvas::Properties::first_arrowhead (true)
        << Gnome::Canvas::Properties::last_arrowhead (true)
        << Gnome::Canvas::Properties::arrow_shape_a (6.0)
        << Gnome::Canvas::Properties::arrow_shape_b (6.0)
        << Gnome::Canvas::Properties::arrow_shape_c (4.0);

  line->signal_event()
      .connect(sigc::bind(sigc::mem_fun(*this, &Primitives::on_item_event), line));
}


void
Primitives::setup_polygons(Gnome::Canvas::Group& root)
{
  Gnome::Canvas::Points points;
  points.push_back(Gnome::Art::Point(210.0, 320.0));
  points.push_back(Gnome::Art::Point(210.0, 380.0));
  points.push_back(Gnome::Art::Point(260.0, 350.0));

  if(root.get_canvas()->property_aa() == true) {
    Gnome::Canvas::Polygon* polygon
        = Gtk::manage(new Gnome::Canvas::Polygon(root));
    polygon->property_points().set_value(points);
    polygon->property_fill_color_rgba() = 0x0000ff80;
    polygon->property_outline_color() = "black";
    polygon->signal_event()
        .connect(sigc::bind(sigc::mem_fun(*this, &Primitives::on_item_event), polygon));
  } else {
    Gnome::Canvas::Polygon* polygon
        = Gtk::manage(new Gnome::Canvas::Polygon(root));
    polygon->property_points().set_value(points);
    polygon->property_fill_color() = "blue";
    polygon->property_fill_stipple()
        .set_value(Gdk::Bitmap::create(gray50_bits,
                                       gray50_width,
                                       gray50_height));
    polygon->property_outline_color() = "black";
    polygon->signal_event()
        .connect(sigc::bind(sigc::mem_fun(*this, &Primitives::on_item_event), polygon));
  }

  points.clear();
  points.push_back(Gnome::Art::Point(270.0, 330.0));
  points.push_back(Gnome::Art::Point(270.0, 430.0));
  points.push_back(Gnome::Art::Point(390.0, 430.0));
  points.push_back(Gnome::Art::Point(390.0, 330.0));
  points.push_back(Gnome::Art::Point(310.0, 330.0));
  points.push_back(Gnome::Art::Point(310.0, 390.0));
  points.push_back(Gnome::Art::Point(350.0, 390.0));
  points.push_back(Gnome::Art::Point(350.0, 370.0));
  points.push_back(Gnome::Art::Point(330.0, 370.0));
  points.push_back(Gnome::Art::Point(330.0, 350.0));
  points.push_back(Gnome::Art::Point(370.0, 350.0));
  points.push_back(Gnome::Art::Point(370.0, 410.0));
  points.push_back(Gnome::Art::Point(290.0, 410.0));
  points.push_back(Gnome::Art::Point(290.0, 330.0));
  Gnome::Canvas::Polygon* polygon
      = Gtk::manage(new Gnome::Canvas::Polygon(root));
  polygon->property_points().set_value(points);
  polygon->property_fill_color() = "tan";
  polygon->property_outline_color() = "black";
  polygon->property_width_units() = 3.0;
  polygon->signal_event()
      .connect(sigc::bind(sigc::mem_fun(*this, &Primitives::on_item_event), polygon));
}

void
Primitives::setup_curves(Gnome::Canvas::Group& root)
{
  Glib::RefPtr<Gnome::Canvas::PathDef> pathdef
      = Gnome::Canvas::PathDef::create();
  pathdef->moveto(500.0, 175.0);
  pathdef->curveto(550.0, 175.0, 550.0, 275.0, 500.0, 275.0);
  Gnome::Canvas::Bpath* bpath
      = Gtk::manage(new Gnome::Canvas::Bpath(root));
  bpath->set_bpath(pathdef);
  bpath->property_outline_color () = "black";
  bpath->property_width_pixels () = 4;
  bpath->signal_event()
      .connect(sigc::bind(sigc::mem_fun(*this, &Primitives::on_item_event), bpath));
}

void
Primitives::setup_widgets(Gnome::Canvas::Group& root)
{
  Gtk::Button* button = Gtk::manage(new Gtk::Button("Hello world!"));
  Gnome::Canvas::Widget* widget
      = Gtk::manage(new Gnome::Canvas::Widget(root, 420.0, 330.0, *button));
//     widget->property_widget().set_value(Glib::RefPtr<Gtk::Widget>(button));
//     widget->property_x() = 420.0;
//     widget->property_y() = 330.0;
  widget->property_width() = 100.0;
  widget->property_height() = 40.0;
  widget->property_anchor() = Gtk::ANCHOR_NW;
  widget->property_size_pixels() = false;
  widget->signal_event()
      .connect(sigc::bind(sigc::mem_fun(*this, &Primitives::on_item_event), widget));
}
