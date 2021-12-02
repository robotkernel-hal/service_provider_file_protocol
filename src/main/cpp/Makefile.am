
lib_LTLIBRARIES = libservice_provider_file_protocol.la libservice_definitions.la

extraincludedir = $(includedir)/service_provider/file_protocol
extrainclude_HEADERS = include/service_provider/file_protocol/base.h

libservice_provider_file_protocol_la_SOURCES  = provider.cpp mds.cpp
libservice_provider_file_protocol_la_CXXFLAGS = --std=c++11 -fno-strict-aliasing -Wall 			\
												-I$(srcdir) -I$(builddir) -I$(srcdir)/include 	\
												@ROBOTKERNEL_CFLAGS@ 
libservice_provider_file_protocol_la_LDFLAGS  = -Wall -release $(PACKAGE_VERSION)

libservice_definitions_la_SOURCES  = mds.cpp
libservice_definitions_la_CXXFLAGS = --std=c++11 -fno-strict-aliasing -Wall -I$(srcdir)
