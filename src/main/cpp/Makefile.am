ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libservice_provider_file_protocol.la

BUILT_SOURCES = $(top_builddir)/src/main/cpp/service_definitions.h
CLEANFILES = $(top_builddir)/src/main/cpp/service_definitions.h

extraincludedir = $(includedir)/service_provider/file_protocol
extrainclude_HEADERS = include/service_provider/file_protocol/base.h

libservice_provider_file_protocol_la_SOURCES  = provider.cpp
libservice_provider_file_protocol_la_CXXFLAGS = --std=c++11 -fno-strict-aliasing -Wall 			\
												-I$(srcdir) -I$(builddir) -I$(srcdir)/include 	\
												@ROBOTKERNEL_CFLAGS@ 
libservice_provider_file_protocol_la_LDFLAGS  = -Wall -release $(PACKAGE_VERSION)

VPATH = $(srcdir):$(top_srcdir)/share/service_definitions

SERVICE_DEFINITIONS = robotkernel/service_provider_file_protocol/file_read \
					  robotkernel/service_provider_file_protocol/file_write

$(top_builddir)/src/main/cpp/service_definitions.h: Makefile $(SERVICE_DEFINITIONS)
	install -d $(top_builddir)/src/main/cpp/include/robotkernel
	@echo creating $@
	service_generate --indir $(top_srcdir)/share/service_definitions --out $@ $(SERVICE_DEFINITIONS)
	touch $@


