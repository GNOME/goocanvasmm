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

#ifndef _GOOCANVASMM_EXAMPLEWINDOW_H
#define _GOOCANVASMM_EXAMPLEWINDOW_H

#include <gtkmm.h>
#include <goocanvasmm.h>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();

private:
  void on_button_translate();
  void on_button_setxy();
  void on_button_scale();
  void on_button_zoom_canvas();
  void on_button_set_width();
  void on_button_set_width_unlimited();

  void update_label();

  Goocanvas::Canvas m_canvas;
  Glib::RefPtr<Goocanvas::Text> m_text;

  Gtk::VBox m_box;
  Gtk::HBox m_button_box1, m_button_box2;
  Gtk::Label m_label_origin, m_label_status;
  Gtk::Button m_button_translate, m_button_scale, m_button_setxy, m_button_zoom;
  Gtk::Button m_button_set_width, m_button_set_width_unlimited;
};

#endif //_GOOCANVASMM_EXAMPLEWINDOW_H

