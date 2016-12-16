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

  enum DragItem
  {
    DRAG_ITEM_NONE,
    DRAG_ITEM_RECTANGLE,
    DRAG_ITEM_ELLIPSE
  };

  void make_widget_draggable(Gtk::Widget& widget, DragItem drag_item);

  void on_button_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& drag_context, Gtk::SelectionData& selection_data, guint info, guint time, DragItem drag_item);
  bool on_canvas_drag_drop(const Glib::RefPtr<Gdk::DragContext>& drag_context, int x, int y, guint timestamp);
  bool on_canvas_drag_motion(const Glib::RefPtr<Gdk::DragContext>& drag_context, int x, int y, guint timestamp);
  void on_canvas_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& drag_context, int x, int y, const Gtk::SelectionData& selection_data, guint info, guint timestamp);

  Glib::RefPtr<Goocanvas::Item> create_canvas_item(DragItem drag_item, int x, int y);
  
  static DragItem get_drag_item_from_selection_data(const Gtk::SelectionData& selection_data);
  
  Goocanvas::Canvas m_canvas;

  Gtk::Box m_vbox;
  Gtk::Box m_hbox;
  Gtk::Button m_button_rect, m_button_ellipse;

  std::vector<Gtk::TargetEntry> m_drag_targets;
  Glib::RefPtr<Goocanvas::Item> m_layout_item_dropping;
  bool m_drag_preview_requested;
};

#endif //_GOOCANVASMM_EXAMPLEWINDOW_H

