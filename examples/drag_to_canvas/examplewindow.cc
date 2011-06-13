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
#include <iostream>

const int DRAG_DATA_FORMAT = 8; // 8 bits format

ExampleWindow::ExampleWindow()
: m_vbox(false, 6),
  m_hbox(false, 6),
  m_button_rect("Rectangle"),
  m_button_ellipse("Ellipse"),
  m_drag_preview_requested(false)
{
  set_title("goocanvasmm - Simple Example");

  m_drag_targets.push_back( Gtk::TargetEntry("goocanvasmm_example_drag_item", Gtk::TARGET_SAME_APP) );

  add(m_vbox);
  m_vbox.pack_start(m_hbox, Gtk::PACK_SHRINK);

  m_hbox.pack_start(m_button_rect, Gtk::PACK_SHRINK);
  make_widget_draggable(m_button_rect, DRAG_ITEM_RECTANGLE);
  m_hbox.pack_start(m_button_ellipse, Gtk::PACK_SHRINK);
  make_widget_draggable(m_button_ellipse, DRAG_ITEM_ELLIPSE);

  m_canvas.set_size_request(640, 480);
  m_canvas.set_bounds(0, 0, 1000, 1000);


  Gtk::ScrolledWindow* sw = Gtk::manage(new Gtk::ScrolledWindow());
  sw->add(m_canvas);
  m_vbox.pack_start(*sw);

  // Make the canvas a drag-and-drop destination. As we are implementing
  // custom handlers for all (motion, highlight, drop), we set the second
  // argument of drag_dest_set to 0. See the documentation of
  // drag_dest_set for details. It would be nice if Gtk::DestDefaults did
  // contain a GTK_DEST_DEFAULT_NONE, but short of that we can still brute
  // force it to 0.
  m_canvas.drag_dest_set(m_drag_targets, (Gtk::DestDefaults)0, Gdk::ACTION_COPY);
  m_canvas.signal_drag_motion().connect(
      sigc::mem_fun(*this, &ExampleWindow::on_canvas_drag_motion) );
  m_canvas.signal_drag_drop().connect(
      sigc::mem_fun(*this, &ExampleWindow::on_canvas_drag_drop) );

  m_canvas.signal_drag_data_received().connect(
      sigc::mem_fun(*this, &ExampleWindow::on_canvas_drag_data_received) );

  show_all_children();
}

void ExampleWindow::make_widget_draggable(Gtk::Widget& widget, DragItem drag_item)
{
  widget.drag_source_set(m_drag_targets, Gdk::BUTTON1_MASK, Gdk::ACTION_COPY);

  //Set the icon to be shown when dragging:
  //Glib::RefPtr<Gdk::Pixbuf> pixbuf = get_icon_for_toolbar_item(*item);
  //if(pixbuf)
  //  widget.drag_source_set_icon(pixbuf);

  //widget.signal_drag_begin().connect(
  //  sigc::mem_fun(*this, &ExampleWindow::on_toolbar_item_drag_begin) );

  //widget.signal_drag_end().connect(
  //  sigc::mem_fun(*this, &ExampleWindow::on_toolbar_item_drag_end) );

  //Let the item supply some data when the destination asks for it:
  widget.signal_drag_data_get().connect(
    sigc::bind( sigc::mem_fun(*this, &ExampleWindow::on_button_drag_data_get), drag_item) );
}

bool ExampleWindow::on_canvas_drag_drop(const Glib::RefPtr<Gdk::DragContext>& drag_context, int x, int y, guint timestamp)
{
  std::cout << "ExampleWindow::on_canvas_drag_drop" << std::endl;
  Glib::ustring target = m_canvas.drag_dest_find_target(drag_context);
  if(target.empty())
    return false;

  //Get the details, to create the appropriate canvas item:
  //This will cause our drag_data_received callback to be called, with that information:
  m_drag_preview_requested = false;
  m_canvas.drag_get_data(drag_context, target, timestamp);
  return true; //Allow the drop.
}


bool ExampleWindow::on_canvas_drag_motion(const Glib::RefPtr<Gdk::DragContext>& drag_context, int x, int y, guint timestamp)
{
  std::cout << "ExampleWindow::on_canvas_drag_motion" << std::endl;
  Glib::ustring target = m_canvas.drag_dest_find_target(drag_context);
  if(target.empty())
    return false;

  m_canvas.drag_highlight();

  //Create the temporary canvas item if necesary:
  if(!m_layout_item_dropping)
  {
    std::cout << "  ExampleWindow::on_canvas_drag_motion(): Calling drag_get_data()" << std::endl;

    //TODO: This stops the drop (or any further motion events) from happening:

    //We need to examine the SelectionData:
    //This will cause our drag_data_received callback to be called, with that information:
    m_drag_preview_requested = true;
    m_canvas.drag_get_data(drag_context, target, timestamp);
    return true;
  }

  std::cout << "  ExampleWindow::on_canvas_drag_motion(): item already created." << std::endl;

  drag_context->drag_status(Gdk::ACTION_COPY, timestamp);

  //Move the temporary canvas item to the new position:
  double item_x = x;
  double item_y = y;
  m_canvas.convert_from_pixels(item_x, item_y);

  gdouble t_x, t_y, t_scale, t_rotation;
  m_layout_item_dropping->get_simple_transform(t_x, t_y, t_scale, t_rotation);
  m_layout_item_dropping->set_simple_transform(item_x, item_y, t_scale, t_rotation);

  return true; //Allow the drop.
}

