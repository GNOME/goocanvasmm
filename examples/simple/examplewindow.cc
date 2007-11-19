#include "examplewindow.h"
#include <cairomm/cairomm.h>
#include <iostream>

ExampleWindow::ExampleWindow()
{
  set_title("goocanvasmm - Simple Example");

  m_canvas.set_size_request(640, 480);
  m_canvas.set_bounds(0, 0, 1000, 1000);

  Glib::RefPtr<Goocanvas::Item> root = m_canvas.get_root_item();
  Glib::RefPtr<Goocanvas::Rect> rect = Goocanvas::Rect::create(100, 100, 400, 400);
  root->add_child(rect);
  rect->property_line_width().set_value(10.0);
  rect->property_radius_x().set_value(20.0);
  rect->property_radius_y().set_value(20.0);
  rect->property_stroke_color().set_value("yellow");
  rect->property_fill_color().set_value("red");

  Glib::RefPtr<Goocanvas::Text> text = Goocanvas::Text::create("Hello World", 300, 300, -1, Gtk::ANCHOR_CENTER);
  root->add_child(text);
  text->property_font().set_value("Sans 24");
  text->rotate(45, 300, 300);

  Gtk::ScrolledWindow* sw = Gtk::manage(new Gtk::ScrolledWindow());
  sw->add(m_canvas);
  add(*sw);

  show_all_children();
}

bool
ExampleWindow::on_rect_button_press(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventButton* event)
{
  std::cout << "You clicked the rectangle!" << std::endl ;
  return true ;
}

