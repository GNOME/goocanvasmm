
#include <gtkmm.h>
#include <goocanvasmm.h>

class SimpleWindow : public Gtk::Window
{
public:
  SimpleWindow() ;

private:

  Goocanvas::Canvas* _canvas ;
  Glib::RefPtr<Goocanvas::Rect> _rect ;

  bool on_rect_button_press(const Glib::RefPtr<Goocanvas::Item>& target, GdkEventButton* event);
};

