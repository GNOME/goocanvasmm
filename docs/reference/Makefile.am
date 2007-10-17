
doxygen_configfile = Doxyfile
web_path_reference = /home/groups/g/gt/gtkmm/htdocs/gtkmm2DONTUPLOADTHIS/reference

EXTRA_DIST	= README $(doxygen_configfile)


goocanvasmm-reference: $(doxygen_configfile)
	doxygen $(doxygen_configfile)

goocanvasmm-reference-html: goocanvasmm-reference

goocanvasmm-reference-html.tar.gz: goocanvasmm-reference-html
	tar -cf - $< | gzip > $@


post-html: goocanvasmm-reference
	(cd html && tar -cf - *.html *.gif *.css | gzip -3 | \
	 ssh $$SSH_OPT $$USER@gtkmm.sourceforge.net "cd $(web_path_reference)/html ; gunzip | tar -xvf - ; chmod a+r,g+w * ; chgrp gtkmm *")


all-local: goocanvasmm-reference

clean-local:
	-rm -rf html
	-rm -f goocanvasmm-reference-html.tar.gz

