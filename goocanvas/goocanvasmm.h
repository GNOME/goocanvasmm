/* $Id: goocanvasmm.h,v 1.4 2005/08/23 15:43:32 murrayc Exp $ */
/* goocanvasmm - a C++ wrapper for libgoocanvas
 *
 * Copyright 1999-2001 Free Software Foundation
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

#ifndef LIBGOOCANVASMM_H
#define LIBGOOCANVASMM_H

//extern "C" {
//#include <gtk/gtk.h>
//}

/* goocanvasmm version.  */
extern const int goocanvasmm_major_version;
extern const int goocanvasmm_minor_version;
extern const int goocanvasmm_micro_version;

#include <glibmm.h>

#include <goocanvasmm/bounds.h>
#include <goocanvasmm/canvas.h>
#include <goocanvasmm/ellipse.h>
#include <goocanvasmm/ellipsemodel.h>
#include <goocanvasmm/enums.h>
#include <goocanvasmm/group.h>
#include <goocanvasmm/groupmodel.h>
#include <goocanvasmm/image.h>
#include <goocanvasmm/imagemodel.h>
#include <goocanvasmm/init.h>
#include <goocanvasmm/item.h>
#include <goocanvasmm/itemmodel.h>
#include <goocanvasmm/itemmodelsimple.h>
#include <goocanvasmm/itemsimple.h>
#include <goocanvasmm/linedash.h>
#include <goocanvasmm/path.h>
#include <goocanvasmm/pathmodel.h>
#include <goocanvasmm/points.h>
#include <goocanvasmm/polyline.h>
#include <goocanvasmm/polylinemodel.h>
#include <goocanvasmm/rect.h>
#include <goocanvasmm/rectmodel.h>
#include <goocanvasmm/style.h>
#include <goocanvasmm/table.h>
#include <goocanvasmm/tablemodel.h>
#include <goocanvasmm/text.h>
#include <goocanvasmm/textmodel.h>
#include <goocanvasmm/types.h>
#include <goocanvasmm/widget.h>

#endif /* #ifndef LIBGOOCANVASMM_H */
