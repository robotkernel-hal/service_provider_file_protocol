//! robotkernel service provider file protocol
/*!
 * author: Robert Burger
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

#include "provider.h"

#include "robotkernel/kernel.h"
#include "robotkernel/exceptions.h"

SERVICE_PROVIDER_DEF(file_protocol, 
        service_provider::file_protocol::provider);

using namespace std;
using namespace std::placeholders;
using namespace robotkernel;
using namespace service_provider;
using namespace string_util;

//! default construction
/*!
 * \param node configuration node
 */
file_protocol::handler::handler(const robotkernel::sp_service_interface_t& req) 
    : log_base("file_protocol", req->owner + "." + req->device_name) {
    robotkernel::kernel& k = *robotkernel::kernel::get_instance();

    _instance = std::dynamic_pointer_cast<service_provider::file_protocol::base>(req);
    if (!_instance)
        throw str_exception("wrong base class");

    k.add_service(_instance->owner, _instance->device_name + ".file_read", 
            service_definition_file_read,
            std::bind(&file_protocol::handler::service_file_read, this, _1, _2));
    k.add_service(_instance->owner, _instance->device_name + ".file_write", 
            service_definition_file_write,
            std::bind(&file_protocol::handler::service_file_write, this, _1, _2));
}

//! handler destruction
file_protocol::handler::~handler() {
    kernel& k = *kernel::get_instance();
    k.remove_service(_instance->owner, _instance->device_name + ".file_read");
    k.remove_service(_instance->owner, _instance->device_name + ".file_write");
}

//! service callback request file read
/*!
 * \param request service request data
 * \param response service response data
 * \return success
 */
int file_protocol::handler::service_file_read(
        const robotkernel::service_arglist_t& request, 
        robotkernel::service_arglist_t& response) {
    // request data
#define FILE_READ_REQ_PASSWORD      0
#define FILE_READ_REQ_FILE_NAME     1
    string password  = request[FILE_READ_REQ_PASSWORD];
    string file_name = request[FILE_READ_REQ_FILE_NAME];

    file_readwrite_info_t info = { password, file_name };
    
    // default response values
    string error_message = "";
    std::vector<rk_type> file_data;

    try {
        _instance->file_read(info);
        file_data.assign(info.file_data.begin(), info.file_data.end());
    } catch (std::exception& e) {
        error_message = e.what();
    }
                            
    // response data
#define FILE_READ_RESP_FILE_DATA        0
#define FILE_READ_RESP_ERROR_MESSAGE    1
    response.resize(2);
    response[FILE_READ_RESP_FILE_DATA]      = file_data;
    response[FILE_READ_RESP_ERROR_MESSAGE]  = error_message;

    return 0;
}

const std::string file_protocol::handler::service_definition_file_read =
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
int file_protocol::handler::service_file_write(
        const robotkernel::service_arglist_t& request, 
        robotkernel::service_arglist_t& response) {
    // request data
#define FILE_READ_REQ_PASSWORD      0
#define FILE_READ_REQ_FILE_NAME     1
#define FILE_READ_REQ_FILE_DATA     2
    string password  = request[FILE_READ_REQ_PASSWORD];
    string file_name = request[FILE_READ_REQ_FILE_NAME];
    std::vector<rk_type> file_data = request[FILE_READ_REQ_FILE_DATA];

    file_readwrite_info_t info = { password, file_name };
    info.file_data.assign(file_data.begin(), file_data.end());

    // default response values
    string error_message = "";

    try {
        _instance->file_write(info);
    } catch (std::exception& e) {
        error_message = e.what();
    }

    // response data
#define FILE_WRITE_RESP_ERROR_MESSAGE    0
    response.resize(1);
    response[FILE_WRITE_RESP_ERROR_MESSAGE]  = error_message;

    return 0;
}

const std::string file_protocol::handler::service_definition_file_write =
"request:\n"
"   string: password\n"
"   string: file_name\n"
"   vector/uint8_t: file_data\n"
"response:\n"
"   string: error_message\n";

