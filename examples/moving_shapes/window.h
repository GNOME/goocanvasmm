
#include <gtkmm.h>
#include <goocanvasmm.h>

class Window : public Gtk::Window
{
public:
  Window() ;

private:

  Goocanvas::Canvas* _canvas ;

  Glib::RefPtr< Goocanvas::Item > _dragging ;
  int _drag_x ;
  int _drag_y ;

  void on_item_created(const Glib::RefPtr<Goocanvas::Item>& item, const Glib::RefPtr<Goocanvas::ItemModel>& model) ;
  bool on_item_button_press_event(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventButton* event) ;
  bool on_item_button_release_event(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventButton* event) ;
  bool on_item_motion_notify_event(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventMotion* event) ;
/*
  bool on_focus_in_event(const Glib::RefPtr<Goocanvas::Item>& view, GdkEventFocus* event) ;
  bool on_focus_out_event(const Glib::RefPtr<Goocanvas::Item>& view, GdkEventFocus* event) ;
*/
};

