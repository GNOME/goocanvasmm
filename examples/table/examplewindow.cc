/* Copyright (C) 2008 The goocanvasmm Development Team
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

#include "examplewindow.h"
#include <cairomm/cairomm.h>
#include <iostream>


ExampleWindow::ExampleWindow()
{
  set_title("goocanvasmm - Simple Example");

  m_canvas.set_size_request(640, 480);
  m_canvas.set_bounds(0, 0, 1000, 1000);

  Glib::RefPtr<Goocanvas::Item> root = m_canvas.get_root_item();

  m_table = Goocanvas::Table::create();
  //m_table->property_x() = 10;
  //m_table->property_y() = 10;
  m_table->property_height() = 200;
  m_table->property_width() = 300;
  m_table->property_column_spacing() = 6;
  m_table->property_row_spacing() = 6;
  //m_table->property_columns() = 2;
  //m_table->property_row() = 2;
  root->add_child(m_table);

  add_text_to_cell(m_table, "top left", 0, 0); 
  add_text_to_cell(m_table, "top right", 0, 1);
  add_text_to_cell(m_table, "bottom left", 1, 0);
  add_text_to_cell(m_table, "bottom right", 1, 1);


  Gtk::ScrolledWindow* sw = Gtk::manage(new Gtk::ScrolledWindow());
  sw->add(m_canvas);
  add(*sw);

  show_all_children();
}

void ExampleWindow::add_text_to_cell(const Glib::RefPtr<Goocanvas::Table>& table, const Glib::ustring& text, guint row, guint col)
{
  Glib::RefPtr<Goocanvas::Text> text_item = Goocanvas::Text::create(text);
  table->attach(text_item, col, col+1, row, row+1, Gtk::EXPAND | Gtk::FILL, Gtk::SHRINK);
}

bool
ExampleWindow::on_rect_button_press(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventButton* event)
{
  std::cout << "You clicked the rectangle!" << std::endl ;
  return true ;
}

