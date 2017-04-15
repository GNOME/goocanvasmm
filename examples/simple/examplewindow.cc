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
  set_title("goocanvasmm - Simple Example");

  m_canvas.set_size_request(640, 480);
  m_canvas.set_bounds(0, 0, 1000, 1000);

  auto root = m_canvas.get_root_item();
  auto rect = Goocanvas::Rect::create(100, 100, 400, 400);
  root->add_child(rect);

#ifdef GLIBMM_PROPERTIES_ENABLED
  rect->property_line_width() = 10.0;
  rect->property_radius_x() = 20.0;
  rect->property_radius_y() = 20.0;
  rect->property_stroke_color() = "yellow";
  rect->property_fill_color() = "red";
#else
  rect->set_property("line_width", 10.0);
  rect->set_property("radius_x", 20.0);
  rect->set_property("radius_y", 20.0);
  rect->set_property("stroke_color", Glib::ustring("yellow"));
  rect->set_property("fill_color", Glib::ustring("red"));
#endif //GLIBMM_PROPERTIES_ENABLED
  rect->signal_button_press_event ().connect (sigc::mem_fun(*this,
    &ExampleWindow::on_rect_button_press));

  auto text = Goocanvas::Text::create("Hello World", 300, 300, -1, Goocanvas::AnchorType::CENTER);
  root->add_child(text);
#ifdef GLIBMM_PROPERTIES_ENABLED
  text->property_font() = "Sans 24";
#else
  text->set_property("font=", Glib::ustring("Sans 24"));
#endif //GLIBMM_PROPERTIES_ENABLED
  text->rotate(45, 300, 300);

  auto sw = Gtk::manage(new Gtk::ScrolledWindow());
  sw->add(m_canvas);
  add(*sw);
}

bool
ExampleWindow::on_rect_button_press(const Glib::RefPtr<Goocanvas::Item>& /* item */, GdkEventButton* /* event */)
{
  std::cout << "You clicked the rectangle." << std::endl ;
  return true ;
}

