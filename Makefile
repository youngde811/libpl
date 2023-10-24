
# This Makefile may be used to build libpl, a thin veneer over the libc getcontext() function, for use
# with Swift on Linux. At present, only Debian-based distributions are supported.

uname := $(shell uname)
arch := $(shell uname -m)

SRCDIR := src
INCDIR := include
LIBDIR := lib
TESTDIR := test
PKGDIR := packages
DEBDIR := $(PKGDIR)/debian
DEBLIB := $(DEBDIR)/libpl
PACKAGE := $(DEBLIB)/libpl.deb

CC := gcc
CFLAGS := -ansi -g -I$(INCDIR)

SRC := $(wildcard $(SRCDIR)/*.c)
OBJ := $(SRC:$(SRCDIR)/%.c=$(LIBDIR)/%.o)

TEST := $(wildcard $(TESTDIR)/*.c)
TESTOBJ := $(TEST:$(TESTDIR)/%.c=$(TESTDIR)/%.o)
TESTDRIVER := $(TESTDIR)/driver

LDFLAGS := -L.

ifeq ($(arch), aarch64)
PKGNAME := $(PKGDIR)/libpl-arm64.deb
endif

$(info Architecture is: $(arch))

ifeq ($(arch), x86_64)
PKGNAME := $(PKGDIR)/libpl-x86_64.deb
endif

MAJOR := libpl-1.0.0.so
BASE := libpl.so

LIBNAME := $(LIBDIR)/$(MAJOR)

.PHONY: all clean ctags debian etags libpl lint packages

all: libpl packages

libpl: $(LIBNAME)
packages: debian
test: $(TESTDRIVER) libpl

$(LIBNAME): LDFLAGS += -shared
$(LIBNAME): $(OBJ)
	$(CC) $(LDFLAGS) $^ -Wl,-soname,$(MAJOR) -o $@

$(LIBDIR): CFLAGS += -fPIC
$(LIBDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(TESTDIR)/%.o: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(TESTDRIVER): $(TESTOBJ)
	$(CC) -o $@ $< -L/usr/lib/plogic -lpl

debian: libpl $(PKGNAME)

$(PKGNAME):
	@bin/mklibpl

lint: $(PKGNAME)
	@lintian $(DEBDIR)/libpl.deb

ctags:
	ctags -R --languages=C .

etags:
	etags -R --languages=C .

clean:
	@rm -rf lib/libpl.o lib/libpl.* $(DEBDIR)/*.deb
	@rm -f $(TESTDIR)/*.o $(TESTDRIVER)
	@rm -rf $(DEBLIB)/usr
