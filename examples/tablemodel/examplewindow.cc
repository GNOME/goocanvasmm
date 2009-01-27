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
  set_title("goocanvasmm - TableModel example");

  m_first_canvas.set_size_request(640, 240);
  m_first_canvas.set_bounds(0, 0, 1000, 1000);

  m_second_canvas.set_size_request(640, 240);
  m_second_canvas.set_bounds(0, 0, 500, 500);

  Glib::RefPtr<Goocanvas::ItemModel> root = Goocanvas::GroupModel::create() ;
  m_first_canvas.set_root_item_model(root);
  m_second_canvas.set_root_item_model(root);

  m_table = Goocanvas::TableModel::create();
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


  Gtk::ScrolledWindow* sw1 = Gtk::manage(new Gtk::ScrolledWindow());
  sw1->add(m_first_canvas);
  Gtk::ScrolledWindow* sw2 = Gtk::manage(new Gtk::ScrolledWindow());
  sw2->add(m_second_canvas);

  Gtk::VBox* box = Gtk::manage(new Gtk::VBox(false, 6));
  box->pack_start(*sw1, Gtk::PACK_EXPAND_WIDGET);
  box->pack_start(*sw2, Gtk::PACK_EXPAND_WIDGET);
  add(*box);

  show_all_children();
}

void ExampleWindow::add_text_to_cell(const Glib::RefPtr<Goocanvas::TableModel>& table, const Glib::ustring& text, guint row, guint col)
{
  Glib::RefPtr<Goocanvas::TextModel> text_item = Goocanvas::TextModel::create(text);
  table->attach(text_item, col, col+1, row, row+1, Gtk::EXPAND | Gtk::FILL, Gtk::SHRINK);
}

