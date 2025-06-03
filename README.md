That service provider suppliles services for all robotkernel modules
with support for file protocol devices. The service provider will
provide acyclic calls for file up- and downloads.

# Configuration

No specific configuration is needed for the service provider. The
robotkernel just needs to know which service provider to load. To load
der *service_provider_file_protocol* just add it to your config file.

```yaml
service_providers:
- name: file_sp
  so_file: libservice_provider_file_protocol.so
```

# Services

This service provider will register two services to the robotkernel-5.
One for reading and one for writing files.

## file_read

This service support reading of files from a robotkernel-5 device. The
service definition request contains the target file name (file_name) and
an optional file password. The caller will get an error signaled in the
error message response field, otherwise (on success) this will be empty
and the file data buffer.

```yaml
request:
- string: password
- string: file_name
response:
- vector/uint8_t: file_data
- string: error_message
```

## file_write

This service support writing of files to a robotkernel-5 device. The
service definition request contains the target file name (file_name), an
optional file password and the file data buffer. The caller will get an
error signaled in the error message response field, otherwise (on
success) this will be empty.

```yaml
request:
- string: password
- string: file_name
- vector/uint8_t: file_data
response:
- string: error_message
```

All of these services will be available through a robotkernel brigdge
(e.g. [bridge_ln](robotkernel-5/bridge_ln "wikilink"),
[bridge_jsonrpc](robotkernel-5/bridge_jsonrpc "wikilink"),
[bridge_cli](robotkernel-5/bridge_cli "wikilink"), \...)

# Implement a file protocol device {#implement_a_file_protocol_device}

To implement a robotkernel-5 device with file protocol support you have
to include service_provider/file_protocol/base.h and derive your
device class from service_provider::file_protocol::base.

```c++
base(std::string owner, std::string service_prefix)
```

You have to call the base constructor with the owner string - usually
the module name - and a service_prefix string. You have to implement
all virtual functions of the base class.

```c++
//! read from file
/*!
 * \param info file info structure
 */
virtual void file_read(file_readwrite_info_t& info) = 0;

//! write to file
/*!
 * \param info file info structure
 */
virtual void file_write(const file_readwrite_info_t& info) = 0;
```

[Service Provider File Protocol](Category:Robotkernel-5 "wikilink")

