/* example Copyright (C) 2007 goocanvasmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "window.h"
#include <iostream>
#include <sstream>

ExampleWindow::ExampleWindow()
: m_box(Gtk::Orientation::VERTICAL, 6),
  m_button_box(Gtk::Orientation::HORIZONTAL, 6),
  m_label_origin("origin (0, 0)"),
  m_button_translate("translate(20, 20)"),
  m_button_scale("scale(1.2, 1.2)"),
  m_button_setxy("set x=50,y=50)")
{
  set_title("goocanvasmm Example");

  m_box.pack_start(m_label_origin, Gtk::PackOptions::SHRINK);
  m_label_origin.set_xalign(0.0);

  m_canvas.set_size_request(640, 480);
  m_canvas.set_bounds(0, 0, 1000, 1000);

  auto root = m_canvas.get_root_item();
  m_rect = Goocanvas::Rect::create(10, 10, 60, 60);
  root->add_child(m_rect);
#ifdef GLIBMM_PROPERTIES_ENABLED
  m_rect->property_line_width() = 10.0;
  m_rect->property_stroke_color() = "yellow";
  m_rect->property_fill_color() = "gray";
#else
  m_rect->set_property("line_width", 10.0);
  m_rect->set_property("stroke_color", Glib::ustring("yellow"));
  m_rect->set_property("fill_color", Glib::ustring("gray"));
#endif


  auto sw = Gtk::manage(new Gtk::ScrolledWindow());
  sw->add(m_canvas);
  m_box.pack_start(*sw);

  m_box.pack_start(m_button_box, Gtk::PackOptions::SHRINK);
  
  m_button_box.pack_start(m_button_translate, Gtk::PackOptions::SHRINK);
  m_button_translate.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_translate));

  m_button_box.pack_start(m_button_setxy, Gtk::PackOptions::SHRINK);
  m_button_setxy.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_setxy));

  m_button_box.pack_start(m_button_scale, Gtk::PackOptions::SHRINK);
  m_button_scale.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_scale));

  m_box.pack_start(m_label_status, Gtk::PackOptions::SHRINK);
  m_label_status.set_xalign(0.0);
  add(m_box);

  update_label();
}


void ExampleWindow::update_label()
{
  std::stringstream str;
#ifdef GLIBMM_PROPERTIES_ENABLED
  str << "Rect: x=" << m_rect->property_x() << ", y=" << m_rect->property_y() <<
         ", width=" << m_rect->property_width() << ",  height=" << m_rect->property_height() <<
         ", line_width=" << m_rect->property_line_width() << std::endl;
#else
  //TODO.
#endif

  auto bounds = m_rect->get_bounds();
  str << "Item bounds: x1=" << bounds.get_x1() << ", y1=" << bounds.get_y1() << ", x2=" << bounds.get_x2() << ", y2=" << bounds.get_y2() << std::endl;

  

  m_label_status.set_text(str.str());
}

void ExampleWindow::on_button_translate()
{
  m_rect->translate(20, 20);
  update_label();
}

void ExampleWindow::on_button_setxy()
{
#ifdef GLIBMM_PROPERTIES_ENABLED
  m_rect->property_x() = 50;
  m_rect->property_y() = 50;
#else
  m_rect->set_property("x", 50);
  m_rect->set_property("y", 50);
#endif

  update_label();
}


void ExampleWindow::on_button_scale()
{
  m_rect->scale(1.2, 1.2);
  update_label();
}



