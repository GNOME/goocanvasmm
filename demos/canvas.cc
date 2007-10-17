/* canvas.cc
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

#include <libgnomecanvasmm/init.h>
#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include <gtkmm/notebook.h>

#include "primitives.h"
#include "canvas_features.h"
#include "fifteen.h"
#include "arrowhead.h"
#include "richtext.h"
#include "curve.h"

class MainWin : public Gtk::Window
{
public:
  MainWin();

protected:
};

MainWin::MainWin()
{
  Gtk::Notebook* notebook = Gtk::manage(new Gtk::Notebook());
  add(*notebook);
  
  Primitives* primitives = Gtk::manage(new Primitives(false));
  notebook->append_page(*primitives, "Primitives");    
  Primitives* antialias = Gtk::manage(new Primitives(true));
  notebook->append_page(*antialias, "Antialias");    
  Arrowhead* arrowhead = Gtk::manage(new Arrowhead());
  notebook->append_page(*arrowhead, "Arrowhead");    
  Fifteen* fifteen = Gtk::manage(new Fifteen());
  notebook->append_page(*fifteen, "Fifteen");
  Features* features = Gtk::manage(new Features());
  notebook->append_page(*features, "Features");
  Richtext* richtext = Gtk::manage(new Richtext());
  notebook->append_page(*richtext, "Rich Text");
  Curve* curve = Gtk::manage(new Curve());
  notebook->append_page(*curve, "Bezier Curve");
  
  show_all();
}


int 
main(int argc, char* argv[])
{
  Gnome::Canvas::init();
  Gtk::Main app(argc, argv);
  
  MainWin mainwin;
  app.run(mainwin);
  
  return 0;
}
