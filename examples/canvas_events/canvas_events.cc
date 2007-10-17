// CanvasEvents.cc
// This program tries to sample the event handling inside the canvas
// (c) Agustin Ferrin Pozuelo <ferrin@arrakis.es>
// Note that you have to click 2^N times over the canvas,
// It took me 5.60 seconds to have 64 valid events! I'm Termclickator

#include <libgnomecanvasmm.h>
#include <gtkmm/window.h>
#include <gtkmm/main.h>
#include <gdkmm/color.h>
#include <gdkmm/colormap.h>
#include <stdio.h>


guint32 etime = 0;
guint  status = 0;
enum someEnum
{
  CE = 0,
  CEA = 1,
  CBE = 2,
  IE = 3,
  IEA = 4,
  CBEA = 5,
  N = 6
};

enum { ENDING_STATUS = (1<<N) };

gchar record[N+1], stmask[N+1];

gchar* cname[N] = {"canvas_event","canvas_event_after"
    ,"canvas_button_press_event"
    ,"item_button_press_event","item_button_press_event_after"
    ,"canvas_button_press_event_after"};


class CanvasExample : public Gnome::Canvas::Canvas
{
public:
  CanvasExample();
  virtual ~CanvasExample();

protected:
  void on_event_explorer_notify(GdkEvent* e, someEnum caller);
  void on_button_event_stub_notify(GdkEventButton* e, someEnum caller);
  bool on_button_event_stub(GdkEventButton* e, someEnum caller);

private:
  bool on_event_explorer(GdkEvent* e, someEnum caller);
  Gnome::Canvas::Group m_canvasgroup;
};

CanvasExample::CanvasExample()
  : m_canvasgroup(*(root()), 0, 0)
{
  Gdk::Color redColor("red");
  Gdk::Color blackColor("black");
  get_colormap()->alloc_color(redColor);
  get_colormap()->alloc_color(blackColor);

  Gnome::Canvas::Ellipse* item = Gtk::manage(new Gnome::Canvas::Ellipse(
            m_canvasgroup,
            (gdouble) -100, (gdouble) -100,
            (gdouble) 100, (gdouble) 100) );
  *item << Gnome::Canvas::Properties::fill_color(blackColor);

  Gnome::Canvas::Ellipse* item2 = Gtk::manage(new Gnome::Canvas::Ellipse(
             m_canvasgroup,
             (gdouble) -50, (gdouble) -50,
             (gdouble) 50, (gdouble) 50) );
  *item2 << Gnome::Canvas::Properties::fill_color(redColor);

  //Connect canvas signals:

  signal_event().connect_notify( sigc::bind(sigc::mem_fun(*this, &CanvasExample::on_event_explorer_notify), CE) );
  signal_button_press_event().connect_notify(sigc::bind(sigc::mem_fun(*this, &CanvasExample::on_button_event_stub_notify),CBE));
  signal_button_press_event().connect(sigc::bind(sigc::mem_fun(*this, &CanvasExample::on_button_event_stub),CBEA));

  item->signal_event().connect_notify(sigc::bind(sigc::mem_fun(*this, &CanvasExample::on_event_explorer_notify),IE));
  item->signal_event().connect(sigc::bind(sigc::mem_fun(*this, &CanvasExample::on_event_explorer),IEA));

  item2->signal_event().connect_notify(sigc::bind(sigc::mem_fun(*this, &CanvasExample::on_event_explorer_notify),IE));
  item2->signal_event().connect(sigc::bind(sigc::mem_fun(*this, &CanvasExample::on_event_explorer),IEA));
}

CanvasExample::~CanvasExample()
{
}

bool
CanvasExample::on_event_explorer(GdkEvent* e, someEnum caller)
{
  GdkEventButton* b;
  // Ignore all but button-press events:
  if(e->type != GDK_BUTTON_PRESS)
    return TRUE;

  b = &(e->button);
  if(b->time != etime) // if new event
  {
    gint i;
    if(etime != 0) // if not first, inc status and show last record
    {
      for(i = 0; i < N; i++)
        stmask[i]= (status & (1<<i)) ? '1': '0';
        
      stmask[N] = 0;
      printf("  Event mask / Events reached %s/%s\n", stmask, record);
      
      if((++status) >= ENDING_STATUS)
        exit(0);
    }

    for(i = 0; i < N; i++)
      record[i] = '0';
      
    record[N] = 0;
    etime = b->time;
    printf("New event (%u) at time %X\n", status, (guint)etime);
  }

  record[caller] = '1';
  printf("  %-30s() is returning ", cname[caller]);
  
  if(status & (1 << caller))
  {
    printf("TRUE\n");
    return true;
  }
  else
  {
    printf("FALSE\n");
    return false;
  }
}

void
CanvasExample::on_event_explorer_notify(GdkEvent* e, someEnum caller)
{
  std::cerr << "on_event_explorer_notify" << std::endl;
}

bool
CanvasExample::on_button_event_stub(GdkEventButton* b, someEnum caller)
{
  return on_event_explorer((GdkEvent *) b, caller);
}

void
CanvasExample::on_button_event_stub_notify(GdkEventButton* b, someEnum caller)
{
  std::cerr << "on_button_event_stub_notify" << std::endl;
}

class MainWindow: public Gtk::Window
{
public:
  MainWindow(const std::string& title) {
    set_title(title);
    add(m_canvas);
    show_all();
  }
private:
  CanvasExample m_canvas;
};

int main(int argc, char* argv[])
{
  
  Gnome::Canvas::init();
  Gtk::Main canvasmain(argc, argv);
  
  MainWindow window("Gnome::Canvas event example");
  canvasmain.run(window);
  
  return 0;
}

