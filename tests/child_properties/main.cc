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

#include <gtkmm.h>
#include <goocanvasmm.h>
#include <iostream>

int
main(int argc, char* argv[])
{
  Gtk::Main app(&argc, &argv) ;
  Goocanvas::init("goocanvasmm Simple Example", "0.1", argc, argv);

  Glib::RefPtr<Goocanvas::Table> table = Goocanvas::Table::create();

  //Add a child to the table:
  Glib::RefPtr<Goocanvas::Text> child = Goocanvas::Text::create("test");
  table->attach(child, 2, 3, 5, 6, Gtk::EXPAND | Gtk::FILL, Gtk::SHRINK);

  //Examine the child property:
  Glib::Value<int> column_value;
  column_value.init(Glib::Value<int>::value_type());
  table->get_child_property(child, "column", column_value);

  std::cout << "Column: " << column_value.get() << std::endl;

  return 0;
}
