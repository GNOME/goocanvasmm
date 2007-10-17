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
#include <goocanvasrect.h>
#include <iostream>
#include <sstream>

ExampleWindow::ExampleWindow()
: m_box(false, 6),
  m_button_box(false, 6),
  m_label_origin("origin (0, 0)"),
  m_button_translate("translate(20, 20)"),
  m_button_setxy("set x=50,y=50)"),
  m_button_scale("scale(1.2, 1.2)")
{
  set_title("goocanvasmm Example");

  m_box.pack_start(m_label_origin, Gtk::PACK_SHRINK);
  m_label_origin.set_alignment(0.0, 0.5);

  m_canvas.set_size_request(640, 480);
  m_canvas.set_bounds(0, 0, 1000, 1000);

  Glib::RefPtr<Goocanvas::Item> root = m_canvas.get_root_item();
  m_rect = Goocanvas::Rect::create(10, 10, 60, 60);
  root->add_child(m_rect);
  m_rect->property_line_width().set_value(10.0);
  m_rect->property_stroke_color().set_value("yellow");
  m_rect->property_fill_color().set_value("gray");


  Gtk::ScrolledWindow* sw = Gtk::manage(new Gtk::ScrolledWindow());
  sw->add(m_canvas);
  m_box.pack_start(*sw);

  m_box.pack_start(m_button_box, Gtk::PACK_SHRINK);
  
  m_button_box.pack_start(m_button_translate, Gtk::PACK_SHRINK);
  m_button_translate.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_translate));

  m_button_box.pack_start(m_button_setxy, Gtk::PACK_SHRINK);
  m_button_setxy.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_setxy));

  m_button_box.pack_start(m_button_scale, Gtk::PACK_SHRINK);
  m_button_scale.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_scale));

  m_box.pack_start(m_label_status, Gtk::PACK_SHRINK);
  m_label_status.set_alignment(0.0, 0.5);
  add(m_box);

  show_all_children();

  update_label();
}


void ExampleWindow::update_label()
{
  std::stringstream str;
  str << "Rect: x=" << m_rect->property_x() << ", y=" << m_rect->property_y() << 
         ", width=" << m_rect->property_width() << ",  height=" << m_rect->property_height() << 
         ", line_width=" << m_rect->property_line_width() << std::endl;

  Goocanvas::Bounds bounds = m_rect->get_bounds();
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
  m_rect->property_x() = 50;
  m_rect->property_y() = 50;
  update_label();
}


void ExampleWindow::on_button_scale()
{
  m_rect->scale(1.2, 1.2);
  update_label();
}


