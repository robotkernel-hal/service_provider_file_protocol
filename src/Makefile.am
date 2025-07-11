ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libservice_provider_file_protocol.la

BUILT_SOURCES = $(top_builddir)/src/service_definitions.h
CLEANFILES = $(top_builddir)/src/service_definitions.h

extraincludedir = $(includedir)/service_provider_file_protocol
extrainclude_HEADERS = $(top_srcdir)/include/service_provider_file_protocol/base.h

libservice_provider_file_protocol_la_SOURCES  = provider.cpp
libservice_provider_file_protocol_la_CXXFLAGS = --std=c++11 -fno-strict-aliasing -Wall 			\
												-I$(top_srcdir)/include -I$(builddir)/include -I$(srcdir)	\
												@ROBOTKERNEL_CFLAGS@ 
libservice_provider_file_protocol_la_LDFLAGS  = -Wall -release $(PACKAGE_VERSION)

VPATH = $(srcdir):$(top_srcdir)/share/service_definitions

SERVICE_DEFINITIONS = service_provider_file_protocol/file_read \
					  service_provider_file_protocol/file_write

$(top_builddir)/src/service_definitions.h: Makefile $(SERVICE_DEFINITIONS)
	@echo creating $@
	service_generate --indir $(top_srcdir)/share/service_definitions --out $@ $(SERVICE_DEFINITIONS)
	touch $@


