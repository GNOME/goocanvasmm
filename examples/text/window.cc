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
: m_box(Gtk::ORIENTATION_VERTICAL, 6),
  m_button_box1(Gtk::ORIENTATION_HORIZONTAL, 6),
  m_button_box2(Gtk::ORIENTATION_HORIZONTAL, 6),
  m_label_origin("origin (0, 0)"),
  m_button_translate("translate(20, 20)"),
  m_button_scale("scale(1.2, 1.2)"),
  m_button_setxy("set x=50,y=50)"),
  m_button_zoom("scale (zoom) canvas"),
  m_button_set_width("set width=40"),
  m_button_set_width_unlimited("set width=-1 (unlimited)")
{
  set_title("goocanvasmm Example");

  m_box.pack_start(m_label_origin, Gtk::PACK_SHRINK);
  m_label_origin.set_xalign(0.0);

  m_canvas.set_size_request(640, 480);
#ifdef GLIBMM_PROPERTIES_ENABLED
  m_canvas.property_units() = Gtk::UNIT_MM;
#else
  m_canvas.set_property("units", Gtk::UNIT_MM);
#endif 
  m_canvas.set_bounds(0, 0, 210, 297);

  auto root = m_canvas.get_root_item();
  m_text = Goocanvas::Text::create("some text");
  root->add_child(m_text);
#ifdef GLIBMM_PROPERTIES_ENABLED
  m_text->property_font() = "Sans 9";
  m_text->property_line_width() = 10.0;
  m_text->property_stroke_color() = "yellow";
  m_text->property_fill_color() = "gray";
#else
  m_text->set_property("font", Glib::ustring("Sans 9"));
  m_text->set_property("line_width", 10.0);
  m_text->set_property("stroke_color", Glib::ustring("yellow"));
  m_text->set_property("fill_color", Glib::ustring("gray"));
#endif


  auto sw = Gtk::manage(new Gtk::ScrolledWindow());
  sw->add(m_canvas);
  m_box.pack_start(*sw);

  m_box.pack_start(m_button_box1, Gtk::PACK_SHRINK);
  
  m_button_box1.pack_start(m_button_translate, Gtk::PACK_SHRINK);
  m_button_translate.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_translate));

  m_button_box1.pack_start(m_button_setxy, Gtk::PACK_SHRINK);
  m_button_setxy.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_setxy));

  m_button_box1.pack_start(m_button_scale, Gtk::PACK_SHRINK);
  m_button_scale.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_scale));

  m_button_box1.pack_start(m_button_zoom, Gtk::PACK_SHRINK);
  m_button_zoom.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_zoom_canvas));

  m_box.pack_start(m_button_box2, Gtk::PACK_SHRINK);
  
  m_button_box2.pack_start(m_button_set_width, Gtk::PACK_SHRINK);
  m_button_set_width.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_set_width));

  m_button_box2.pack_start(m_button_set_width_unlimited, Gtk::PACK_SHRINK);
  m_button_set_width_unlimited.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_set_width_unlimited));

  m_box.pack_start(m_label_status, Gtk::PACK_SHRINK);
  m_label_status.set_xalign(0.0);
  add(m_box);

  show_all_children();

  update_label();
}


void ExampleWindow::update_label()
{
  std::stringstream str;

#ifdef GLIBMM_PROPERTIES_ENABLED
  str << "Rect: x=" << m_text->property_x() << ", y=" << m_text->property_y() << 
         ", width=" << m_text->property_width() << //",  height=" << m_text->property_height() << 
         ", line_width=" << m_text->property_line_width() << std::endl;
#else
  //TODO:
#endif

  auto bounds = m_text->get_bounds();
  str << "Item bounds: x1=" << bounds.get_x1() << ", y1=" << bounds.get_y1() << ", x2=" << bounds.get_x2() << ", y2=" << bounds.get_y2() << std::endl;

  

  m_label_status.set_text(str.str());
}

void ExampleWindow::on_button_translate()
{
  m_text->translate(20, 20);
  update_label();
}

void ExampleWindow::on_button_setxy()
{
#ifdef GLIBMM_PROPERTIES_ENABLED
  m_text->property_x() = 50;
  m_text->property_y() = 50;
#else
  m_text->set_property("x", 50);
  m_text->set_property("y", 50);
#endif

  update_label();
}

void ExampleWindow::on_button_scale()
{
  m_text->scale(1.2, 1.2);
  update_label();
}

void ExampleWindow::on_button_zoom_canvas()
{
  m_canvas.set_scale(m_canvas.get_scale() + 0.1);
  update_label();
}

void ExampleWindow::on_button_set_width()
{
#ifdef GLIBMM_PROPERTIES_ENABLED
  m_text->property_width() = 40;
#else
  m_text->set_property("width", 40);
#endif

  update_label();
}

void ExampleWindow::on_button_set_width_unlimited()
{
#ifdef GLIBMM_PROPERTIES_ENABLED
  m_text->property_width() = -1;
#else
  m_text->set_property("width", -1);
#endif
  update_label();
}






