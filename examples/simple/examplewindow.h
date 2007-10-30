
#include <gtkmm.h>
#include <goocanvasmm.h>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow() ;

protected:

  Goocanvas::Canvas m_canvas;
  Glib::RefPtr<Goocanvas::Rect> m_table;

  bool on_rect_button_press(const Glib::RefPtr<Goocanvas::Item>& target, GdkEventButton* event);
};

