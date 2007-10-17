/* features.cc
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

#include "canvas_features.h"



Features::Features()
: Gtk::VBox(false, 4)
{
  set_border_width(4);
  
  Gtk::Label* label 
      = Gtk::manage(new Gtk::Label("Reparent test:  click on the items to switch them between parents"));
  pack_start(*label, Gtk::PACK_SHRINK);
  
  Gtk::Alignment* alignment 
      = Gtk::manage(new Gtk::Alignment(0.5, 0.5, 0.0, 0.0));
  pack_start(*alignment, Gtk::PACK_SHRINK);
  
  Gtk::Frame* frame = Gtk::manage(new Gtk::Frame());
  frame->set_shadow_type(Gtk::SHADOW_IN);
  alignment->add(*frame);
  
  Gnome::Canvas::Canvas* canvas = Gtk::manage(new Gnome::Canvas::Canvas());
  canvas->set_size_request(400, 200);
  canvas->set_scroll_region(0, 0, 400, 200);
  frame->add(*canvas);
  
  m_parent1 = Gtk::manage(new Gnome::Canvas::Group(*canvas->root()));
  Gnome::Canvas::Rect* rect1 = Gtk::manage(new Gnome::Canvas::Rect(*m_parent1));
  rect1->property_x1() = 0.0;
  rect1->property_y1() = 0.0;
  rect1->property_x2() = 200.0;
  rect1->property_y2() = 200.0;
  rect1->property_fill_color() = "tan";
  
  m_parent2 = Gtk::manage(new Gnome::Canvas::Group(*canvas->root(),
                                              200.0, 0.0));
  Gnome::Canvas::Rect* rect2 = Gtk::manage(new Gnome::Canvas::Rect(*m_parent2));
  rect2->property_x1() = 0.0;
  rect2->property_y1() = 0.0;
  rect2->property_x2() = 200.0;
  rect2->property_y2() = 200.0;
  rect2->property_fill_color() = "#204060";
  
  
  Gnome::Canvas::Ellipse* ellipse1
      = Gtk::manage(new Gnome::Canvas::Ellipse(*m_parent1));
  ellipse1->property_x1() = 10.0;
  ellipse1->property_y1() = 10.0;
  ellipse1->property_x2() = 190.0;
  ellipse1->property_y2() = 190.0;
  ellipse1->property_outline_color() = "black";
  ellipse1->property_fill_color() = "mediumseagreen";
  ellipse1->property_width_units() = 3.0;
  ellipse1->signal_event()
      .connect(sigc::bind(sigc::mem_fun(*this, &Features::on_item_event), ellipse1));


  Gnome::Canvas::Group* group
      = Gtk::manage(new Gnome::Canvas::Group(*m_parent2, 100.0, 100.0));
  group->signal_event()
      .connect(sigc::bind(sigc::mem_fun(*this, &Features::on_item_event), group));
  Gnome::Canvas::Ellipse* ellipse2
      = Gtk::manage(new Gnome::Canvas::Ellipse(*group));
  ellipse2->property_x1() = -50.0;
  ellipse2->property_y1() = -50.0;
  ellipse2->property_x2() = 50.0;
  ellipse2->property_y2() = 50.0;
  ellipse2->property_outline_color() = "black";
  ellipse2->property_fill_color() = "wheat";
  ellipse2->property_width_units() = 3.0;
  Gnome::Canvas::Ellipse* ellipse3
      = Gtk::manage(new Gnome::Canvas::Ellipse(*group));
  ellipse3->property_x1() = -25.0;
  ellipse3->property_y1() = -25.0;
  ellipse3->property_x2() = 25.0;
  ellipse3->property_y2() = 25.0;
  ellipse3->property_fill_color() = "steelblue";
}


Features::~Features()
{
}


bool
Features::on_item_event(GdkEvent* event,
                        Gnome::Canvas::Item* item)
{
  if((event->type != GDK_BUTTON_PRESS) ||(event->button.button != 1)) {
      return false;
  }
  
  if(item->get_parent_group() == m_parent1) {
      item->reparent(*m_parent2);
  } else {
      item->reparent(*m_parent1);
  }
  
  return true;
}
