MAINTAINERCLEANFILES = Makefile.in aclocal.m4 config.guess config.h.in \
		       config.sub configure depcomp install-sh ltmain.sh \
		       missing module.desktop config.rpath mkinstalldirs

SUBDIRS = src \
data

filesdir = $(datadir)
files_DATA = module.desktop

EXTRA_DIST = module.desktop.in \
	     e_modules-comptonmod.spec.in \
	     data/images/module_icon.png

clean-local:
	 rm -rf module.desktop e_modules-comptonmod.spec *~

uninstall:
	rm -rf $(DESTDIR)$(datadir)
