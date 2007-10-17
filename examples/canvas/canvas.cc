// This example was started by Guillaume Laurent.
// It has become a place to dump code that tests parts of the
// gnomemm canvas code. Little thought has been given to the
// actual on-screen output.

#include <libgnomecanvasmm.h>

class MyCanvasLine : public Gnome::Canvas::Line
{
public:
  MyCanvasLine(Gnome::Canvas::Group& parentx)
  : Gnome::Canvas::Line(parentx)
  {
    std::cout << "debug: MyCanvasLine constructor 1." << std::endl;
  }

  MyCanvasLine(Gnome::Canvas::Group& parentx, const Gnome::Canvas::Points& points)
  : Gnome::Canvas::Line(parentx, points)
  {
    std::cout << "debug: MyCanvasLine constructor 2." << std::endl;
  }

  ~MyCanvasLine()
  {
    std::cout << "debug: MyCanvasLine destructor." << std::endl;
  }
};

class CanvasExample : public Gnome::Canvas::CanvasAA
{
public:
  CanvasExample();
  virtual ~CanvasExample();

protected:
  Gnome::Canvas::Group m_canvasgroup;
  MyCanvasLine *m_line;
  Gnome::Canvas::Ellipse *m_ellipse;
  Gnome::Canvas::Rect *m_rect;
  //  Gnome::Canvas::Image *m_image;
  Gnome::Canvas::Text *m_text;
};

CanvasExample::CanvasExample()
  : m_canvasgroup(*(root()), 0, 0)
{
  // create some elements there
  Gnome::Canvas::Points m_points;

  m_points.push_back(Gnome::Art::Point(0, 0));
  m_points.push_back(Gnome::Art::Point(100, 0));
  m_points.push_back(Gnome::Art::Point(0, 100));
  m_points.push_back(Gnome::Art::Point(100, 100));

  // we want to use the stream like interface
  using namespace Gnome::Canvas;

  m_line = Gtk::manage( new MyCanvasLine(m_canvasgroup, m_points) );
  *m_line << Properties::fill_color("red")
          << Properties::width_units(4.0)
          << Properties::cap_style(Gdk::CAP_ROUND);

  m_ellipse = new Gnome::Canvas::Ellipse(m_canvasgroup, 0, 0, 100, 100);
  *m_ellipse << Properties::fill_color("blue");

  m_rect = new Gnome::Canvas::Rect(m_canvasgroup, 10, 10, 50, 100);
  *m_rect << Properties::width_pixels(2)
          << Properties::fill_color("white");

  //m_image = new Gnome::Canvas::Image(m_canvasgroup, 0, 0, Gdk_Imlib::Image("example.png"));
  //The width and height are set from the information in the image file.

  m_text = new Gnome::Canvas::Text(m_canvasgroup, 10, 10, "Some Text");
  *m_text << Properties::font("-Adobe-Helvetica-Medium-R-Normal--*-100-*-*-*-*-*-*")
          << Properties::fill_color("blue"); //Changes the color of the text.
}

CanvasExample::~CanvasExample()
{
  //delete m_line;
  delete m_ellipse;
  delete m_rect;
//  delete m_image;
  delete m_text;
}


//MainWin:

class MainWin : public Gtk::Window
{
public:
  MainWin(const std::string& title);

protected:
  //Member widgets:
  CanvasExample m_canvas;
};

MainWin::MainWin(const std::string& title)
{
  set_title (title);
  add(m_canvas);

  show_all();
}

//main():

int main(int argc, char *argv[])
{
  Gnome::Canvas::init();
  Gtk::Main app(argc, argv);

  MainWin mainwin("Gnome::Canvas Example");
  app.run(mainwin);

  return 0;
}
