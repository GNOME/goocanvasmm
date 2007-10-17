/* fifteen.cc
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

#include "fifteen.h"

#include <stdio.h>


#define PIECE_SIZE 50

Fifteen::Fifteen()
: Gtk::VBox(false, 4)
{
  set_border_width(4);
  
  Gtk::Alignment* alignment 
      = Gtk::manage(new Gtk::Alignment(0.5, 0.5, 0.0, 0.0));
  pack_start(*alignment);
  
  Gtk::Frame* frame = Gtk::manage(new Gtk::Frame());
  frame->set_shadow_type(Gtk::SHADOW_IN);
  alignment->add(*frame);
  
  m_canvas = Gtk::manage(new Gnome::Canvas::Canvas());
  m_canvas->set_size_request(PIECE_SIZE * 4 + 1, PIECE_SIZE * 4 + 1);
  m_canvas->set_scroll_region(0, 0, PIECE_SIZE * 4 + 1, PIECE_SIZE * 4 + 1);
  frame->add(*m_canvas);
  
  for(int i = 0; i < 15; ++i) {
      int y = i / 4;
      int x = i % 4;
      
      m_board.push_back(Gtk::manage(new Gnome::Canvas::Group(*m_canvas
                                                        ->root(),
                                                        x * PIECE_SIZE,
                                                        y * PIECE_SIZE)));
      Gnome::Canvas::Rect* rect 
          = Gtk::manage(new Gnome::Canvas::Rect(*m_board.back(),
                                           0.0, 0.0,
                                           PIECE_SIZE, 
                                           PIECE_SIZE));
      rect->property_fill_color() = get_piece_color(i);
      rect->property_outline_color() = "black";
      rect->property_width_pixels() = 0;
      
      char buf[20];
      sprintf(buf, "%d", i + 1);
      
      Gnome::Canvas::Text* text 
          = Gtk::manage(new Gnome::Canvas::Text(*m_board.back(),
                                           PIECE_SIZE / 2.0,
                                           PIECE_SIZE / 2.0,
                                           buf));
      text->property_font() = "Sans bold 24";
      text->property_anchor() = Gtk::ANCHOR_CENTER;
      text->property_fill_color() = "black";
      
      m_board.back()->signal_event()
          .connect(sigc::bind(sigc::mem_fun(*this, &Fifteen::on_piece_event),
                        m_board.back(),
                        text));
  }
  m_board.push_back(NULL);

  Gtk::Button* button = Gtk::manage(new Gtk::Button("Scramble"));
  button->signal_clicked().connect(sigc::mem_fun(*this, &Fifteen::on_scramble));
  pack_start(*button, Gtk::PACK_SHRINK);
}


Fifteen::~Fifteen()
{
}


Glib::ustring
Fifteen::get_piece_color(int piece)
{
  static char buf[50];
  
  int y = piece / 4;
  int x = piece % 4;
  
  int r =((4 - x) * 255) / 4;
  int g =((4 - y) * 255) / 4;
  int b = 128;
  
  sprintf(buf, "#%02x%02x%02x", r, g, b);
  
  return buf;
}


#define SCRAMBLE_MOVES 256

void
Fifteen::on_scramble(void)
{
  srand(time(NULL));
  
  // First, find the blank spot 
  
  int pos;
  for(pos = 0; pos < 16; ++pos) {
      if(m_board[pos] == NULL) {
          break;
      }
  }
  
  // "Move the blank spot" around in order to scramble the pieces 
  
  for(int i = 0; i < SCRAMBLE_MOVES; ++i) {
  retry_scramble:
      int dir = rand() % 4;
      
      int x = 0;
      int y = 0;
      
      if((dir == 0) &&(pos > 3)) { // up 
          y = -1;
      } else if((dir == 1) &&(pos < 12)) { // down 
          y = 1;
      } else if((dir == 2) &&((pos % 4) != 0)) { // left 
          x = -1;
      } else if((dir == 3) &&((pos % 4) != 3)) { // right
          x = 1;
      } else {
          goto retry_scramble;
      }
      
      int oldpos = pos + y * 4 + x;
      m_board[pos] = m_board[oldpos];
      m_board[oldpos] = NULL;
      m_board[pos]->move(-x * PIECE_SIZE, -y * PIECE_SIZE);
      m_canvas->update_now();
      pos = oldpos;
  }
}


bool
Fifteen::on_piece_event(GdkEvent *event,
                        Gnome::Canvas::Group* item,
                        Gnome::Canvas::Text* text)
{
  int pos = 0;
  for(pos = 0; pos < 16; ++pos) {
      if(m_board[pos] == item) {
          break;
      }
  }
  
  switch(event->type) {
  case GDK_ENTER_NOTIFY:
      text->property_fill_color() = "white";
      break;
      
  case GDK_LEAVE_NOTIFY:
      text->property_fill_color() = "black";
      break;
      
  case GDK_BUTTON_PRESS: {
      int y = pos / 4;
      int x = pos % 4;
      double dx = 0.0;
      double dy = 0.0;
      
      bool move = true;
      
      if((y > 0) &&(m_board[(y - 1) * 4 + x] == NULL)) {
          dx = 0.0;
          dy = -1.0;
          y--;
      } else if((y < 3) &&(m_board[(y + 1) * 4 + x] == NULL)) {
          dx = 0.0;
          dy = 1.0;
          y++;
      } else if((x > 0) &&(m_board[y * 4 + x - 1] == NULL)) {
          dx = -1.0;
          dy = 0.0;
          x--;
      } else if((x < 3) &&(m_board[y * 4 + x + 1] == NULL)) {
          dx = 1.0;
          dy = 0.0;
          x++;
      } else {
          move = true;
      }
      
      if(move == true) {
          int newpos = y * 4 + x;
          m_board[pos] = NULL;
          m_board[newpos] = item;
          item->move(dx * PIECE_SIZE, dy * PIECE_SIZE);
      }
      
      break;
      
  }        
  default:
      break;
  }
  
  return false;
}
