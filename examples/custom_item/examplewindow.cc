/* Copyright (C) 2008 The goocanvasmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "examplewindow.h"
#include <cairomm/cairomm.h>
#include <iostream>

ExampleWindow::ExampleWindow()
{
  set_title("goocanvasmm - Custom Item Example");

  m_canvas.set_size_request(640, 480);
  m_canvas.set_bounds(0, 0, 1000, 1000);


  auto item = ExampleItem::create(100, 100, 400, 400);
#ifdef GLIBMM_PROPERTIES_ENABLED
  item->property_line_width() = 10.0;
  item->property_stroke_color() = "yellow";
  item->property_fill_color() = "red";
#else
  item->set_property("line_width", 10.0);
  item->set_property("stroke_color", Glib::ustring("yellow"));
  item->set_property("fill_color", Glib::ustring("red"));
#endif

  auto root = m_canvas.get_root_item();
  root->add_child(item);

  auto sw = Gtk::manage(new Gtk::ScrolledWindow());
  sw->add(m_canvas);
  add(*sw);
}

