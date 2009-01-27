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

#ifndef _GOOCANVASMM_EXAMPLEITEM_H
#define _GOOCANVASMM_EXAMPLEITEM_H

#include <goocanvasmm/itemsimple.h>

class ExampleItem : public Goocanvas::ItemSimple
{
protected:
  ExampleItem(double x = 0, double y = 0, double width = 0, double height = 0);

public:
  static Glib::RefPtr<ExampleItem> create(double x = 0, double y = 0, double width = 0, double height = 0);

protected:
  void simple_update_vfunc(const Cairo::RefPtr<Cairo::Context>& cr);
  void simple_paint_vfunc(const Cairo::RefPtr<Cairo::Context>& cr, const Goocanvas::Bounds& bounds);

  double m_x, m_y;
  double m_width, m_height;
};

#endif //_GOOCANVASMM_EXAMPLEWINDOW_H

