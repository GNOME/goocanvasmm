/*
#include <libglademm.h>
*/
#include "window.h"
#include "primitives.h"

DemoWindow::DemoWindow()
{
  set_title("goocanvasmm Demo") ;
  set_default_size(640, 600) ;

  _pages.push_back(new Primitives()) ;


  Gtk::Notebook* nb = Gtk::manage(new Gtk::Notebook());

  std::vector< Page* >::iterator iter ;
  for(iter = _pages.begin() ; iter != _pages.end() ; iter++)
  {
    Page* p = *iter ;
    nb->append_page(*(p->getWidget()), p->getName()) ;
  }

  add(*nb) ;
  show_all_children() ;
}

