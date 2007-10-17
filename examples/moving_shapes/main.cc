
#include "window.h"

int
main(int argc, char* argv[])
{
  Gtk::Main app(&argc, &argv) ;
  Goocanvas::init("goocanvasmm Simple Example", "0.1", argc, argv) ;

  Window w ;
  Gtk::Main::run(w) ;
}



