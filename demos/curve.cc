/* curve.cc
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

#include "curve.h"
#include <libgnomecanvasmm/rect.h>
#include <libgnomecanvasmm/text.h>
#include <gtkmm/frame.h>
#include <gtkmm/label.h>

Curve::Curve()
: Gtk::VBox(false, 4),
  m_current_state(STATE_INIT),
  m_points(4),
  m_current_item(NULL)
{
  set_border_width(4);

  Gtk::Label* label 
      = Gtk::manage(new Gtk::Label("Drag a line with button 1. Then mark 2 control points wth\n"
                              "button 1. Shift+click with button 1 to destroy the curve.\n"));
  
  pack_start(*label, Gtk::PACK_SHRINK);

  Gtk::Widget* canvas_frame = create_canvas(false);
  pack_start(*canvas_frame);

  Gtk::Widget* aa_canvas_frame = create_canvas(true);
  pack_start(*aa_canvas_frame);
}

Curve::~Curve()
{
}

Gtk::Widget*
Curve::create_canvas(bool aa)
{
  Gnome::Canvas::Canvas* canvas;
  if(aa == true) {
      canvas = Gtk::manage(new Gnome::Canvas::CanvasAA());
  } else {
      canvas = Gtk::manage(new Gnome::Canvas::Canvas());
  }
  
  canvas->set_size_request(600, 250);
  canvas->set_scroll_region(0, 0, 600, 250);

  Gnome::Canvas::Rect* rect 
      = Gtk::manage(new Gnome::Canvas::Rect(*canvas->root(), 
                                       0.0, 0.0, 
                                       600.0, 250.0));
  rect->property_outline_color() = "black";
  rect->property_fill_color() = "white";
  rect->signal_event().connect(sigc::bind(sigc::mem_fun(*this, &Curve::on_canvas_event), canvas));

  Gnome::Canvas::Text* text
      = Gtk::manage(new Gnome::Canvas::Text(*canvas->root(),
                                       270.0, 6.0,
                                       aa ? "AntiAlias" : "Non-AntiAlias"));
  text->property_font() = "Sans 12";
  text->property_anchor() = Gtk::ANCHOR_N;
  text->property_fill_color() = "black";

  Gtk::Frame* frame = Gtk::manage(new Gtk::Frame());
  frame->set_shadow_type(Gtk::SHADOW_IN);
  frame->add(*canvas);

  return frame;
}

bool
Curve::on_canvas_event(GdkEvent* event, Gnome::Canvas::Canvas* canvas)
{
  switch(event->type) {
  case GDK_BUTTON_PRESS:
    if(event->button.button != 1)
      break;
    
  switch(m_current_state) {
  case STATE_INIT:
    draw_curve(*canvas, event->button.x, event->button.y);
    m_current_state = STATE_FIRST_PRESS;
    break;
  case STATE_FIRST_RELEASE:
    draw_curve(*canvas, event->button.x, event->button.y);
    m_current_state = STATE_SECOND_PRESS;
    break;
  case STATE_SECOND_PRESS:
    draw_curve(*canvas, event->button.x, event->button.y);
    m_current_state = STATE_INIT;
    break;
  default:
    g_warning("shouldn't have reached here %d", m_current_state);
    break;
  }
  break;
  case GDK_BUTTON_RELEASE:
    if(event->button.button != 1)
      break;
      
    switch(m_current_state) {
    case STATE_FIRST_PRESS:
      draw_curve(*canvas, event->button.x, event->button.y);
      m_current_state = STATE_FIRST_RELEASE;
      break;
    default:
      break;
    }
    break;
  case GDK_MOTION_NOTIFY:
    switch(m_current_state) {
    case STATE_FIRST_PRESS:
      draw_curve(*canvas, event->motion.x, event->motion.y);
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
  
  return false;
}

bool
Curve::on_item_event(GdkEvent* event, Gnome::Canvas::Bpath* bpath)
{
  if(event->type == GDK_BUTTON_PRESS 
     && event->button.button == 1 
     && event->button.state & GDK_SHIFT_MASK) {
    delete bpath;
        
    if(bpath == m_current_item) {
      m_current_item = NULL;
      m_current_state = STATE_INIT;
    }
    
    return true;
  }
  
  return false;
}

void
Curve::draw_curve(Gnome::Canvas::Canvas& canvas, double x, double y)
{
  switch(m_current_state) {
  case STATE_INIT:
    m_points[0] = Gnome::Art::Point(x, y);
    break;
  case STATE_FIRST_PRESS: {
    m_points[1] = Gnome::Art::Point(x, y);
    
    Glib::RefPtr<Gnome::Canvas::PathDef> path 
        = Gnome::Canvas::PathDef::create();
    
    path->moveto(m_points[0].get_x(), m_points[0].get_y());
    path->lineto(m_points[1].get_x(), m_points[1].get_y());
    
    if(m_current_item == NULL) {
      m_current_item = Gtk::manage(new Gnome::Canvas::Bpath(*canvas.root()));
      m_current_item->property_outline_color() = "blue";
      m_current_item->property_width_pixels() = 5;
      m_current_item->property_cap_style() = Gdk::CAP_ROUND;
      
      m_current_item->signal_event()
          .connect(sigc::bind(sigc::mem_fun(*this, &Curve::on_item_event), m_current_item));
    }
    
    m_current_item->set_bpath(path);
    
    break;
  }
  case STATE_FIRST_RELEASE: {
    g_assert(m_current_item);
    
    m_points[2] = Gnome::Art::Point(x, y);
    
    Glib::RefPtr<Gnome::Canvas::PathDef> path 
        = Gnome::Canvas::PathDef::create();
    
    path->moveto(m_points[0].get_x(), m_points[0].get_y());
    path->curveto(m_points[2].get_x(), m_points[2].get_y(),
                  m_points[2].get_x(), m_points[2].get_y(),
                  m_points[1].get_x(), m_points[1].get_y());
    
    m_current_item->set_bpath(path);
    break;
  }
  case STATE_SECOND_PRESS: {
    g_assert(m_current_item);
    
    m_points[3] = Gnome::Art::Point(x, y);
    
    Glib::RefPtr<Gnome::Canvas::PathDef> path 
        = Gnome::Canvas::PathDef::create();
    
    path->moveto(m_points[0].get_x(), m_points[0].get_y());
    path->curveto(m_points[2].get_x(), m_points[2].get_y(),
                  m_points[3].get_x(), m_points[3].get_y(),
                  m_points[1].get_x(), m_points[1].get_y());
    
    m_current_item->set_bpath(path);
    
    m_current_item = NULL;
    break;
  }
  default:
    g_assert_not_reached();
    break;
  }
}
