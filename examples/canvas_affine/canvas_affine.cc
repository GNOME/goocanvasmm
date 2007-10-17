// CanvasAffine.cc
// Sample use of the Gnome::Art::Affine and Gnome::Art::Point classes
// (c) Agustin Ferrin Pozuelo <ferrin@arrakis.es>

#include <libgnomecanvasmm.h>
#include <gtkmm/window.h>
#include <gtkmm/main.h>

Gnome::Canvas::Line* some_lines(Gnome::Canvas::Group *group, gchar * color="black")
{
  using namespace Gnome::Art;
	
  // create some elements there
  Gnome::Canvas::Points points;
  points.push_back(Point(0, 0));
  points.push_back(Point(0, -10));
  points.push_back(Point(-5, -15));
  points.push_back(Point(0,-20));
  points.push_back(Point(5, -15));
  points.push_back(Point(0, -10));
	
  Gnome::Canvas::Line* line = Gtk::manage(new Gnome::Canvas::Line(*group, points));
  *line << Gnome::Canvas::Properties::fill_color(color);
 
  return line;
}

int main(int argc, char* argv[])
{
  using namespace Gnome::Art;
	
  Gnome::Canvas::init();
  Gtk::Main canvasmain(argc, argv);
  
  Gtk::Window window;
	
  Gnome::Canvas::Canvas *canvas = Gtk::manage(new Gnome::Canvas::Canvas());
  window.set_default_size(600, 500);
  window.add(*canvas);
  window.show_all();

  // First, something nice
  for(int i=0; i<12; i++)
  {
    Gnome::Canvas::Line* line = some_lines(canvas->root(), "black");
    AffineTrans tx  =AffineTrans::scaling((10.0 + i) / 3)
										* AffineTrans::rotation(i * 30);
    line->affine_absolute(tx);
    line->move(-100, -100);
  }
	
  // Next, let's see Affine are not conmutative
  for(int i=0; i<12; i++)
  {
    Gnome::Canvas::Line* line = some_lines(canvas->root(), "blue");
		
    // Translating then rotating then scaling...
    AffineTrans tx = AffineTrans::translation(5, 0)
      * AffineTrans::rotation(i * 30)
      * AffineTrans::scaling((10.0 +i ) / 3);

    line->affine_absolute(tx);
    line->move(-100, 100);
  }
	
  for(int i=0; i<12; i++)
  {
    Gnome::Canvas::Line* line = some_lines(canvas->root(), "red");
		
    // Isn't the same as scaling then translating then rotating!
    AffineTrans tx = AffineTrans::scaling((10.0 + i) / 3)
      * AffineTrans::translation(5, 0)
      * AffineTrans::rotation(i * 30);

    line->affine_absolute(tx);
    line->move(100, 100);
  }

  canvasmain.run(window);
  return 0;
}


