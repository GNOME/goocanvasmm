/* curve.h
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

#ifndef __CURVE_H
#define __CURVESH

#include <gtkmm/box.h>
#include <libgnomecanvasmm/line.h>
#include <libgnomecanvasmm/bpath.h>
#include <libgnomecanvasmm/canvas.h>

namespace Gtk {
    class Widget;
}


class Curve: public Gtk::VBox
{
public:
  enum State {
      STATE_INIT = 0,
      STATE_FIRST_PRESS,
      STATE_FIRST_RELEASE,
      STATE_SECOND_PRESS,
  };

  Curve();
  ~Curve();

protected:
  Gtk::Widget* create_canvas(bool aa);
  bool on_canvas_event(GdkEvent* event, Gnome::Canvas::Canvas* canvas);
  bool on_item_event(GdkEvent* event, Gnome::Canvas::Bpath* bpath);
  void draw_curve(Gnome::Canvas::Canvas& canvas, double x, double y);

  State m_current_state;
  Gnome::Canvas::Points m_points;
  Gnome::Canvas::Bpath* m_current_item;
};

#endif //__CURVE_H
