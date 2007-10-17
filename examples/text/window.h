/* example Copyright (C) 2007 goocanvasmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include <gtkmm.h>
#include <goocanvasmm.h>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();

private:
  void on_button_translate();
  void on_button_setxy();
  void on_button_scale();
  void on_button_zoom_canvas();
  void on_button_set_width();
  void on_button_set_width_unlimited();

  void update_label();

  Goocanvas::Canvas m_canvas;
  Glib::RefPtr<Goocanvas::Text> m_text;

  Gtk::VBox m_box;
  Gtk::HBox m_button_box1, m_button_box2;
  Gtk::Label m_label_origin, m_label_status;
  Gtk::Button m_button_translate, m_button_scale, m_button_setxy, m_button_zoom;
  Gtk::Button m_button_set_width, m_button_set_width_unlimited;
};

