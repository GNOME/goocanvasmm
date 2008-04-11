
#include <gtkmm.h>
#include <goocanvasmm.h>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow() ;

protected:

  void add_text_to_cell(const Glib::RefPtr<Goocanvas::TableModel>&, const Glib::ustring& text, guint row, guint col);

  //bool on_rect_button_press(const Glib::RefPtr<Goocanvas::ItemModel>& target, GdkEventButton* event);
  
  Goocanvas::Canvas m_first_canvas;
  Goocanvas::Canvas m_second_canvas;
  Glib::RefPtr<Goocanvas::TableModel> m_table;
};

