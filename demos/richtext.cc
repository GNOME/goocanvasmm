/* richtext.cc
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

#include "richtext.h"
#include <libgnomecanvasmm/canvas.h>
#include <libgnomecanvasmm/rect.h>
#include <libgnomecanvasmm/ellipse.h>
#include <libgnomecanvasmm/rich-text.h>
#include <gtkmm/frame.h>
#include <gtkmm/alignment.h>


Richtext::Richtext()
: Gtk::VBox(false, 4)
{
  set_border_width(4);

  Gtk::Alignment* alignment 
      = manage(new Gtk::Alignment(0.5, 0.5, 0.0, 0.0));
  pack_start(*alignment);
  
  Gtk::Frame* frame = manage(new Gtk::Frame());
  frame->set_shadow_type(Gtk::SHADOW_IN);
  alignment->add(*frame);
  
  Gnome::Canvas::Canvas* canvas = manage(new Gnome::Canvas::Canvas());
  canvas->set_size_request(600, 450);
  frame->add(*canvas);
  
  Gnome::Canvas::Rect* rect 
      = manage(new Gnome::Canvas::Rect(*canvas->root(),
                                       -90.0, -50.0, 110.0, 50.0));
  rect->property_fill_color() = "green";
  rect->property_outline_color() = "green";
  
  Gnome::Canvas::RichText* text
      = manage(new Gnome::Canvas::RichText(*canvas->root(),
                                           -90.0, -50.0,
                                           "English is so boring because everyone uses it.\n"
                                           "Here is something exciting:  "
                                           "وقد بدأ ثلاث من أكثر المؤسسات تقدما في شبكة اكسيون برامجها كمنظمات لا تسعى للربح، ثم تحولت في السنوات الخمس الماضية إلى مؤسسات مالية منظمة، وباتت جزءا من النظام المالي في بلدانها، ولكنها تتخصص في خدمة قطاع المشروعات الصغيرة. وأحد أكثر هذه المؤسسات نجاحا هو »بانكوسول« في بوليفيا.\n"
                                           "And here is some more plain, boring English."));
  text->property_width() = 200.0;
  text->property_height() = 100.0;
  text->property_grow_height() = true;
  
  Gnome::Canvas::Ellipse* ellipse 
      = manage(new Gnome::Canvas::Ellipse(*canvas->root(),
                                          -5.0, -5.0, 5.0, 5.0));
  ellipse->property_fill_color() = "white";
  
  
  rect = manage(new Gnome::Canvas::Rect(*canvas->root(),
                                        100.0, -30.0, 200.0, 30.0));
  rect->property_fill_color() = "yellow";
  rect->property_outline_color() = "yellow";
  
  text = manage(new Gnome::Canvas::RichText(*canvas->root(),
                                            100.0, -30.0,
                                            "The quick brown fox jumped over the lazy dog.\n"));
  text->property_width() = 100.0;
  text->property_height() = 60.0;
  text->property_cursor_visible() = true;
  text->property_cursor_blink() = true;
  text->property_grow_height() = true;
  
  rect = manage(new Gnome::Canvas::Rect(*canvas->root(),
                                        50.0, 70.0, 150.0, 100.0));
  rect->property_fill_color() = "pink";
  rect->property_outline_color() = "pink";
  
  text = manage(new Gnome::Canvas::RichText(*canvas->root(),
                                            50.0, 70.0,
                                            "This is a test.\nI enjoy tests a great deal\nThree lines!"));
  text->property_width() = 100.0;
  text->property_height() = 30.0;
  text->property_cursor_visible() = true;
  text->property_cursor_blink() = true;
}


Richtext::~Richtext()
{
}
