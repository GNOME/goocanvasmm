
#ifndef WINDOW_HH
#define WINDOW_HH

#include <gtkmm.h>
#include <goocanvasmm.h>
#include "page.h"

class DemoWindow : public Gtk::Window
{
public:

  DemoWindow() ;

private:

  std::vector< Page* >  _pages ;
};

#endif /* Included window.h */


