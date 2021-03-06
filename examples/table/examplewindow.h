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

#ifndef _GOOCANVASMM_EXAMPLEWINDOW_H
#define _GOOCANVASMM_EXAMPLEWINDOW_H

#include <gtkmm.h>
#include <goocanvasmm.h>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();

protected:

  void add_text_to_cell(const Glib::RefPtr<Goocanvas::Table>&, const Glib::ustring& text, guint row, guint col);

  bool on_rect_button_press(const Glib::RefPtr<Goocanvas::Item>& target, Gdk::EventButton& event);
  
  Goocanvas::Canvas m_canvas;
  Glib::RefPtr<Goocanvas::Table> m_table;
};

#endif //_GOOCANVASMM_EXAMPLEWINDOW_H

