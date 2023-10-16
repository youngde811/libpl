
# This Makefile may be used to build libpl, a thin veneer over the libc getcontext() function, for use
# with Swift on Linux. At present, only Debian-based distributions are supported.

uname := $(shell uname)

SRCDIR := src
INCDIR := include
LIBDIR := lib
PKGDIR := packages
DEBDIR := $(PKGDIR)/debian
DEBLIB := $(DEBDIR)/libpl

CC := gcc
CFLAGS := -ansi -pedantic -Wall -Werror -g -I$(INCDIR) -fPIC

SRC := $(wildcard $(SRCDIR)/*.c)
OBJ := $(SRC:$(SRCDIR)/%.c=$(LIBDIR)/%.o)

LIBNAME := $(LIBDIR)/libpl.so
LDFLAGS := -L.

PKGNAME := $(PKGDIR)/libpl.deb

MAJOR := libpl.so.1.0.0
MINOR := libpl.so.1
BASE := libpl.so

.PHONY: all clean ctags etags libpl lint packages

$(info Building for: [${uname}])

all: libpl packages

libpl: $(LIBNAME)
packages: debian

$(LIBNAME): LDFLAGS += -shared
$(LIBNAME): $(OBJ)
	$(CC) $(LDFLAGS) $^ -Wl,-soname,libpl.so.1 -o $@.1.0.0

$(LIBDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

debian: $(PKGNAME) libpl
	@mkdir -p $(DEBLIB)/usr/lib
	@mkdir -p $(DEBLIB)/usr/include
	@mkdir -p $(DEBLIB)/usr/share/doc/libpl
	@cp $(LIBDIR)/$(MAJOR) $(DEBLIB)/usr/lib
	@(cd $(DEBLIB)/usr/lib; ln -fs $(MAJOR) $(MINOR); ln -fs $(MINOR) $(BASE))
	@cp $(INCDIR)/libpl.h $(DEBLIB)/usr/include
	@gzip --best -cn $(DEBDIR)/changelog.Debian > $(DEBLIB)/usr/share/doc/libpl/changelog.Debian.gz
	@cp $(DEBDIR)/copyright $(DEBLIB)/usr/share/doc/libpl
	@(cd $(DEBDIR); dpkg-deb --root-owner-group --build libpl)

lint: $(PKGNAME)
	@lintian $(DEBDIR)/libpl.deb

ctags:
	ctags -R --languages=C .

etags:
	etags -R --languages=C .

clean:
	rm -rf lib/*.o lib/*.so $(DEBDIR)/*.deb
	rm -rf $(DEBLIB)/usr
