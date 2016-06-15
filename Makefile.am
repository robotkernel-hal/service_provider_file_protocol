ACLOCAL_AMFLAGS = -I m4 -I scripts/m4

libdir = $(prefix)/lib
lib_LTLIBRARIES = libinterface_file_protocol.la
BUILT_SOURCES = ln_messages.h
CLEANFILES = ln_messages.h

libinterface_file_protocol_la_SOURCES  = interface_file_protocol.cpp

libinterface_file_protocol_la_CXXFLAGS = -fno-strict-aliasing \
											-Wall \
											-I$(top_srcdir)/src \
											-I$(top_builddir) \
											@ROBOTKERNEL_CFLAGS@ \
								 			@LIBSTRING_UTIL_CFLAGS@

libinterface_file_protocol_la_LDFLAGS  = -Wall -release $(PACKAGE_VERSION)

VPATH = $(srcdir):$(srcdir)/share/ln/message_definitions

LN_MESSAGES = robotkernel/file_protocol/file_read \
			  robotkernel/file_protocol/file_write

ln_messages.h: Makefile $(LN_MESSAGES)
	@echo creating ln_messages.h
	@LN_GENERATE@ -o $@ $(LN_MESSAGES)
	touch $@

install-exec-hook:
	mkdir -p $(prefix)/share
	-cp -rf $(srcdir)/share/* $(prefix)/share/

