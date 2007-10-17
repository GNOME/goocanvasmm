/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Author:  Paul Davis pjdavis@engineering.uiowa.edu
 * Copyright: University of Iowa 2006
 * FileInfo:  $Id$
 *
 */

#ifndef PAGE_HH
#define PAGE_HH

class Page
{
public:

  virtual ~Page() {}

  virtual const Glib::ustring&
  getName() = 0 ;

  virtual Gtk::Widget*
  getWidget() = 0 ;
};

#endif /* Included page.h */

