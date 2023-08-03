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
#include "service_definitions.h"

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
    : log_base(req->owner, "file_protocol", req->device_name) 
{
    _instance = std::dynamic_pointer_cast<service_provider::file_protocol::base>(req);
    if (!_instance)
        throw str_exception("wrong base class");

    add_svc_file_read(_instance->owner, _instance->device_name + ".file_read");
    add_svc_file_write(_instance->owner, _instance->device_name + ".file_write");
}

//! svc_file_read
/*!
 * \param[in]   req     Service request data.
 * \param[out]  resp    Service response data.
 */
void file_protocol::handler::svc_file_read(const struct svc_req_file_read& req, struct svc_resp_file_read& resp) {
    file_readwrite_info_t info = { req.password, req.file_name };
    
    try {
        _instance->file_read(info);
        resp.file_data.assign(info.file_data.begin(), info.file_data.end());
    } catch (std::exception& e) {
        resp.error_message = e.what();
    }
}

//! svc_file_write
/*!
 * \param[in]   req     Service request data.
 * \param[out]  resp    Service response data.
 */
void file_protocol::handler::svc_file_write(const struct svc_req_file_write& req, struct svc_resp_file_write& resp) {
    file_readwrite_info_t info = { req.password, req.file_name };
    info.file_data.assign(req.file_data.begin(), req.file_data.end());

    try {
        _instance->file_write(info);
    } catch (std::exception& e) {
        resp.error_message = e.what();
    }
}

