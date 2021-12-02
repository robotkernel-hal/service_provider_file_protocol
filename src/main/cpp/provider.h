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

#include "robotkernel/service_provider_base.h"
#include "robotkernel/service_provider_intf.h"
#include "robotkernel/service.h"
#include "robotkernel/kernel.h"
#include "robotkernel/log_base.h"

#include "service_provider/file_protocol/base.h"

namespace service_provider {
#ifdef EMACS
}
#endif

namespace file_protocol {
#ifdef EMACS
}
#endif

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

class handler : public robotkernel::log_base {
    public:
        typedef std::shared_ptr<service_provider::file_protocol::base> sp_cp_base_t;
        sp_cp_base_t _instance;

        //! handler construction
        handler(const robotkernel::sp_service_interface_t& req);

        //! handler destruction
        ~handler();

        //! service callback request file read
        /*!
         * \param request service request data
         * \parma response service response data
         * \return success
         */
        int service_file_read(const robotkernel::service_arglist_t& request, 
                robotkernel::service_arglist_t& response);

        //! service callback request file write
        /*!
         * \param request service request data
         * \parma response service response data
         * \return success
         */
        int service_file_write(const robotkernel::service_arglist_t& request, 
                robotkernel::service_arglist_t& response);
};

#ifdef EMACS
{
#endif
}; // namespace file_protocol


#ifdef EMACS
{
#endif
}; // namespace service_provider

#endif // __SERVICE_PROVIDER__FILE_PROTOCOL__PROVIDER_H__

