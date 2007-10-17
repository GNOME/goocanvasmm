_CONVERSION(`GnomeCanvas*',`Canvas*',`Glib::wrap($3)')
_CONVERSION(`GnomeCanvasItem*',`Item*',`Glib::wrap($3)')
_CONVERSION(`GnomeCanvasGroup*',`Group*',`Glib::wrap($3)')
_CONVERSION(`GnomeCanvasItem*',`Group*',`Glib::wrap(GNOME_CANVAS_GROUP($3))')
_CONVERSION(`Group&',`GnomeCanvasGroup*',`($3).gobj()')
_CONVERSION(`GnomeCanvasPathDef*',`Glib::RefPtr<PathDef>',`Glib::wrap($3)')

_CONVERSION(`Gtk::TextIter&',`GtkTextIter*',__FR2P)
_CONVERSION(`const Gtk::TextIter&',`const GtkTextIter*',__FR2P)
_CONVERSION(`GtkTextBuffer*',`Glib::RefPtr<Gtk::TextBuffer>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Gtk::TextBuffer>&',`GtkTextBuffer*',__CONVERT_REFPTR_TO_P)
_CONVERSION(`ArtBPath&',`ArtBPath*',`&($3)')

# Used by Signals:
_CONVERSION(`GdkDrawable*',`const Glib::RefPtr<Gdk::Drawable>&',`Glib::wrap($3, true)')
_CONVERSION(`const Glib::RefPtr<Gdk::Drawable>&',`GdkDrawable*',`Glib::unwrap($3)')
_CONVERSION(`GtkTextTag*',`const Glib::RefPtr<Gtk::TextTag>&',`Glib::wrap($3, true)')
_CONVERSION(`const Glib::RefPtr<Gtk::TextTag>&',`GtkTextTag*',`Glib::unwrap($3)')