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

#include "exampleitem.h"
#include <goocanvasitemsimple.h>

ExampleItem::ExampleItem(double x, double y, double width, double height)
: m_x(x), m_y(y), m_width(width), m_height(height)
{
}

Glib::RefPtr<ExampleItem> ExampleItem::create(double x, double y, double width, double height)
{
  return Glib::RefPtr<ExampleItem>(new ExampleItem(x, y, width, height));
}

/* The update method. This is called when the canvas is initially shown and
     also whenever the object is updated and needs to change its size and/or
     shape. It should calculate its new bounds in its own coordinate space,
     storing them in simple->bounds. */
void ExampleItem::simple_update_vfunc(const Cairo::RefPtr<Cairo::Context>& cr)
{
  Goocanvas::ItemSimple::simple_update_vfunc(cr);

  GooCanvasItemSimple* simple = GOO_CANVAS_ITEM_SIMPLE(gobj());
  if(simple)
  {
    /* Compute the new bounds. */
    simple->bounds.x1 = m_x;
    simple->bounds.y1 = m_y;
    simple->bounds.x2 = m_x + m_width;
    simple->bounds.y2 = m_y + m_height;
  }
}


void ExampleItem::simple_paint_vfunc(const Cairo::RefPtr<Cairo::Context>& cr, const Goocanvas::Bounds& bounds)
{
  Goocanvas::ItemSimple::simple_paint_vfunc(cr, bounds);

  if(!cr)
    return;

  cr->move_to(m_x, m_y);
  cr->line_to(m_x, m_y + m_height);
  cr->line_to(m_x + m_width, m_y + m_height);
  cr->line_to(m_x + m_width, m_y);
  cr->close_path();

  GooCanvasItemSimple* simple = GOO_CANVAS_ITEM_SIMPLE(gobj());
  if(simple && simple->simple_data)
  {
    Glib::RefPtr<Goocanvas::Style> style = Glib::wrap(simple->simple_data->style, true /* take_copy */);
    if(style)
      style->set_fill_options(cr);
  }

  cr->fill();
}

