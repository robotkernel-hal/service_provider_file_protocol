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

#ifndef __SERVICE_PROVIDER__FILE_PROTOCOL__BASE__H__
#define __SERVICE_PROVIDER__FILE_PROTOCOL__BASE__H__

#include <list>

#include "robotkernel/service_requester_base.h"

namespace service_provider {

    namespace file_protocol {

        //! file read 
        typedef struct file_readwrite_info {
            std::string          password;   //! [in]     file password
            std::string          file_name;  //! [in]     file name
            std::vector<uint8_t> file_data;  //! [in/out] file data
        } file_readwrite_info_t;

        class base : public robotkernel::service_requester_base {
            public:
                //! construction
                base(std::string owner, std::string service_prefix)
                : robotkernel::service_requester_base(owner, service_prefix) {};

                //! destruction
                virtual ~base() = 0;

                //! read from file
                /*!
                 * \param info file info structure
                 */
                virtual void file_read(file_readwrite_info_t& info) = 0;

                //! write to file
                /*!
                 * \param info file info structure
                 */
                virtual void file_write(const file_readwrite_info_t& info) = 0;
        };
        
        inline base::~base() { }

    }; // namespace file_protocol

}; // namespace service_provider

#endif // __SERVICE_PROVIDER__FILE_PROTOCOL__BASE__H__

