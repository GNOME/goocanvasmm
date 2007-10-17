/* $Id: generate_defs_libgnomecanvas.cc 509 2003-11-03 09:41:50Z murrayc $ */

/* generate_defs_libgnomecanvas.h
 *
 * Copyright (C) 2001 The Free Software Foundation
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
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

#include "glibmm_generate_extra_defs/generate_extra_defs.h"
#include <libgnomecanvas/libgnomecanvas.h>
//#include <libgnomecanvas/gnome-canvas-clipgroup.h>

#include <gtk/gtk.h>

int main (int argc, char *argv[])
{
  gtk_init(&argc, &argv);

  std::cout << get_defs( GNOME_TYPE_CANVAS_BPATH )
            //<< get_defs( GNOME_TYPE_CANVAS_CLIPGROUP )
            << get_defs( GNOME_TYPE_CANVAS_LINE )
            << get_defs( GNOME_TYPE_CANVAS_PIXBUF )
            << get_defs( GNOME_TYPE_CANVAS_POLYGON )
            << get_defs( GNOME_TYPE_CANVAS_RE )
            << get_defs( GNOME_TYPE_CANVAS_RECT )
            << get_defs( GNOME_TYPE_CANVAS_ELLIPSE )
            << get_defs( GNOME_TYPE_CANVAS_RICH_TEXT )
            << get_defs( GNOME_TYPE_CANVAS_SHAPE )
            << get_defs( GNOME_TYPE_CANVAS_TEXT )
            << get_defs( GNOME_TYPE_CANVAS_WIDGET )
            << get_defs( GNOME_TYPE_CANVAS_ITEM )
            << get_defs( GNOME_TYPE_CANVAS_GROUP )
            << get_defs( GNOME_TYPE_CANVAS );
            //<< get_defs( GNOME_TYPE_CANVAS_POINTS );

  return 0;
}
