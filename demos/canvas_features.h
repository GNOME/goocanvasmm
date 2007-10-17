/* features.h
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

#ifndef __FEATURES_H
#define __FEATURES_H

//This file would be called features.h, but there is a system header of the same name.

#include <gtkmm/box.h>
#include <libgnomecanvasmm/canvas.h>
#include <libgnomecanvasmm/ellipse.h>
#include <libgnomecanvasmm/rect.h>
#include <libgnomecanvasmm/group.h>
#include <gtkmm/label.h>
#include <gtkmm/frame.h>
#include <gtkmm/alignment.h>

class Features : public Gtk::VBox
{
public:
  Features();
  ~Features();
    
protected:
  bool on_item_event(GdkEvent* event, Gnome::Canvas::Item* item);

  Gnome::Canvas::Group* m_parent1;
  Gnome::Canvas::Group* m_parent2;
};


#endif //__FEATURES_H
