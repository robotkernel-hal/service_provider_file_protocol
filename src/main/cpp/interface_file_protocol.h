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

#ifndef __INTERFACE_file_protocol_handler_H__
#define __INTERFACE_file_protocol_handler_H__

#include "robotkernel/service_provider_base.h"
#include "robotkernel/service_provider_intf.h"
#include "robotkernel/service.h"
#include "robotkernel/kernel.h"
#include "robotkernel/log_base.h"

namespace interface_file_protocol {
	extern const char* file_protocol_sp_magic;

	// forward declaration
	class file_protocol_handler;

	class file_protocol : 
		public robotkernel::service_provider_base<file_protocol_handler> {
			public:
				//! default construction
				/*!
				 * \param node configuration node
				 */
				file_protocol()
					: service_provider_base("file_protocol") {};

				~file_protocol() {};

				//! service provider magic 
				/*!
				 * \return return service provider magic string
				 */
				const char* get_sp_magic() 
				{ return file_protocol_sp_magic; };
	};

	class file_protocol_handler : public robotkernel::log_base {
		public:
			std::string mod_name;	//!< slave owner module
			std::string dev_name;	//!< service device name
			int slave_id;			//!< slave identifier

			//! handler construction
			file_protocol_handler(std::string mod_name, std::string dev_name, int slave_id);

			//! handler destruction
			~file_protocol_handler();

			//! service callback request file read
			/*!
			 * \param request service request data
			 * \parma response service response data
			 * \return success
			 */
			int service_file_read(const robotkernel::service_arglist_t& request, 
					robotkernel::service_arglist_t& response);
			static const std::string service_definition_file_read;	

			//! service callback request file write
			/*!
			 * \param request service request data
			 * \parma response service response data
			 * \return success
			 */
			int service_file_write(const robotkernel::service_arglist_t& request, 
					robotkernel::service_arglist_t& response);
			static const std::string service_definition_file_write;	
	};

} // namespace interface

#endif // __INTERFACE_file_protocol_handler_H__

