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

#ifndef __SERVICE_PROVIDER__FILE_PROTOCOL__PROVIDER_H__
#define __SERVICE_PROVIDER__FILE_PROTOCOL__PROVIDER_H__

// Robotkernel includes
#include "robotkernel/service_provider_base.h"
#include "robotkernel/service.h"
#include "robotkernel/log_base.h"

// Service provider includes
#include "service_provider/file_protocol/base.h"
#include "service_definitions.h"

namespace service_provider {
namespace file_protocol {

// forward declaration
class handler;

class provider : public robotkernel::service_provider_base<handler, base> {
    public:
        //! default construction
        /*!
         * \param node configuration node
         */
        provider(const std::string& name)
            : service_provider_base(name, "file_protocol") {};
};

class handler : 
    public robotkernel::log_base,
    public svc_base_file_read, 
    public svc_base_file_write
{
    public:
        typedef std::shared_ptr<service_provider::file_protocol::base> sp_cp_base_t;
        sp_cp_base_t _instance;

        static const std::string service_definition_file_read;
        static const std::string service_definition_file_write;

        //! handler construction
        handler(const robotkernel::sp_service_interface_t& req);

        //! handler destruction
        ~handler() {}

        //! svc_file_read
        /*!
         * \param[in]   req     Service request data.
         * \param[out]  resp    Service response data.
         */
        virtual void svc_file_read(const struct svc_req_file_read& req, struct svc_resp_file_read& resp);

        //! svc_file_write
        /*!
         * \param[in]   req     Service request data.
         * \param[out]  resp    Service response data.
         */
        virtual void svc_file_write(const struct svc_req_file_write& req, struct svc_resp_file_write& resp);
};

}; // namespace file_protocol
}; // namespace service_provider

#endif // __SERVICE_PROVIDER__FILE_PROTOCOL__PROVIDER_H__

