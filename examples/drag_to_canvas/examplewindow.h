
#include <gtkmm.h>
#include <goocanvasmm.h>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();

protected:

  enum DragItem
  {
    DRAG_ITEM_NONE,
    DRAG_ITEM_RECTANGLE,
    DRAG_ITEM_ELLIPSE
  };

  void make_widget_draggable(Gtk::Widget& widget, DragItem drag_item);

  void on_button_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& drag_context, Gtk::SelectionData& selection_data, guint info, guint time, DragItem drag_item);
  bool on_canvas_drag_drop(const Glib::RefPtr<Gdk::DragContext>& drag_context, int x, int y, guint timestamp);
  bool on_canvas_drag_motion(const Glib::RefPtr<Gdk::DragContext>& drag_context, int x, int y, guint timestamp);
  void on_canvas_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& drag_context, int x, int y, const Gtk::SelectionData& selection_data, guint info, guint timestamp);

  Glib::RefPtr<Goocanvas::Item> create_canvas_item(DragItem drag_item, int x, int y);
  
  static DragItem get_drag_item_from_selection_data(const Gtk::SelectionData& selection_data);
  
  Goocanvas::Canvas m_canvas;

  Gtk::VBox m_vbox;
  Gtk::HBox m_hbox;
  Gtk::Button m_button_rect, m_button_ellipse;

  std::list<Gtk::TargetEntry> m_drag_targets;
  Glib::RefPtr<Goocanvas::Item> m_layout_item_dropping;
  bool m_drag_preview_requested;
};

