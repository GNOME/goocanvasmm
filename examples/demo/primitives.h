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

#ifndef PRIMITIVES_HH
#define PRIMITIVES_HH

#include <gtkmm.h>
#include <goocanvasmm.h>
#include "page.h"

class Primitives : public Page
{
public:
  Primitives();

  const Glib::ustring&
  getName() override;

  Gtk::Widget*
  getWidget() override;

private:

  bool      _on_background_button_press(const Glib::RefPtr<Goocanvas::Item>& item, Gdk::EventButton& ev);
  bool      _on_button_press(const Glib::RefPtr<Goocanvas::Item>& item, Gdk::EventButton& ev);
  bool      _on_button_release(const Glib::RefPtr<Goocanvas::Item>& item, Gdk::EventButton& ev);
  bool      _on_motion_notify(const Glib::RefPtr<Goocanvas::Item>& item, Gdk::EventMotion& ev);

  void      _setup_signals(const Glib::RefPtr<Goocanvas::Item>& item);
  void      _setup_heading(const Glib::ustring& heading, int pos);
  void      _setup_divisions();
  void      _setup_rectangles();
  void      _setup_ellipses();
  void      _setup_texts();
  void      _setup_images();
  void      _setup_lines();

  Cairo::RefPtr<Cairo::Pattern>
        _create_stipple(const Glib::ustring& color);

  Glib::RefPtr<Goocanvas::Item>
        _create_anchor(double x, double y);

  void      _create_flower(double x, double y, Goocanvas::AnchorType anchor);
  void      _create_polish_diamond();
  void      _create_hilbert();

  Glib::ustring    _name ;
  Gtk::Box*    _vbox ;
  Gtk::RadioButtonGroup  _rbg ;
  Goocanvas::Canvas*  _canvas ;
  Gtk::ScrolledWindow*  _scrolled_window ;
};

#endif /* Included primitives.h */
