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

class Window : public Gtk::Window
{
public:
  Window();

private:

  Goocanvas::Canvas* _canvas ;

  Glib::RefPtr< Goocanvas::Item > _dragging ;
  int _drag_x ;
  int _drag_y ;

  void on_item_created(const Glib::RefPtr<Goocanvas::Item>& item, const Glib::RefPtr<Goocanvas::ItemModel>& model);
  bool on_item_button_press_event(const Glib::RefPtr<Goocanvas::Item>& item, Gdk::EventButton& event);
  bool on_item_button_release_event(const Glib::RefPtr<Goocanvas::Item>& item, Gdk::EventButton& event);
  bool on_item_motion_notify_event(const Glib::RefPtr<Goocanvas::Item>& item, Gdk::EventMotion& event);
/*
  bool on_focus_in_event(const Glib::RefPtr<Goocanvas::Item>& view, Gdk::EventFocus& event);
  bool on_focus_out_event(const Glib::RefPtr<Goocanvas::Item>& view, Gdk::EventFocus& event);
*/
};

#endif //_GOOCANVASMM_EXAMPLEWINDOW_H

