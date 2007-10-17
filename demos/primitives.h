/* primitives.h
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

#ifndef __PRIMITIVES_HH
#define __PRIMITIVES_HH

#include <libgnomecanvasmm/canvas.h>
#include <gtkmm/label.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/button.h>
#include <gtkmm/scrollbar.h>
#include <gtkmm/frame.h>
#include <gtkmm/table.h>
#include <gtkmm/box.h>


class Primitives : public Gtk::VBox
{
public:
  Primitives(bool aa);
  ~Primitives();
  
protected:
  void on_zoom_changed(Gnome::Canvas::Canvas* canvas,
                    Gtk::Adjustment* adj);
  bool on_key_press(GdkEventKey* event, Gnome::Canvas::Canvas* canvas);
  bool on_item_event(GdkEvent* event, Gnome::Canvas::Item* item);
  
  void setup_heading(Gnome::Canvas::Group& root,
                     const Glib::ustring& text,
                     int pos);
  void setup_divisions(Gnome::Canvas::Group& root);
  void setup_rectangles(Gnome::Canvas::Group& root);
  void setup_ellipses(Gnome::Canvas::Group& root);
  void plant_flower(Gnome::Canvas::Group& root,
                    double x, double y);
  void setup_images(Gnome::Canvas::Group& root);
  Gnome::Canvas::Group* make_anchor(Gnome::Canvas::Group& root, 
                                    double x, double y);
  void setup_texts(Gnome::Canvas::Group& root);
  void polish_diamond(Gnome::Canvas::Group& root);
  void make_hilbert(Gnome::Canvas::Group& root);
  void setup_lines(Gnome::Canvas::Group& root);
  void setup_polygons(Gnome::Canvas::Group& root);
  void setup_curves(Gnome::Canvas::Group& root);
  void setup_widgets(Gnome::Canvas::Group& root);
};


#endif //__PRIMITIVES_HH
