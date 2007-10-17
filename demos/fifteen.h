/* fifteen.h
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

#ifndef __FIFTEEN_H
#define __FIFTEEN_H

#include <libgnomecanvasmm/canvas.h>
#include <libgnomecanvasmm/rect.h>
#include <libgnomecanvasmm/group.h>
#include <libgnomecanvasmm/text.h>
#include <gtkmm/frame.h>
#include <gtkmm/alignment.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <vector>

namespace Gnome
{
  namespace Canvas
    {
      class Canvas;
      class Group;
      class Text;
    }
}

class Fifteen : public Gtk::VBox
{
public:
  Fifteen();
  ~Fifteen();
    
protected:
  void on_scramble(void);
  Glib::ustring get_piece_color(int piece);
  bool on_piece_event(GdkEvent* event,
                      Gnome::Canvas::Group* item,
                      Gnome::Canvas::Text* text);
    
  Gnome::Canvas::Canvas* m_canvas;
  std::vector<Gnome::Canvas::Group*> m_board;
};


#endif //__FIFTEEN_H
