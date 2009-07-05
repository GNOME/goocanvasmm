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

#include <goocanvasrect.h>
#include <iostream>
#include "window.h"

Window::Window()
{
  set_title("goocanvasmm Moving Shapes");
  set_default_size(640, 480);

  _canvas = Gtk::manage(new Goocanvas::Canvas());
  _canvas->signal_item_created().connect(sigc::mem_fun(*this, &Window::on_item_created));
  Glib::RefPtr<Goocanvas::ItemModel> root = Goocanvas::GroupModel::create();
  _canvas->set_root_item_model(root);

  Glib::RefPtr<Goocanvas::RectModel> rect = Goocanvas::RectModel::create(200, 200, 100, 100);
        root->add_child(rect);
#ifdef GLIBMM_PROPERTIES_ENABLED
  rect->property_line_width() = 3;
  rect->property_radius_x() = 10.0;
  rect->property_radius_y() = 10.0;
  rect->property_stroke_color() = "red";
  rect->property_fill_color() = "blue";
#else
  rect->set_property("line_width", 3);
  rect->set_property("radius_x", 10.0);
  rect->set_property("radius_y", 10.0);
  rect->set_property("stroke_color", Glib::ustring("red"));
  rect->set_property("fill_color", Glib::ustring("blue"));
#endif //GLIBMM_PROPERTIES_ENABLED

  Glib::RefPtr<Goocanvas::EllipseModel> ellipse = Goocanvas::EllipseModel::create(400, 200, 100, 50);
        root->add_child(ellipse);
#ifdef GLIBMM_PROPERTIES_ENABLED
  ellipse->property_line_width() = 3;
  ellipse->property_stroke_color() = "midnightblue";
  ellipse->property_fill_color() = "wheat";
#else
  ellipse->set_property("line_width", 3);
  ellipse->set_property("stroke_color", Glib::ustring("midnightblue"));
  ellipse->set_property("fill_color", Glib::ustring("wheat"));
#endif //GLIBMM_PROPERTIES_ENABLED

  Glib::RefPtr<Goocanvas::PolylineModel> polyline = Goocanvas::PolylineModel::create(250, 250, 450, 225);
        root->add_child(polyline);
#ifdef GLIBMM_PROPERTIES_ENABLED
  polyline->property_line_width() = 4;
#else
  polyline->set_property("line_width", 4);
#endif //GLIBMM_PROPERTIES_ENABLED

  Gtk::ScrolledWindow* sw = Gtk::manage(new Gtk::ScrolledWindow());
  sw->add(*_canvas);
  add(*sw);

  show_all_children();
}

void
Window::on_item_created(const Glib::RefPtr<Goocanvas::Item>& item, const Glib::RefPtr<Goocanvas::ItemModel>& model)
{
  Glib::RefPtr<Goocanvas::Group> group = Glib::RefPtr<Goocanvas::Group>::cast_dynamic(item);
  if(group) return ;

  item->signal_button_press_event().connect(sigc::mem_fun(*this, &Window::on_item_button_press_event));
  item->signal_button_release_event().connect(sigc::mem_fun(*this, &Window::on_item_button_release_event));
  item->signal_motion_notify_event().connect(sigc::mem_fun(*this, &Window::on_item_motion_notify_event));
}

bool
Window::on_item_button_press_event(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventButton* event)
{
  if(event->button == 1)
  {
    _dragging = item ;
    _drag_x = (int) event->x ;
    _drag_y = (int) event->y ;
  }
  return false;
}

bool
Window::on_item_button_release_event(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventButton* event)
{
  if(event->button == 1)
  {
    _dragging.clear();
  }
  return false;
}

bool
Window::on_item_motion_notify_event(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventMotion* event)
{
  if(item && _dragging && item == _dragging)
  {
    double new_x = event->x ;
    double new_y = event->y ;
    item->translate(new_x - _drag_x, new_y - _drag_y);
  }
  return false;
}
