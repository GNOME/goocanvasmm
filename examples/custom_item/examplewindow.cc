#include "examplewindow.h"
#include <cairomm/cairomm.h>
#include <iostream>

ExampleWindow::ExampleWindow()
{
  set_title("goocanvasmm - Custom Item Example");

  m_canvas.set_size_request(640, 480);
  m_canvas.set_bounds(0, 0, 1000, 1000);


  Glib::RefPtr<ExampleItem> item = ExampleItem::create(100, 100, 400, 400);
  item->property_line_width().set_value(10.0);
  item->property_stroke_color().set_value("yellow");
  item->property_fill_color().set_value("red");

  Glib::RefPtr<Goocanvas::Item> root = m_canvas.get_root_item();
  root->add_child(item);

  Gtk::ScrolledWindow* sw = Gtk::manage(new Gtk::ScrolledWindow());
  sw->add(m_canvas);
  add(*sw);

  show_all_children();
}

