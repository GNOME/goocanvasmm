
#include <gtkmm.h>
#include <goocanvasmm.h>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow() ;

protected:

  void add_text_to_cell(const Glib::RefPtr<Goocanvas::Table>&, const Glib::ustring& text, guint row, guint col);

  bool on_rect_button_press(const Glib::RefPtr<Goocanvas::Item>& target, GdkEventButton* event);
  
  Goocanvas::Canvas m_canvas;
  Glib::RefPtr<Goocanvas::Table> m_table;
};