ExampleWindow::DragItem ExampleWindow::get_drag_item_from_selection_data(const Gtk::SelectionData& selection_data)
{
  DragItem item_type = DRAG_ITEM_NONE;
  if((selection_data.get_length() >= 0) && (selection_data.get_format() == DRAG_DATA_FORMAT))
  {
    const guint8* data = selection_data.get_data();
    if(data)
      item_type = (DragItem)(data[0]);
  }

  return item_type;
}

void ExampleWindow::on_canvas_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& drag_context, int x, int y, const Gtk::SelectionData& selection_data, guint info, guint timestamp)
{
  std::cout << "ExampleWindow::on_canvas_drag_data_received" << std::endl;

  //This is called when an item is dropped on the canvas,
  //or after our drag_motion handler has called drag_get_data()): 
  
  //Discover what toolbar item was dragged:
  const DragItem drag_item = get_drag_item_from_selection_data(selection_data);


  //Create the temporary drag item if necessary:
  if(m_drag_preview_requested && !m_layout_item_dropping)
  {
    m_layout_item_dropping = create_canvas_item(drag_item, x, y);
  }
  else
  {
    if(m_layout_item_dropping)
      m_layout_item_dropping->remove();

    m_layout_item_dropping.clear();
    create_canvas_item(drag_item, x, y);
  }
  
  if(m_drag_preview_requested)
  {
    std::cout << "ExampleWindow::on_canvas_drag_data_received: m_drag_preview_requested" << std::endl;

    drag_context->drag_status(Gdk::ACTION_COPY, timestamp);
    m_drag_preview_requested = false;
  }
  else
  {
    drag_context->drag_finish(false, false, timestamp);
    m_canvas.drag_unhighlight();
  }
}

void ExampleWindow::on_button_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& drag_context, Gtk::SelectionData& selection_data, guint info, guint time, DragItem drag_item)
{
  std::cout << "ExampleWindow::on_button_drag_data_get" << std::endl;
  
  selection_data.set(selection_data.get_target(), DRAG_DATA_FORMAT,
          (const guchar*)&drag_item,
          1 /* 1 byte */);
}

Glib::RefPtr<Goocanvas::Item> ExampleWindow::create_canvas_item(DragItem drag_item, int x, int y)
{
  Glib::RefPtr<Goocanvas::Item> result;

  if(drag_item == DRAG_ITEM_RECTANGLE)
  {
    Glib::RefPtr<Goocanvas::Rect> rect = Goocanvas::Rect::create(0, 0, 20, 20);
#ifdef GLIBMM_PROPERTIES_ENABLED
    rect->property_line_width() = 10.0;
    rect->property_stroke_color() = "yellow";
    rect->property_fill_color() = "red";
#else
    rect->set_property("line_width", 10.0);
    rect->set_property("stroke_color", Glib::ustring("yellow"));
    rect->set_property("fill_color", Glib::ustring("red"));
#endif //GLIBMM_PROPERTIES_ENABLED
    result = rect;
  }
  else if(drag_item == DRAG_ITEM_ELLIPSE)
  {
    Glib::RefPtr<Goocanvas::Ellipse> ellipse = Goocanvas::Ellipse::create();
#ifdef GLIBMM_PROPERTIES_ENABLED
    ellipse->property_line_width() = 10.0;
    ellipse->property_radius_x() = 20.0;
    ellipse->property_radius_y() = 20.0;
    ellipse->property_stroke_color() = "yellow";
    ellipse->property_fill_color() = "red";
#else
    ellipse->set_property("line_width", 10.0);
    ellipse->set_property("radius_x", 20.0);
    ellipse->set_property("radius_y", 20.0);
    ellipse->set_property("stroke_color", Glib::ustring("yellow"));
    ellipse->set_property("fill_color", Glib::ustring("red"));
#endif //GLIBMM_PROPERTIES_ENABLED
    result = ellipse;
  }

  if(result)
  {
    Glib::RefPtr<Goocanvas::Item> root = m_canvas.get_root_item();
    root->add_child(result);

    //Show it on the canvas, at the position:
    double item_x = x;
    double item_y = y;
    m_canvas.convert_from_pixels(item_x, item_y);
    result->translate(item_x, item_y);
  }

  return result;
}

