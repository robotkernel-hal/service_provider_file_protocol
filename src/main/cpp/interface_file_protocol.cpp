//! robotkernel interface file protocol
/*!
 * author: Robert Burger
 *
 * $Id$
 */

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab:

/*
 * This file is part of robotkernel.
 *
 * robotkernel is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * robotkernel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with robotkernel.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>

#include "module_intf.h"
#include "interface_file_protocol.h"
#include "robotkernel/kernel.h"
#include "robotkernel/exceptions.h"

SERVICE_PROVIDER_DEF(file_protocol, interface_file_protocol::file_protocol);

using namespace std;
using namespace std::placeholders;
using namespace robotkernel;
using namespace interface_file_protocol;

const char* interface_file_protocol::file_protocol_sp_magic = "file_protocol"; 

#ifndef __linux__
char *strndup(const char *s, size_t n) {
	char *result;
	size_t len = strlen (s);

	if (n < len)
		len = n;

	result = (char *) malloc (len + 1);
	if (!result)
		return 0;

	result[len] = '\0';
	return (char *) memcpy (result, s, len);
}
#endif

//! default construction
/*!
 * \param node configuration node
 */
file_protocol_handler::file_protocol_handler(
		std::string mod_name, std::string dev_name, int slave_id) : 
	log_base(mod_name, (mod_name + "." + dev_name + ".file_protocol")), 
	mod_name(mod_name), dev_name(dev_name), slave_id(slave_id) {
	kernel& k = *kernel::get_instance();

	stringstream base;
	base << mod_name << "." << dev_name << ".file_protocol.";

	k.add_service(mod_name, base.str() + "file_read", 
			service_definition_file_read,
			std::bind(&file_protocol_handler::service_file_read, this, _1, _2));
	k.add_service(mod_name, base.str() + "file_write", 
			service_definition_file_write,
			std::bind(&file_protocol_handler::service_file_write, this, _1, _2));
}
			
//! handler destruction
file_protocol_handler::~file_protocol_handler() {
	kernel& k = *kernel::get_instance();

	stringstream base;
	base << mod_name << "." << dev_name << ".file_protocol.";
	k.remove_service(base.str() + "file_read");
	k.remove_service(base.str() + "file_write");
}

//! service callback request file read
/*!
 * \param request service request data
 * \param response service response data
 * \return success
 */
int file_protocol_handler::service_file_read(const robotkernel::service_arglist_t& request, 
		robotkernel::service_arglist_t& response) {
	// request data
#define FILE_READ_REQ_PASSWORD      0
#define FILE_READ_REQ_FILE_NAME     1
	string password  = request[FILE_READ_REQ_PASSWORD];
	string file_name = request[FILE_READ_REQ_FILE_NAME];

	// default response values
	std::vector<uint8_t> file_data;
	string error_message = "";

	file_readwrite_info_t frwi;
	memset(&frwi, 0, sizeof(frwi));
	frwi.slave_id  = slave_id;
	frwi.password  = password.c_str();
	frwi.file_name = file_name.c_str();

	// execute module request file read
	int ret = kernel::request_cb(mod_name.c_str(), 
			MOD_REQUEST_FILE_READ, (void *)&frwi);
	if (ret == -1) {
		if (frwi.error_message) {
			error_message = frwi.error_message;
			free(frwi.error_message);
		} else
			error_message = "reading file failed!";

		return 0;
	}

	if (frwi.file_data) {
		if (frwi.file_data_len > 0) {
			// copy file data
			file_data.resize(frwi.file_data_len);
			file_data.assign(frwi.file_data, 
					frwi.file_data + frwi.file_data_len);
		}

		free(frwi.file_data);
	}

	// response data
#define FILE_READ_RESP_FILE_DATA        0
#define FILE_READ_RESP_ERROR_MESSAGE    1
	response.resize(2);
	response[FILE_READ_RESP_FILE_DATA]      = file_data;
	response[FILE_READ_RESP_ERROR_MESSAGE]  = error_message;

	return 0;
}

const std::string file_protocol_handler::service_definition_file_read =
"request:\n"
"   string: password\n"
"   string: file_name\n"
"response:\n"
"   vector/uint8_t: file_data\n"
"   string: error_message\n";

//! service callback request file write
/*!
 * \param request service request data
 * \param response service response data
 * \return success
 */
int file_protocol_handler::service_file_write(
		const robotkernel::service_arglist_t& request, 
		robotkernel::service_arglist_t& response) {
	// request data
#define FILE_READ_REQ_PASSWORD      0
#define FILE_READ_REQ_FILE_NAME     1
#define FILE_READ_REQ_FILE_DATA     2
	string password = request[FILE_READ_REQ_PASSWORD];
	string file_name = request[FILE_READ_REQ_FILE_NAME];
	std::vector<uint8_t> file_data = request[FILE_READ_REQ_FILE_DATA];

	// default response values
	string error_message = "";

	file_readwrite_info_t frwi;
	memset(&frwi, 0, sizeof(frwi));
	frwi.slave_id = slave_id;
	frwi.password = password.c_str();
	frwi.file_name = file_name.c_str();
	frwi.file_data = &file_data[0];
	frwi.file_data_len = file_data.size();

	// execute module request file write
	int ret = kernel::request_cb(mod_name.c_str(), 
			MOD_REQUEST_FILE_WRITE, (void *)&frwi);
	if (ret == -1) {
		if (frwi.error_message) {
			error_message = frwi.error_message;
			free(frwi.error_message);
		} else
			error_message = "writing file failed!";
	}

	// response data
#define FILE_WRITE_RESP_ERROR_MESSAGE    0
	response.resize(2);
	response[FILE_WRITE_RESP_ERROR_MESSAGE]  = error_message;

	return 0;
}

const std::string file_protocol_handler::service_definition_file_write =
"request:\n"
"   string: password\n"
"   string: file_name\n"
"   vector/uint8_t: file_data\n"
"response:\n"
"   string: error_message\n";

