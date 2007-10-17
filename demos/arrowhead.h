/* arrowhead.h
 *
 * Copyright (C) 2002 The libgnomecanvasmm Development Team
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

#ifndef __ARROWHEAD_H
#define __ARROWHEAD_H



#include <gtkmm/box.h>
#include <libgnomecanvasmm/rect.h>
#include <libgnomecanvasmm/canvas.h>
#include <libgnomecanvasmm/rect.h>
#include <libgnomecanvasmm/group.h>
#include <libgnomecanvasmm/text.h>
#include <libgnomecanvasmm/line.h>
#include <vector>

class DragBox : public Gnome::Canvas::Rect
{
public:
  DragBox(Gnome::Canvas::Group& root);
  ~DragBox();

  void move_drag_box(double x, double y);

protected:
  bool on_event(GdkEvent* event);
};


class Dimension
{
public:
  Dimension(Gnome::Canvas::Group& root, Gtk::AnchorType anchor);
  ~Dimension();

  void set_dimension(double x1, double y1, 
                     double x2, double y2, 
                     double tx, double ty, 
                     int dim);

protected:
  Gnome::Canvas::Line* m_line;
  Gnome::Canvas::Text* m_text;
};

class Arrowhead : public Gtk::VBox
{
public:
  Arrowhead();
  virtual ~Arrowhead();
    
protected:
  bool on_width_event(GdkEvent* event,
                      Gnome::Canvas::Item* item);
  bool on_shape_a_event(GdkEvent* event,
                        Gnome::Canvas::Item* item);
  bool on_shape_b_c_event(GdkEvent* event,
                          Gnome::Canvas::Item* item);
  
  Gnome::Canvas::Text* create_info(Gnome::Canvas::Group& root,
                                   double x, double y);
  Gnome::Canvas::Line* create_sample_arrow(Gnome::Canvas::Group& root, 
                                           double x1, double y1,
                                           double x2, double y2);
  void set_arrow_shape();
  
  int m_width;
  int m_shape_a;
  int m_shape_b;
  int m_shape_c;
  Gnome::Canvas::Line* m_big_arrow;
  Gnome::Canvas::Line* m_outline;
  DragBox* m_width_drag_box;
  DragBox* m_shape_a_drag_box;
  DragBox* m_shape_b_c_drag_box;
  Dimension* m_width_arrow;
  Dimension* m_shape_a_arrow;
  Dimension* m_shape_b_arrow;
  Dimension* m_shape_c_arrow;
  Gnome::Canvas::Text* m_width_info;
  Gnome::Canvas::Text* m_shape_a_info;
  Gnome::Canvas::Text* m_shape_b_info;
  Gnome::Canvas::Text* m_shape_c_info;
  Gnome::Canvas::Line* m_sample1;
  Gnome::Canvas::Line* m_sample2;
  Gnome::Canvas::Line* m_sample3;
};


#endif //__ARROWHEAD_H
